#ifndef _COMMON_H_
#define _COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

PVOID NTAPI
CmAllocateNonPagedMemory(
    __in SIZE_T NumberOfBytes);

VOID NTAPI
CmFreeNonPagedMemory(
    __in PVOID Pointer);

PVOID NTAPI
CmAllocateContiguousMemory(
    __in SIZE_T NumberOfBytes);

VOID NTAPI
CmFreeContiguousMemory(
    __in PVOID BaseAddress);

ULONG_PTR NTAPI
CmGetDirectoryTableBase(
    __in PEPROCESS Process);

NTSTATUS NTAPI
CmBuildPageDirectory(
    __out PVOID DirectoryPointer
);

#ifdef __cplusplus
}
#endif

#endif
