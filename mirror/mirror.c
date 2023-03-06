#include "idefs.h"
#include "logger.h"
#include "thunk.h"

VOID NTAPI
DriverUnload(
    __in PDRIVER_OBJECT DriverObject)
{
    TuGenericCall(TASK_SHUTDOWN, NULL);
    TuUninitialize();
    LogUninitialize();
}

NTSTATUS NTAPI
DriverEntry(
    __in PDRIVER_OBJECT DriverObject,
    __in PUNICODE_STRING RegistryPath)
{
    NTSTATUS Status = STATUS_SUCCESS;

    DriverObject->DriverUnload = DriverUnload;

    Status = LogInitialize(1);

    if (FALSE == NT_SUCCESS(Status)) {
        return Status;
    }

    Status = TuInitialize();

    if (FALSE == NT_SUCCESS(Status)) {
        LogUninitialize();
        return Status;
    }

    TuGenericCall(TASK_STARTUP, NULL);
    return STATUS_SUCCESS;
}