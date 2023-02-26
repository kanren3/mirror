#ifndef _FEATURES_H_
#define _FEATURES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MACHINE_NONE  0x00000000
#define MACHINE_INTEL 0x00000001
#define MACHINE_AMD   0x00000002

#define VMX_FEATURE_SUPPORT 0x00000001
#define VMX_FEATURE_ENABLE  0x00000002

#define SVM_FEATURE_SUPPORT       0x00000001
#define SVM_FEATURE_ENABLE        0x00000002
#define SVM_FEATURE_NPT           0x00000004
#define SVM_FEATURE_VMCB_CLEAN    0x00000008
#define SVM_FEATURE_FLUSH_BY_ASID 0x00000010

ULONG NTAPI
FeGetMachineType();

ULONG NTAPI
FeGetXFeatureEnabledSizeMax();

ULONG NTAPI
FeGetXFeatureSupportedSizeMax();

ULONG NTAPI
FeGetXFeatureSupportedLowMask();

ULONG NTAPI
FeGetXFeatureSupportedUpperMask();

ULONG NTAPI
FeGetVmxFeature();

ULONG NTAPI
FeGetSvmFeature();

ULONG NTAPI
FeGetSvmAsidNumber();

#ifdef __cplusplus
}
#endif

#endif
