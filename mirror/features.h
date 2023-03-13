#ifndef _FEATURES_H_
#define _FEATURES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROCESSOR_OTHERS          0x00000000
#define PROCESSOR_INTEL           0x00000001
#define PROCESSOR_AMD             0x00000002

ULONG NTAPI
FeaGetProcessorType();

ULONG NTAPI
FeaGetProcessorNumber();

ULONG NTAPI
FeaGetXFeatureSupportedSizeMax();

#ifdef __cplusplus
}
#endif

#endif
