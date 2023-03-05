#include "idefs.h"
#include "logger.h"
#include "common.h"
#include "features.h"
#include "svmcore.h"
#include "vmxcore.h"
#include "thunk.h"

ULONG TuProcessorNumber;
ULONG TuProcessorType;

PVOID TuControllerDomain;
PVOID TuPageDirectoryPointer;

NTSTATUS NTAPI
TuBuildHostPageDirectory(
    __out PVOID DirectoryPointer)
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

NTSTATUS NTAPI
TuInitialize()
{
    NTSTATUS Status;

    TuProcessorType = FeaGetProcessorType();

    TuProcessorNumber = FeaGetProcessorNumber();

    if (PROCESSOR_OTHERS == TuProcessorType) {
        return STATUS_NOT_SUPPORTED;
    }

    TuPageDirectoryPointer = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == TuPageDirectoryPointer) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = TuBuildHostPageDirectory(TuPageDirectoryPointer);

    if (FALSE == NT_SUCCESS(Status)) {
        CmFreeContiguousMemory(TuPageDirectoryPointer);
        return Status;
    }

    if (PROCESSOR_AMD == TuProcessorType) {
        TuControllerDomain = CmAllocateNonPagedMemory(TuProcessorNumber * sizeof(SVM_DOMAIN));
    }
    else {
        TuControllerDomain = CmAllocateNonPagedMemory(TuProcessorNumber * sizeof(VMX_DOMAIN));
    }

    if (NULL == TuControllerDomain) {
        CmFreeContiguousMemory(TuPageDirectoryPointer);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    return Status;
}

VOID NTAPI
TuUninitialize()
{
    if (NULL != TuPageDirectoryPointer) {
        CmFreeContiguousMemory(TuPageDirectoryPointer);
    }

    if (NULL != TuControllerDomain) {
        CmFreeNonPagedMemory(TuControllerDomain);
    }
}