#include "idefs.h"
#include "logger.h"
#include "common.h"
#include "features.h"
#include "svm.h"
#include "vmx.h"
#include "hvm.h"

PHVM_MANAGER HvmGlobalManager = NULL;

NTSTATUS NTAPI
HvmCreateHostPageDirectory(
    __out PPAGE_DIRECTORY PageDirectory)
{
    PVOID RootDirectoryPointer;
    PHYSICAL_ADDRESS RootDirectoryBase;

    RootDirectoryBase.QuadPart = CmGetDirectoryTableBase(PsInitialSystemProcess) & ~0xFFF;

    RootDirectoryPointer = MmGetVirtualForPhysical(RootDirectoryBase);

    if (NULL == RootDirectoryPointer) {
        return STATUS_UNSUCCESSFUL;
    }

    PageDirectory->DirectoryPointer = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == PageDirectory->DirectoryPointer) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    PageDirectory->DirectoryBase = MmGetPhysicalAddress(PageDirectory->DirectoryPointer);

    RtlCopyMemory(PageDirectory->DirectoryPointer, RootDirectoryPointer, PAGE_SIZE);

    return STATUS_SUCCESS;
}

VOID NTAPI
HvmDestroyHostPageDirectory(
    __in PPAGE_DIRECTORY PageDirectory)
{
    CmFreeContiguousMemory(PageDirectory->DirectoryPointer);
}

NTSTATUS NTAPI
HvmInitialize(
    __in ULONG CallKey)
{
    NTSTATUS Status;
    PHVM_MANAGER Manager;

    Manager = CmAllocateNonPagedMemory(sizeof(HVM_MANAGER));

    if (NULL == Manager) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Status = HvmCreateHostPageDirectory(&Manager->HostPageDirectory);

    if (FALSE == NT_SUCCESS(Status)) {

        CmFreeNonPagedMemory(Manager);

        return Status;
    }

    Manager->ProcessorType = FeaGetProcessorType();

    if (PROCESSOR_OTHERS == Manager->ProcessorType) {

        HvmDestroyHostPageDirectory(&Manager->HostPageDirectory);
        CmFreeNonPagedMemory(Manager);

        return STATUS_NOT_SUPPORTED;
    }

    if (PROCESSOR_AMD == Manager->ProcessorType) {
        //
    }
    else {
        //
    }

    if (NULL == Manager->ControlDomain) {

        HvmDestroyHostPageDirectory(&Manager->HostPageDirectory);
        CmFreeNonPagedMemory(Manager);

        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Manager->CallKey = CallKey;
    Manager->ProcessorNumber = KeQueryActiveProcessorCountEx(ALL_PROCESSOR_GROUPS);

    HvmGlobalManager = Manager;

    return STATUS_SUCCESS;
}

VOID NTAPI
HvmUninitialize()
{
    if (NULL != HvmGlobalManager) {
        HvmDestroyHostPageDirectory(&HvmGlobalManager->HostPageDirectory);
        CmFreeNonPagedMemory(HvmGlobalManager);
    }
}