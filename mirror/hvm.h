#ifndef _HVM_H_
#define _HVM_H_

#ifdef __cplusplus
extern "C" {
#endif
#define VMM_STATE_NONE  0x00000000
#define VMM_STATE_ROOT  0x00000001
#define VMM_STATE_GUEST 0x00000002

typedef struct _HVM_MANAGER {
    union {
        PSVM_MANAGER Svm;
        PVMX_MANAGER Vmx;
    };

    ULONG ManagerState;
    ULONG ManagerType;

    ULONG ProcessorNumber;

    ULONG XFeatureEnabledSizeMax;
    ULONG XFeatureSupportedSizeMax;
    ULONG XFeatureSupportedLowMask;
    ULONG XFeatureSupportedUpperMask;

    ULONG_PTR RootDirectoryTableBase;
} HVM_MANAGER, *PHVM_MANAGER;

NTSTATUS NTAPI
HvmInitializeManager();

#ifdef __cplusplus
}
#endif

#endif
