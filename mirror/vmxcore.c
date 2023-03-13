#include "idefs.h"
#include "common.h"
#include "logger.h"
#include "features.h"
#include "vmxcore.h"
#include "thunk.h"

extern PVOID TuPageDirectoryPointer;

VOID NTAPI
VmxUnprepareDomainSpace(
    __in PVMX_DOMAIN Domain
)
{
    if (NULL != Domain->Vmon) {
        CmFreeContiguousMemory(Domain->Vmon);
    }

    if (NULL != Domain->Vmcs) {
        CmFreeContiguousMemory(Domain->Vmcs);
    }

    if (NULL != Domain->MsrBitmap) {
        CmFreeContiguousMemory(Domain->MsrBitmap);
    }

    if (NULL != Domain->IoBitmap) {
        CmFreeContiguousMemory(Domain->IoBitmap);
    }

    if (NULL != Domain->VmmStack) {
        CmFreeNonPagedMemory(Domain->VmmStack);
    }

    if (NULL != Domain->Tss) {
        CmFreeNonPagedMemory(Domain->Tss);
    }

    if (NULL != Domain->XSaveArea) {
        CmFreeNonPagedMemory(Domain->XSaveArea);
    }

    if (NULL != Domain->Gdtr.Base) {
        CmFreeNonPagedMemory(Domain->Gdtr.Base);
    }

    if (NULL != Domain->Idtr.Base) {
        CmFreeNonPagedMemory(Domain->Idtr.Base);
    }
}

NTSTATUS NTAPI
VmxPrepareDomainSpace(
    __in PVMX_DOMAIN Domain
)
{
    Domain->Vmon = CmAllocateContiguousMemory(sizeof(VMX_REGION));

    if (NULL == Domain->Vmon) {
        goto Cleanup;
    }

    Domain->Vmcs = CmAllocateContiguousMemory(sizeof(VMX_REGION));

    if (NULL == Domain->Vmcs) {
        goto Cleanup;
    }

    Domain->MsrBitmap = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == Domain->MsrBitmap) {
        goto Cleanup;
    }

    Domain->IoBitmap = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == Domain->IoBitmap) {
        goto Cleanup;
    }

    Domain->VmmStack = CmAllocateNonPagedMemory(KERNEL_LARGE_STACK_SIZE);

    if (NULL == Domain->VmmStack) {
        goto Cleanup;
    }

    Domain->Tss = CmAllocateNonPagedMemory(sizeof(KTSS));

    if (NULL == Domain->Tss) {
        goto Cleanup;
    }

    Domain->XSaveArea = CmAllocateNonPagedMemory(FeaGetXFeatureSupportedSizeMax());

    if (NULL == Domain->XSaveArea) {
        goto Cleanup;
    }

    Domain->Gdtr.Base = CmAllocateNonPagedMemory(VGDT_LAST);

    if (NULL == Domain->Gdtr.Base) {
        goto Cleanup;
    }

    Domain->Idtr.Base = CmAllocateNonPagedMemory(PAGE_SIZE);

    if (NULL == Domain->Idtr.Base) {
        goto Cleanup;
    }

    return STATUS_SUCCESS;

Cleanup:

    if (NULL != Domain->Vmon) {
        CmFreeContiguousMemory(Domain->Vmon);
    }

    if (NULL != Domain->Vmcs) {
        CmFreeContiguousMemory(Domain->Vmcs);
    }

    if (NULL != Domain->MsrBitmap) {
        CmFreeContiguousMemory(Domain->MsrBitmap);
    }

    if (NULL != Domain->IoBitmap) {
        CmFreeContiguousMemory(Domain->IoBitmap);
    }

    if (NULL != Domain->VmmStack) {
        CmFreeNonPagedMemory(Domain->VmmStack);
    }

    if (NULL != Domain->Tss) {
        CmFreeNonPagedMemory(Domain->Tss);
    }

    if (NULL != Domain->XSaveArea) {
        CmFreeNonPagedMemory(Domain->XSaveArea);
    }

    if (NULL != Domain->Gdtr.Base) {
        CmFreeNonPagedMemory(Domain->Gdtr.Base);
    }

    if (NULL != Domain->Idtr.Base) {
        CmFreeNonPagedMemory(Domain->Idtr.Base);
    }

    return STATUS_INSUFFICIENT_RESOURCES;
}

