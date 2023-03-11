#include "idefs.h"
#include "common.h"
#include "logger.h"
#include "vmxcore.h"
#include "thunk.h"

VOID NTAPI
VmxUnprepareDomainSpace(
    __in PVMX_DOMAIN Domain)
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
    __in PVMX_DOMAIN Domain)
{
    Domain->Vmon = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == Domain->Vmon) {
        goto Cleanup;
    }

    Domain->Vmcs = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == Domain->Vmcs) {
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

    Domain->VmmStack = CmAllocateNonPagedMemory(PAGE_SIZE);

    if (NULL == Domain->VmmStack) {
        goto Cleanup;
    }

    Domain->Tss = CmAllocateNonPagedMemory(PAGE_SIZE);

    if (NULL == Domain->Tss) {
        goto Cleanup;
    }

    Domain->XSaveArea = CmAllocateNonPagedMemory(PAGE_SIZE);

    if (NULL == Domain->XSaveArea) {
        goto Cleanup;
    }

    Domain->Gdtr.Base = CmAllocateNonPagedMemory(PAGE_SIZE);

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
    __in PVMX_DOMAIN Domain)
{
    ULONG Index;

    for (Index = 0; Index < Number; Index++) {
        VmxUnprepareDomainSpace(&Domain[Index]);
    }

    CmFreeNonPagedMemory(Domain);
}

PVMX_DOMAIN NTAPI
VmxAllocateDomain(
    __in ULONG Number)
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

NTSTATUS NTAPI
VmxTaskDispatcher(
    __in PVMX_DOMAIN Domain,
    __in ULONG TaskCode,
    __inout_opt PVOID Context)
{
    NTSTATUS Status;

    switch (TaskCode) {
    case TASK_STARTUP:
        LogSyncPrint("vmx startup < %p >\n", &Domain[KeGetCurrentProcessorNumber()]);
        Status = STATUS_SUCCESS;
        break;
    case TASK_SHUTDOWN:
        LogSyncPrint("vmx shutdown < %p >\n", &Domain[KeGetCurrentProcessorNumber()]);
        Status = STATUS_SUCCESS;
        break;
    default:
        Status = STATUS_INVALID_PARAMETER;
        break;
    }

    return Status;
}