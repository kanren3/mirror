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

NTSTATUS NTAPI
CmBuildPageDirectory(
    __out PVOID DirectoryPointer
)
{
    PVOID RootDirectoryPointer;
    PHYSICAL_ADDRESS RootDirectoryBase;

    RootDirectoryBase.QuadPart = CmGetDirectoryTableBase(PsInitialSystemProcess) & ~0xFFF;

    RootDirectoryPointer = MmGetVirtualForPhysical(RootDirectoryBase);

    if (NULL == RootDirectoryPointer) {
        return STATUS_UNSUCCESSFUL;
    }

    RtlCopyMemory(DirectoryPointer, RootDirectoryPointer, PAGE_SIZE);

    return STATUS_SUCCESS;
}

VOID WINAPI
CmBuildI386GdtEntry(
    __out PVOID Gdt,
    __in ULONG Selector,
    __in ULONG Base,
    __in ULONG Limit,
    __in ULONG Type,
    __in ULONG Dpl,
    __in BOOLEAN DefaultBig
)
{
    PKGDTENTRY32 GdtEntry;
    KGDT_BASE32 GdtBase;
    KGDT_LIMIT GdtLimit;

    GdtEntry = (PKGDTENTRY32)((PUCHAR)Gdt + (Selector & ~7));

    GdtBase.Base = Base;
    GdtEntry->BaseLow = GdtBase.BaseLow;
    GdtEntry->Bits.BaseMiddle = GdtBase.BaseMiddle;
    GdtEntry->Bits.BaseHigh = GdtBase.BaseHigh;

    if (Limit > (1 << 20)) {
        GdtLimit.Limit = Limit >> 12;
        GdtEntry->Bits.Granularity = 1;
    }
    else {
        GdtLimit.Limit = (ULONG)Limit;
        GdtEntry->Bits.Granularity = 0;
    }

    GdtEntry->LimitLow = GdtLimit.LimitLow;
    GdtEntry->Bits.LimitHigh = GdtLimit.LimitHigh;

    GdtEntry->Bits.Present = 1;
    GdtEntry->Bits.Type = Type;
    GdtEntry->Bits.Dpl = Dpl;
    GdtEntry->Bits.DefaultBig = DefaultBig;
    GdtEntry->Bits.System = 0;
}

VOID WINAPI
CmBuildAmd64GdtEntry(
    __out PVOID Gdt,
    __in ULONG Selector,
    __in ULONGLONG Base,
    __in ULONG Limit,
    __in ULONG Type,
    __in ULONG Dpl,
    __in BOOLEAN LongMode,
    __in BOOLEAN DefaultBig
)
{
    PKGDTENTRY64 GdtEntry;
    KGDT_BASE64 GdtBase;
    KGDT_LIMIT GdtLimit;

    GdtEntry = (PKGDTENTRY64)((PUCHAR)Gdt + (Selector & ~7));

    GdtBase.Base = Base;
    GdtEntry->BaseLow = GdtBase.BaseLow;
    GdtEntry->Bits.BaseMiddle = GdtBase.BaseMiddle;
    GdtEntry->Bits.BaseHigh = GdtBase.BaseHigh;

    if (FALSE != LongMode) {
        GdtEntry->MustBeZero = 0;
        GdtEntry->BaseUpper = GdtBase.BaseUpper;
        GdtEntry->Bits.LongMode = 1;
    }
    else {
        GdtEntry->Bits.LongMode = 0;
    }

    if (Limit > (1 << 20)) {
        GdtLimit.Limit = Limit >> 12;
        GdtEntry->Bits.Granularity = 1;
    }
    else {
        GdtLimit.Limit = (ULONG)Limit;
        GdtEntry->Bits.Granularity = 0;
    }

    GdtEntry->LimitLow = GdtLimit.LimitLow;
    GdtEntry->Bits.LimitHigh = GdtLimit.LimitHigh;

    GdtEntry->Bits.Present = 1;
    GdtEntry->Bits.Type = Type;
    GdtEntry->Bits.Dpl = Dpl;
    GdtEntry->Bits.DefaultBig = DefaultBig;
    GdtEntry->Bits.System = 0;
}