#include "midefs.h"
#include "logger.h"
#include "features.h"
#include "hvm.h"

ULONG HvProcessorNumber;
ULONG HvMachineType;

NTSTATUS NTAPI
HvInitializeProcessor()
{
    HvMachineType = FeGetMachineType();

    if (MACHINE_NONE != HvMachineType) {
        return STATUS_NOT_SUPPORTED;
    }

    HvProcessorNumber = KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);

    return STATUS_SUCCESS;
}