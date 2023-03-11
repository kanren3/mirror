#include "idefs.h"
#include "common.h"
#include "logger.h"
#include "svmcore.h"
#include "thunk.h"

VOID NTAPI
SvmUnprepareDomainSpace(
    __in PSVM_DOMAIN Domain)
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
    __in PSVM_DOMAIN Domain)
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

    return STATUS_INSUFFICIENT_RESOURCES;
}

VOID NTAPI
SvmFreeDomain(
    __in ULONG Number,
    __in PSVM_DOMAIN Domain)
{
    ULONG Index;

    for (Index = 0; Index < Number; Index++) {
        SvmUnprepareDomainSpace(&Domain[Index]);
    }

    CmFreeNonPagedMemory(Domain);
}

PSVM_DOMAIN NTAPI
SvmAllocateDomain(
    __in ULONG Number)
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
SvmTaskDispatcher(
    __in PSVM_DOMAIN Domain,
    __in ULONG TaskCode,
    __inout_opt PVOID Context)
{
    NTSTATUS Status;

    switch (TaskCode) {
    case TASK_STARTUP:
        LogSyncPrint("svm startup < %p >\n", &Domain[KeGetCurrentProcessorNumber()]);
        Status = STATUS_SUCCESS;
        break;
    case TASK_SHUTDOWN:
        LogSyncPrint("svm shutdown < %p >\n", &Domain[KeGetCurrentProcessorNumber()]);
        Status = STATUS_SUCCESS;
        break;
    default:
        Status = STATUS_INVALID_PARAMETER;
        break;
    }

    return Status;
}