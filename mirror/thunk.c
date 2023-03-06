#include "idefs.h"
#include "logger.h"
#include "common.h"
#include "features.h"
#include "svmcore.h"
#include "vmxcore.h"
#include "thunk.h"

ULONG TuProcessorNumber;
ULONG TuProcessorType;

PVOID TuGenericDomain;
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

VOID NTAPI
TuDpcDispatcher(
    __in PKDPC Dpc,
    __in PTHUNK_TASK Task,
    __in PKEVENT Event,
    __in PVOID SystemArgument2)
{
    if (PROCESSOR_AMD == TuProcessorType) {
        Task->Status = SvmTaskDispatcher(TuGenericDomain, Task->TaskCode, Task->Context);
    }
    else {
        Task->Status = VmxTaskDispatcher(TuGenericDomain, Task->TaskCode, Task->Context);
    }

    KeSetEvent(Event, LOW_PRIORITY, FALSE);
}

NTSTATUS NTAPI
TuGenericCall(
    __in ULONG TaskCode,
    __inout_opt PVOID Context)
{
    ULONG i;
    KDPC Dpc;
    KEVENT Event;
    THUNK_TASK Task;
    PROCESSOR_NUMBER Number;

    Task.TaskCode = TaskCode;
    Task.Context = Context;
    Task.Status = STATUS_SUCCESS;

    if (NULL != TuGenericDomain) {
        KeInitializeEvent(&Event, NotificationEvent, FALSE);
        
        for (i = 0; i < TuProcessorNumber; i++) {
            KeGetProcessorNumberFromIndex(i, &Number);
            KeClearEvent(&Event);

            KeInitializeDpc(&Dpc, TuDpcDispatcher, &Task);
            KeSetTargetProcessorDpcEx(&Dpc, &Number);
            KeSetImportanceDpc(&Dpc, HighImportance);

            if (FALSE != KeInsertQueueDpc(&Dpc, &Event, NULL)) {
                KeWaitForSingleObject(&Event, Executive, KernelMode, FALSE, NULL);
            }
        }

        return Task.Status;
    }

    return STATUS_MEMORY_NOT_ALLOCATED;
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
        TuGenericDomain = CmAllocateNonPagedMemory(TuProcessorNumber * sizeof(SVM_DOMAIN));
    }
    else {
        TuGenericDomain = CmAllocateNonPagedMemory(TuProcessorNumber * sizeof(VMX_DOMAIN));
    }

    if (NULL == TuGenericDomain) {
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

    if (NULL != TuGenericDomain) {
        CmFreeNonPagedMemory(TuGenericDomain);
    }
}