#ifndef _SVM_H_
#define _SVM_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SVM_MANAGER {
    ULONG Feature;

    PUCHAR Stack;
    PUCHAR Vmcb;
    PUCHAR Vmhs;
    PUCHAR Msrmap;
    PUCHAR Iomap;
    PUCHAR PageTable;

    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;

    ULONG_PTR Cr0;
    ULONG_PTR Cr3;
    ULONG_PTR Cr4;
} SVM_MANAGER, *PSVM_MANAGER;

#ifdef __cplusplus
}
#endif

#endif
