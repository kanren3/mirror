#include "idefs.h"
#include "common.h"
#include "logger.h"
#include "vmxcore.h"
#include "thunk.h"

VOID NTAPI
VmxUnprepareDomainSpace(
    __in PVMX_DOMAIN Domain,
    __in ULONG Number)
{
    ULONG i;

    for (i = 0; i < Number; i++) {
        if (NULL != Domain[i].Vmon) {
            CmFreeContiguousMemory(Domain[i].Vmon);
        }

        if (NULL != Domain[i].Vmcs) {
            CmFreeContiguousMemory(Domain[i].Vmcs);
        }

        if (NULL != Domain[i].MsrBitmap) {
            CmFreeContiguousMemory(Domain[i].MsrBitmap);
        }

        if (NULL != Domain[i].IoBitmap) {
            CmFreeContiguousMemory(Domain[i].IoBitmap);
        }

        if (NULL != Domain[i].VmmStack) {
            CmFreeNonPagedMemory(Domain[i].VmmStack);
        }

        if (NULL != Domain[i].Tss) {
            CmFreeNonPagedMemory(Domain[i].Tss);
        }

        if (NULL != Domain[i].XSaveArea) {
            CmFreeNonPagedMemory(Domain[i].XSaveArea);
        }

        if (NULL != Domain[i].Gdtr.Base) {
            CmFreeNonPagedMemory(Domain[i].Gdtr.Base);
        }

        if (NULL != Domain[i].Idtr.Base) {
            CmFreeNonPagedMemory(Domain[i].Idtr.Base);
        }
    }

    CmFreeNonPagedMemory(Domain);
}

PVMX_DOMAIN NTAPI
VmxPrepareDomainSpace(
    __in ULONG Number)
{
    ULONG i, j;
    NTSTATUS Status;
    PVMX_DOMAIN Domain;

    Domain = CmAllocateNonPagedMemory(Number * sizeof(VMX_DOMAIN));

    if (NULL == Domain) {
        return NULL;
    }

    for (i = 0; i < Number; i++) {
        Domain[i].Vmon = CmAllocateContiguousMemory(PAGE_SIZE);

        if (NULL == Domain[i].Vmon) {
            goto Cleanup;
        }

        Domain[i].Vmcs = CmAllocateContiguousMemory(PAGE_SIZE);

        if (NULL == Domain[i].Vmcs) {
            goto Cleanup;
        }

        Domain[i].MsrBitmap = CmAllocateContiguousMemory(PAGE_SIZE * 2);

        if (NULL == Domain[i].MsrBitmap) {
            goto Cleanup;
        }

        Domain[i].IoBitmap = CmAllocateContiguousMemory(PAGE_SIZE * 2);

        if (NULL == Domain[i].IoBitmap) {
            goto Cleanup;
        }

        Domain[i].VmmStack = CmAllocateNonPagedMemory(PAGE_SIZE);

        if (NULL == Domain[i].VmmStack) {
            goto Cleanup;
        }

        Domain[i].Tss = CmAllocateNonPagedMemory(PAGE_SIZE);

        if (NULL == Domain[i].Tss) {
            goto Cleanup;
        }

        Domain[i].XSaveArea = CmAllocateNonPagedMemory(PAGE_SIZE);

        if (NULL == Domain[i].XSaveArea) {
            goto Cleanup;
        }

        Domain[i].Gdtr.Base = CmAllocateNonPagedMemory(PAGE_SIZE);

        if (NULL == Domain[i].Gdtr.Base) {
            goto Cleanup;
        }

        Domain[i].Idtr.Base = CmAllocateNonPagedMemory(PAGE_SIZE);

        if (NULL == Domain[i].Idtr.Base) {
            goto Cleanup;
        }
    }

    return Domain;

Cleanup:

    VmxUnprepareDomainSpace(Domain, i + 1);

    return NULL;
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
        LogSyncPrint("vmx startup < %p >\n", Domain);
        Status = STATUS_SUCCESS;
        break;
    case TASK_SHUTDOWN:
        LogSyncPrint("vmx shutdown < %p >\n", Domain);
        Status = STATUS_SUCCESS;
        break;
    default:
        Status = STATUS_INVALID_PARAMETER;
        break;
    }

    return Status;
}