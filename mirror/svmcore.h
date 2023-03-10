#ifndef _SVMCORE_H_
#define _SVMCORE_H_

#ifdef __cplusplus
extern "C" {
#endif

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

VOID NTAPI
SvmUnprepareDomainSpace(
    __in PSVM_DOMAIN Domain,
    __in ULONG Number);

PSVM_DOMAIN NTAPI
SvmPrepareDomainSpace(
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
