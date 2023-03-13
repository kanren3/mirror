#include "idefs.h"
#include "common.h"
#include "logger.h"
#include "features.h"
#include "svmcore.h"
#include "thunk.h"

ULONG NTAPI
SvmGetFeatures()
{
    ULONG Feature = 0;
    CPU_INFO CpuInfo;
    ULONGLONG Value;

    __ins_cpuidex(0x80000001, 0, &CpuInfo.Eax);
    if (0 != (0x00000004 & CpuInfo.Ecx)) {
        Feature |= SVM_FEATURE_SUPPORT;
    }

    Value = __ins_rdmsr(MSR_VM_CR);
    if (0 == (0x00000010 & Value)) {
        Feature |= SVM_FEATURE_ENABLE;
    }

    __ins_cpuidex(0x8000000A, 0, &CpuInfo.Eax);
    if (0 != (0x00000001 & CpuInfo.Edx)) {
        Feature |= SVM_FEATURE_NPT;
    }

    if (0 != (0x00000020 & CpuInfo.Edx)) {
        Feature |= SVM_FEATURE_VMCB_CLEAN;
    }

    if (0 != (0x00000040 & CpuInfo.Edx)) {
        Feature |= SVM_FEATURE_FLUSH_BY_ASID;
    }

    return Feature;
}

VOID NTAPI
SvmUnprepareDomainSpace(
    __in PSVM_DOMAIN Domain
)
{
    if (NULL != Domain->Vmcb) {
        CmFreeContiguousMemory(Domain->Vmcb);
    }

    if (NULL != Domain->Vmhs) {
        CmFreeContiguousMemory(Domain->Vmhs);
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
SvmPrepareDomainSpace(
    __in PSVM_DOMAIN Domain
)
{
    Domain->Vmcb = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == Domain->Vmcb) {
        goto Cleanup;
    }

    Domain->Vmhs = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == Domain->Vmhs) {
        goto Cleanup;
    }

    Domain->MsrBitmap = CmAllocateContiguousMemory(PAGE_SIZE * 2);

    if (NULL == Domain->MsrBitmap) {
        goto Cleanup;
    }

    Domain->IoBitmap = CmAllocateContiguousMemory(PAGE_SIZE * 2);

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
    SvmUnprepareDomainSpace(Domain);
    return STATUS_INSUFFICIENT_RESOURCES;
}

VOID NTAPI
SvmFreeDomain(
    __in ULONG Number,
    __in PSVM_DOMAIN Domain
)
{
    ULONG Index;

    for (Index = 0; Index < Number; Index++) {
        SvmUnprepareDomainSpace(&Domain[Index]);
    }

    CmFreeNonPagedMemory(Domain);
}

PSVM_DOMAIN NTAPI
SvmAllocateDomain(
    __in ULONG Number
)
{
    NTSTATUS Status;
    PSVM_DOMAIN Domain;
    ULONG Succeed;
    ULONG Index;

    Domain = CmAllocateNonPagedMemory(Number * sizeof(SVM_DOMAIN));

    if (NULL != Domain) {
        for (Index = 0; Index < Number; Index++) {

            Status = SvmPrepareDomainSpace(&Domain[Index]);

            if (FALSE == NT_SUCCESS(Status)) {
                break;
            }
        }

        if (FALSE == NT_SUCCESS(Status)) {
            Succeed = Index;

            for (Index = 0; Index < Succeed; Index++) {
                SvmUnprepareDomainSpace(&Domain[Index]);
            }

            CmFreeNonPagedMemory(Domain);
            Domain = NULL;
        }
    }

    return Domain;
}

NTSTATUS NTAPI
SvmFirstEntry(
    __in PSVM_DOMAIN Domain,
    __in PGUEST_CONTEXT Context
)
{
    Domain->Features = SvmGetFeatures();

    if (0 == (Domain->Features & SVM_FEATURE_SUPPORT) ||
        0 == (Domain->Features & SVM_FEATURE_ENABLE)) {
        return STATUS_NOT_SUPPORTED;
    }
    
    return STATUS_SUCCESS;
}

NTSTATUS NTAPI
SvmTaskDispatcher(
    __in PSVM_DOMAIN Domain,
    __in ULONG TaskCode,
    __inout_opt PVOID Context
)
{
    NTSTATUS Status;
    PSVM_DOMAIN CurrentDomain;
    
    CurrentDomain = &Domain[KeGetCurrentProcessorNumber()];

    switch (TaskCode) {
    case TASK_STARTUP:
        Status = SvmPrepareStartup(CurrentDomain);
        LogSyncPrint("svm startup < %p > | < %08x >\n", CurrentDomain, Status);
        break;
    case TASK_SHUTDOWN:
        LogSyncPrint("svm shutdown < %p >\n", CurrentDomain);
        Status = STATUS_SUCCESS;
        break;
    default:
        Status = STATUS_INVALID_PARAMETER;
        break;
    }

    return Status;
}