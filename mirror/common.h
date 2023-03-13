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
    __out PVOID DirectoryPointer);

VOID WINAPI
CmBuildI386GdtEntry(
    __out PVOID Gdt,
    __in ULONG Selector,
    __in ULONG Base,
    __in ULONG Limit,
    __in ULONG Type,
    __in ULONG Dpl,
    __in BOOLEAN DefaultBig);

VOID WINAPI
CmBuildAmd64GdtEntry(
    __out PVOID Gdt,
    __in ULONG Selector,
    __in ULONGLONG Base,
    __in ULONG Limit,
    __in ULONG Type,
    __in ULONG Dpl,
    __in BOOLEAN LongMode,
    __in BOOLEAN DefaultBig);

#ifdef __cplusplus
}
#endif

#endif