VOID NTAPI
VmxFreeDomain(
    __in ULONG Number,
    __in PVMX_DOMAIN Domain
)
{
    ULONG Index;

    for (Index = 0; Index < Number; Index++) {
        VmxUnprepareDomainSpace(&Domain[Index]);
    }

    CmFreeNonPagedMemory(Domain);
}

PVMX_DOMAIN NTAPI
VmxAllocateDomain(
    __in ULONG Number
)
{
    NTSTATUS Status;
    PVMX_DOMAIN Domain;
    ULONG Succeed;
    ULONG Index;

    Domain = CmAllocateNonPagedMemory(Number * sizeof(VMX_DOMAIN));

    if (NULL != Domain) {
        for (Index = 0; Index < Number; Index++) {

            Status = VmxPrepareDomainSpace(&Domain[Index]);

            if (FALSE == NT_SUCCESS(Status)) {
                break;
            }
        }

        if (FALSE == NT_SUCCESS(Status)) {
            Succeed = Index;

            for (Index = 0; Index < Succeed; Index++) {
                VmxUnprepareDomainSpace(&Domain[Index]);
            }

            CmFreeNonPagedMemory(Domain);
            Domain = NULL;
        }
    }

    return Domain;
}

VOID NTAPI
VmxPrepareGdtEntry(
    __in PVMX_DOMAIN Domain
)
{
#ifndef _WIN64
    
#else
    CmBuildAmd64GdtEntry(Domain->Gdtr.Base, VGDT_NULL, 0, 0, 0, 0, FALSE, FALSE);
    CmBuildAmd64GdtEntry(Domain->Gdtr.Base, VGDT_CODE, 0, 0, TYPE_CODE, DPL_SYSTEM, TRUE, TRUE);
    CmBuildAmd64GdtEntry(Domain->Gdtr.Base, VGDT_DATA, 0, 0, TYPE_DATA, DPL_SYSTEM, FALSE, TRUE);
    CmBuildAmd64GdtEntry(Domain->Gdtr.Base, VGDT_TSS, 0, 0, TYPE_TSS64, DPL_SYSTEM, FALSE, TRUE);

    
#endif
}

VOID NTAPI
VmxPrepareIdtEntry()
{

}

ULONG NTAPI
VmxGetFeatures()
{
    ULONG Feature = 0;
    CPU_INFO CpuInfo;
    ULONGLONG Value;

    __ins_cpuidex(0x00000001, 0, &CpuInfo.Eax);
    if (0 != (0x00000020 & CpuInfo.Ecx)) {
        Feature |= VMX_FEATURE_SUPPORT;
    }

    Value = __ins_rdmsr(MSR_FEATURE_CONTROL);
    if (0 != (0x00000004 & Value)) {
        Feature |= VMX_FEATURE_ENABLE;
    }

    return TRUE;
}

