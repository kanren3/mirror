#ifndef _SVM_H_
#define _SVM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_MSR_SWAP 0x100

typedef struct _MSR_SWAP_REGION {
    ULONG Count;
    ULONG Key[MAX_MSR_SWAP];
    ULONGLONG Value[MAX_MSR_SWAP];
} MSR_SWAP_REGION, *PMSR_SWAP_REGION;

typedef struct _SVM_GUEST {

    //
    // GuestOS CPU Id
    // General Purpose Register
    // Segment Register
    // Control Register
    // Debug Register
    // Basic Model Specific Register
    // Extended Control Register
    // Global Descriptor Table
    // Local Descriptor Table
    // Interrupt Descriptor Table
    // XSave Area
    // Exception Control Bitmap
    // I/O Control Bitmap
    // MSR Control Bitmap
    // Execution Control Field
    // MSR Store and Load
    // 

    GUEST_CONTEXT Context;

} SVM_GUEST, *PSVM_GUEST;

typedef struct _SVM_STACK {
    UCHAR Body[KERNEL_LARGE_STACK_SIZE - sizeof(GUEST_CONTEXT)];
    GUEST_CONTEXT Context;
} SVM_STACK, *PSVM_STACK;

typedef struct _SVM_DOMAIN {
    PVOID Self;
    PUCHAR Vmcb;
    PUCHAR Vmhs;
    PUCHAR Msrmap;
    PUCHAR Iomap;
    PUCHAR Page;
    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;
    SVM_STACK Stack;
} SVM_DOMAIN, *PSVM_DOMAIN;

#ifdef __cplusplus
}
#endif

#endif
