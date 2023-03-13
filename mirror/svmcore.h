#ifndef _SVMCORE_H_
#define _SVMCORE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SVM_FEATURE_SUPPORT       0x00000001
#define SVM_FEATURE_ENABLE        0x00000002
#define SVM_FEATURE_NPT           0x00000004
#define SVM_FEATURE_VMCB_CLEAN    0x00000008
#define SVM_FEATURE_FLUSH_BY_ASID 0x00000010

typedef struct _SVM_DOMAIN {
    PUCHAR Vmcb;
    PUCHAR Vmhs;
    PUCHAR VmmStack;
    PUCHAR MsrBitmap;
    PUCHAR IoBitmap;
    PUCHAR Tss;
    PUCHAR XSaveArea;

    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;

    ULONG_PTR Cr0;
    ULONG_PTR Cr3;
    ULONG_PTR Cr4;

    ULONGLONG Features;
} SVM_DOMAIN, *PSVM_DOMAIN;

NTSTATUS NTAPI
SvmPrepareStartup(
    __in PSVM_DOMAIN Domain);

VOID NTAPI
SvmFreeDomain(
    __in ULONG Number,
    __in PSVM_DOMAIN Domain);

PSVM_DOMAIN NTAPI
SvmAllocateDomain(
    __in ULONG Number);

NTSTATUS NTAPI
SvmTaskDispatcher(
    __in PSVM_DOMAIN Domain,
    __in ULONG TaskCode,
    __inout_opt PVOID Context);

#ifdef __cplusplus
}
#endif

#endif
