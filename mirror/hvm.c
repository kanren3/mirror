#include "midefs.h"
#include "logger.h"
#include "hvm.h"

ULONG HvProcessorNumber;
ULONG HvProcessorType;

ULONG NTAPI
HvGetProcessorNumber()
{
    return KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);
}

ULONG NTAPI
HvGetProcessorType()
{
    ULONG i, Feature[4];

    ULONG Selector[][4] = {
        { 0x756E6547, 0x6C65746E, 0x49656E69, MACHINE_INTEL },
        { 0x68747541, 0x444D4163, 0x69746E65, MACHINE_AMD }
    };

    __ins_cpuidex(0, 0, &Feature[0]);

    for (i = 0; i < RTL_NUMBER_OF(Selector); i++) {
        if (0 == memcmp(&Feature[1], Selector[i], 12)) {
            return Selector[i][3];
        }
    }

    return MACHINE_NONE;
}

BOOLEAN NTAPI
HvCheckVmxSupport()
{
    CPU_INFO CpuInfo;
    ULONGLONG Value;

    __ins_cpuidex(1, 0, &CpuInfo.Eax);
    if (0 == (0x00000020 & CpuInfo.Ecx)) {
        return FALSE;
    }

    Value = __ins_rdmsr(MSR_FEATURE_CONTROL);
    if (0 == (0x00000004 & Value)) {
        return FALSE;
    }

    return TRUE;
}

BOOLEAN NTAPI
HvCheckSvmSupport()
{
    CPU_INFO CpuInfo;
    ULONGLONG Value;

    __ins_cpuidex(0x80000001, 0, &CpuInfo.Eax);
    if (0 == (0x00000004 & CpuInfo.Ecx)) {
        return FALSE;
    }

    Value = __ins_rdmsr(MSR_VM_CR);
    if (0 != (0x00000010 & Value)) {
        return FALSE;
    }

    return TRUE;
}

NTSTATUS NTAPI
HvInitializeProcessor()
{
    BOOLEAN Support;

    HvProcessorType = HvGetProcessorType();

    if (MACHINE_NONE == HvProcessorType) {
        return STATUS_NOT_SUPPORTED;
    }

    if (MACHINE_INTEL == HvProcessorType) {
        Support = HvCheckVmxSupport();
    }
    else {
        Support = HvCheckSvmSupport();
    }

    if (FALSE == Support) {
        return STATUS_NOT_SUPPORTED;
    }

    HvProcessorNumber = HvGetProcessorNumber();

    return STATUS_SUCCESS;
}