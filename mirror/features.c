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

ULONG NTAPI
FeaGetXFeatureSupportedSizeMax()
{
    CPU_INFO CpuInfo;

    __ins_cpuidex(0x0000000D, 0, &CpuInfo.Eax);

    return CpuInfo.Ecx;
}