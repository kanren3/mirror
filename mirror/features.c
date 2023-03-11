#include "idefs.h"
#include "features.h"

ULONG NTAPI
FeaGetProcessorType()
{
    ULONG i, Feature[4];

    ULONG Selector[][4] = {
        { 0x756E6547, 0x6C65746E, 0x49656E69, PROCESSOR_INTEL },
        { 0x68747541, 0x444D4163, 0x69746E65, PROCESSOR_AMD }
    };

    __ins_cpuidex(0x00000000, 0, &Feature[0]);

    for (i = 0; i < RTL_NUMBER_OF(Selector); i++) {
        if (0 == memcmp(&Feature[1], Selector[i], 12)) {
            return Selector[i][3];
        }
    }

    return PROCESSOR_OTHERS;
}

ULONG NTAPI
FeaGetProcessorNumber()
{
    return KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);
}

VOID NTAPI
FeaGetXFeatureInfo(
    __out PXFEATURE_INFO XFeatureInfo
)
{
    CPU_INFO CpuInfo;

    __ins_cpuidex(0x0000000D, 0, &CpuInfo.Eax);

    XFeatureInfo->EnabledSizeMax = CpuInfo.Ebx;
    XFeatureInfo->SupportedSizeMax = CpuInfo.Ecx;
    XFeatureInfo->SupportedLowMask = CpuInfo.Eax;
    XFeatureInfo->SupportedUpperMask = CpuInfo.Edx;
}

ULONG NTAPI
FeaGetVmxFeature()
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
FeaGetSvmFeature()
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
FeaGetSvmAsidNumber()
{
    CPU_INFO CpuInfo;

    __ins_cpuidex(0x80000001, 0, &CpuInfo.Eax);

    return CpuInfo.Ebx;
}