#include "idefs.h"
#include "logger.h"
#include "hvm.h"

VOID NTAPI
DriverUnload(
    __in PDRIVER_OBJECT DriverObject)
{
    LogUninitialize();
}

NTSTATUS NTAPI
DriverEntry(
    __in PDRIVER_OBJECT DriverObject,
    __in PUNICODE_STRING RegistryPath)
{
    NTSTATUS Status = STATUS_SUCCESS;

    DriverObject->DriverUnload = DriverUnload;

    Status = HvInitializeProcessor();

    if (FALSE == NT_SUCCESS(Status)) {
        return Status;
    }

    Status = LogInitialize(1);

    if (FALSE == NT_SUCCESS(Status)) {
        return Status;
    }

    return STATUS_SUCCESS;
}