NTSTATUS NTAPI
VmxFirstEntry(
    __in PVMX_DOMAIN Domain,
    __in PGUEST_CONTEXT Context
)
{
    PHYSICAL_ADDRESS PageDirectoryBase;
    PHYSICAL_ADDRESS VmonPa;
    PHYSICAL_ADDRESS VmcsPa;

    Domain->Features = VmxGetFeatures();

    if (0 == (Domain->Features & VMX_FEATURE_SUPPORT) ||
        0 == (Domain->Features & VMX_FEATURE_ENABLE)) {
        return STATUS_NOT_SUPPORTED;
    }

    Domain->BasicInfo.Value = __ins_rdmsr(MSR_VMX_BASIC);

    Domain->Vmon->Identifier = Domain->BasicInfo.Identifier;
    Domain->Vmcs->Identifier = Domain->BasicInfo.Identifier;

    if (0 == Domain->BasicInfo.TrueCtls) {
        Domain->PinFixed.QuadPart = __ins_rdmsr(MSR_VMX_PINBASED_CTLS);
        Domain->PrimaryFixed.QuadPart = __ins_rdmsr(MSR_VMX_PROCBASED_CTLS);
        Domain->SecondaryFixed.QuadPart = __ins_rdmsr(MSR_VMX_SECONDARY_CTLS);
        Domain->ExitFixed.QuadPart = __ins_rdmsr(MSR_VMX_EXIT_CTLS);
        Domain->EntryFixed.QuadPart = __ins_rdmsr(MSR_VMX_ENTRY_CTLS);
    }
    else {
        Domain->PinFixed.QuadPart = __ins_rdmsr(MSR_VMX_TRUE_PINBASED_CTLS);
        Domain->PrimaryFixed.QuadPart = __ins_rdmsr(MSR_VMX_TRUE_PROCBASED_CTLS);
        Domain->SecondaryFixed.QuadPart = __ins_rdmsr(MSR_VMX_SECONDARY_CTLS);
        Domain->ExitFixed.QuadPart = __ins_rdmsr(MSR_VMX_TRUE_EXIT_CTLS);
        Domain->EntryFixed.QuadPart = __ins_rdmsr(MSR_VMX_TRUE_ENTRY_CTLS);
    }

    Domain->Cr0 = Context->Cr0;
    Domain->Cr0 &= __ins_rdmsr(MSR_VMX_CR0_FIXED1);
    Domain->Cr0 |= __ins_rdmsr(MSR_VMX_CR0_FIXED0);

    PageDirectoryBase = MmGetPhysicalAddress(TuPageDirectoryPointer);

#ifndef _WIN64
    Domain->Cr3 = PageDirectoryBase.LowPart;
#else
    Domain->Cr3 = PageDirectoryBase.QuadPart;
#endif

    Domain->Cr4 = Context->Cr4;
    Domain->Cr4 &= __ins_rdmsr(MSR_VMX_CR4_FIXED1);
    Domain->Cr4 |= __ins_rdmsr(MSR_VMX_CR4_FIXED0);

    __ins_writecr(0, Domain->Cr0);
    __ins_writecr(4, Domain->Cr4);

    VmonPa = MmGetPhysicalAddress(Domain->Vmon);
    VmcsPa = MmGetPhysicalAddress(Domain->Vmcs);

    __ins_vmxon(&VmonPa.QuadPart);
    __ins_vmclear(&VmcsPa.QuadPart);
    __ins_vmptrld(&VmcsPa.QuadPart);

    __ins_vmlaunch();
    __ins_vmxoff();

    __ins_writecr(4, Domain->Cr4);
    __ins_writecr(0, Domain->Cr0);
    return STATUS_UNSUCCESSFUL;
}

NTSTATUS NTAPI
VmxTaskDispatcher(
    __in PVMX_DOMAIN Domain,
    __in ULONG TaskCode,
    __inout_opt PVOID Context
)
{
    NTSTATUS Status;
    PVMX_DOMAIN CurrentDomain;

    CurrentDomain = &Domain[KeGetCurrentProcessorNumber()];

    switch (TaskCode) {
    case TASK_STARTUP:
        Status = VmxPrepareStartup(CurrentDomain);
        LogSyncPrint("vmx startup < %p > | < %08x >\n", CurrentDomain, Status);
        break;
    case TASK_SHUTDOWN:
        LogSyncPrint("vmx shutdown < %p >\n", CurrentDomain);
        Status = STATUS_SUCCESS;
        break;
    default:
        Status = STATUS_INVALID_PARAMETER;
        break;
    }

    return Status;
}