#include "idefs.h"
#include "logger.h"
#include "common.h"
#include "features.h"
#include "hvm.h"

typedef struct _SVM_DOMAIN {
    PUCHAR Vmcb;
    PUCHAR Vmhs;
    PUCHAR VmmStack;
    PUCHAR MsrBitmap;
    PUCHAR IoBitmap;
    PUCHAR PageDirectory;
    PUCHAR XSaveArea;

    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;

    ULONG_PTR Cr0;
    ULONG_PTR Cr3;
    ULONG_PTR Cr4;
} SVM_DOMAIN, *PSVM_DOMAIN;

typedef struct _HVM_MANAGER {
    union {
        PVOID SvmDomain;
        PVOID VmxDomain;
    };

    ULONG ProcessorNumber;
    ULONG MachineType;
    ULONG ControlKey;
} HVM_MANAGER, *PHVM_MANAGER;


PHVM_MANAGER HvmVirtualMachineManager = NULL;

NTSTATUS NTAPI
HvmInitialize()
{

    return STATUS_SUCCESS;
}