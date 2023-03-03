#ifndef _HVM_H_
#define _HVM_H_

#ifdef __cplusplus
extern "C" {
#endif
#define VMM_STATE_NONE  0x00000000
#define VMM_STATE_ROOT  0x00000001
#define VMM_STATE_GUEST 0x00000002

typedef struct _PAGE_DIRECTORY {
    PVOID DirectoryPointer;
    PHYSICAL_ADDRESS DirectoryBase;
} PAGE_DIRECTORY, *PPAGE_DIRECTORY;

typedef struct _HVM_MANAGER {
    ULONG CallKey;
    ULONG ProcessorNumber;
    ULONG ProcessorType;

    PVOID ControlDomain;

    PAGE_DIRECTORY HostPageDirectory;
} HVM_MANAGER, *PHVM_MANAGER;

NTSTATUS NTAPI
HvmInitialize(
    __in ULONG CallKey);

VOID NTAPI
HvmUninitialize();

#ifdef __cplusplus
}
#endif

#endif
