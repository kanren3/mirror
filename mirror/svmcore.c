#include "idefs.h"
#include "logger.h"
#include "svmcore.h"
#include "thunk.h"

NTSTATUS NTAPI
SvmTaskDispatcher(
    __in PSVM_DOMAIN Domain,
    __in ULONG TaskCode,
    __inout_opt PVOID Context)
{
    NTSTATUS Status;

    switch (TaskCode) {
    case TASK_STARTUP:
        LogSyncPrint("svm startup < %p >\n", Domain);
        Status = STATUS_SUCCESS;
        break;
    case TASK_SHUTDOWN:
        LogSyncPrint("svm shutdown < %p >\n", Domain);
        Status = STATUS_SUCCESS;
        break;
    default:
        Status = STATUS_INVALID_PARAMETER;
        break;
    }

    return Status;
}