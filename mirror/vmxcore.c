#include "idefs.h"
#include "logger.h"
#include "vmxcore.h"
#include "thunk.h"

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