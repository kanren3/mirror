#include "midefs.h"
#include "features.h"

ULONG NTAPI
FeGetMachineType()
{
    ULONG i, Feature[4];

    ULONG Selector[][4] = {
        { 0x756E6547, 0x6C65746E, 0x49656E69, MACHINE_INTEL },
        { 0x68747541, 0x444D4163, 0x69746E65, MACHINE_AMD }
    };

    __ins_cpuidex(0x00000000, 0, &Feature[0]);

    for (i = 0; i < RTL_NUMBER_OF(Selector); i++) {
        if (0 == memcmp(&Feature[1], Selector[i], 12)) {
            return Selector[i][3];
        }
    }

    return MACHINE_NONE;
}

ULONG NTAPI
FeGetXFeatureEnabledSizeMax()
{
    CPU_INFO CpuInfo;
    __ins_cpuidex(0x0000000D, 0, &CpuInfo.Eax);
    return CpuInfo.Ebx;
}

ULONG NTAPI
FeGetXFeatureSupportedSizeMax()
{
    CPU_INFO CpuInfo;
    __ins_cpuidex(0x0000000D, 0, &CpuInfo.Eax);
    return CpuInfo.Ecx;
}

ULONG NTAPI
FeGetXFeatureSupportedLowMask()
{
    CPU_INFO CpuInfo;
    __ins_cpuidex(0x0000000D, 0, &CpuInfo.Eax);
    return CpuInfo.Eax;
}

ULONG NTAPI
FeGetXFeatureSupportedUpperMask()
{
    CPU_INFO CpuInfo;
    __ins_cpuidex(0x0000000D, 0, &CpuInfo.Eax);
    return CpuInfo.Edx;
}

ULONG NTAPI
FeGetVmxFeature()
{
    ULONG Feature = 0;
    CPU_INFO CpuInfo;
    ULONGLONG Value;

    __ins_cpuidex(0x00000001, 0, &CpuInfo.Eax);
    if (0 != (0x00000020 & CpuInfo.Ecx)) {
        Feature |= VMX_FEATURE_SUPPORT;
    }

    Value = __ins_rdmsr(MSR_FEATURE_CONTROL);
    if (0 != (0x00000004 & Value)) {
        Feature |= VMX_FEATURE_ENABLE;
    }

    return TRUE;
}

ULONG NTAPI
FeGetSvmFeature()
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

ULONG NTAPI
FeGetSvmAsidNumber()
{
    CPU_INFO CpuInfo;
    __ins_cpuidex(0x80000001, 0, &CpuInfo.Eax);
    return CpuInfo.Ebx;
}