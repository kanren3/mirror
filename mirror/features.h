#ifndef _FEATURES_H_
#define _FEATURES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROCESSOR_OTHERS 0x00000000
#define PROCESSOR_INTEL  0x00000001
#define PROCESSOR_AMD    0x00000002

#define VMX_FEATURE_SUPPORT 0x00000001
#define VMX_FEATURE_ENABLE  0x00000002

#define SVM_FEATURE_SUPPORT       0x00000001
#define SVM_FEATURE_ENABLE        0x00000002
#define SVM_FEATURE_NPT           0x00000004
#define SVM_FEATURE_VMCB_CLEAN    0x00000008
#define SVM_FEATURE_FLUSH_BY_ASID 0x00000010

typedef struct _XFEATURE_INFO {
    ULONG EnabledSizeMax;
    ULONG SupportedSizeMax;
    ULONG SupportedLowMask;
    ULONG SupportedUpperMask;
} XFEATURE_INFO, *PXFEATURE_INFO;

typedef struct _VMX_FEATURES {
    ULONG Flags;

    VMX_BASIC BasicInfo;

    ULARGE_INTEGER PinFixed;
    ULARGE_INTEGER PrimaryFixed;
    ULARGE_INTEGER SecondaryFixed;
    ULARGE_INTEGER ExitFixed;
    ULARGE_INTEGER EntryFixed;

} VMX_FEATURES, *PVMX_FEATURES;

typedef struct _VMX_FEATURES {
    ULONG Flags;

    VMX_BASIC BasicInfo;

    ULARGE_INTEGER PinFixed;
    ULARGE_INTEGER PrimaryFixed;
    ULARGE_INTEGER SecondaryFixed;
    ULARGE_INTEGER ExitFixed;
    ULARGE_INTEGER EntryFixed;

} VMX_FEATURES, *PVMX_FEATURES;


ULONG NTAPI
GetVmManagerType();

ULONG NTAPI
GetXFeatureEnabledSizeMax();

ULONG NTAPI
GetXFeatureSupportedSizeMax();

ULONG NTAPI
GetXFeatureSupportedLowMask();

ULONG NTAPI
GetXFeatureSupportedUpperMask();

ULONG NTAPI
GetVmxFeature();

ULONG NTAPI
GetSvmFeature();

ULONG NTAPI
GetSvmAsidNumber();

#ifdef __cplusplus
}
#endif

#endif
