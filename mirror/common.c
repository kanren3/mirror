#include "idefs.h"
#include "common.h"

PVOID NTAPI
CmAllocateNonPagedMemory(
    __in SIZE_T NumberOfBytes
)
{
    PVOID Pointer = NULL;

    Pointer = ExAllocatePoolWithTag(NonPagedPool,
                                    NumberOfBytes,
                                    'mmoC');

    if (NULL != Pointer) {
        RtlZeroMemory(Pointer, NumberOfBytes);
    }

    return Pointer;
}

VOID NTAPI
CmFreeNonPagedMemory(
    __in PVOID Pointer
)
{
    ExFreePoolWithTag(Pointer, 'mmoC');
}

PVOID NTAPI
CmAllocateContiguousMemory(
    __in SIZE_T NumberOfBytes
)
{
    PVOID BaseAddress = NULL;
    PHYSICAL_ADDRESS Lowest = { 0 };
    PHYSICAL_ADDRESS Highest = { 0 };
    PHYSICAL_ADDRESS Boundary = { 0 };

#ifndef _WIN64
    Highest.QuadPart = MAXULONG32;
#else
    Highest.QuadPart = MAXULONG64;
#endif

    BaseAddress = MmAllocateContiguousMemorySpecifyCache(NumberOfBytes,
                                                         Lowest,
                                                         Highest,
                                                         Boundary,
                                                         MmCached);

    if (NULL != BaseAddress) {
        RtlZeroMemory(BaseAddress, NumberOfBytes);
    }

    return BaseAddress;
}

VOID NTAPI
CmFreeContiguousMemory(
    __in PVOID BaseAddress
)
{
    MmFreeContiguousMemory(BaseAddress);
}

ULONG_PTR NTAPI
CmGetDirectoryTableBase(
    __in PEPROCESS Process
)
{
    ULONG_PTR DirectoryTableBase = 0;

#ifndef _WIN64
    DirectoryTableBase = *(PULONG_PTR)((ULONG_PTR)Process + 0x18);
#else
    DirectoryTableBase = *(PULONG_PTR)((ULONG_PTR)Process + 0x28);
#endif

    return DirectoryTableBase;
}