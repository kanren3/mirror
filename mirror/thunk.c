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
TuBuildPageDirectory(
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
        Task->Status = SvmTaskDispatcher(TuGenericDomain,
                                         Task->TaskCode,
                                         Task->Context);
    }
    else {
        Task->Status = VmxTaskDispatcher(TuGenericDomain,
                                         Task->TaskCode,
                                         Task->Context);
    }

    KeSetEvent(Event, LOW_PRIORITY, FALSE);
}

NTSTATUS NTAPI
TuGenericCall(
    __in ULONG TaskCode,
    __inout_opt PVOID Context)
{
    THUNK_TASK ThunkTask;
    ULONG i;
    KEVENT Event;
    KDPC Dpc;
    PROCESSOR_NUMBER Number;

    ThunkTask.TaskCode = TaskCode;
    ThunkTask.Context = Context;
    ThunkTask.Status = STATUS_SUCCESS;

    if (NULL == TuGenericDomain) {
        return STATUS_MEMORY_NOT_ALLOCATED;
    }

    KeInitializeEvent(&Event, NotificationEvent, FALSE);

    for (i = 0; i < TuProcessorNumber; i++) {
        KeGetProcessorNumberFromIndex(i, &Number);
        KeClearEvent(&Event);

        KeInitializeDpc(&Dpc, TuDpcDispatcher, &ThunkTask);
        KeSetTargetProcessorDpcEx(&Dpc, &Number);
        KeSetImportanceDpc(&Dpc, HighImportance);

        if (FALSE != KeInsertQueueDpc(&Dpc, &Event, NULL)) {
            KeWaitForSingleObject(&Event, Executive, KernelMode, FALSE, NULL);
        }
    }

    return ThunkTask.Status;
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

    if (NULL != TuPageDirectoryPointer) {
        Status = TuBuildPageDirectory(TuPageDirectoryPointer);

        if (FALSE != NT_SUCCESS(Status)) {

            if (PROCESSOR_AMD == TuProcessorType) {
                TuGenericDomain = SvmPrepareDomainSpace(TuProcessorNumber);
            }
            else {
                TuGenericDomain = VmxPrepareDomainSpace(TuProcessorNumber);
            }

            if (NULL != TuGenericDomain) {
                return STATUS_SUCCESS;
            }
            else {
                Status = STATUS_INSUFFICIENT_RESOURCES;
            }
        }

        CmFreeContiguousMemory(TuPageDirectoryPointer);
        TuPageDirectoryPointer = NULL;
    }
    else {
        Status = STATUS_INSUFFICIENT_RESOURCES;
    }

    return STATUS_SUCCESS;
}

VOID NTAPI
TuUninitialize()
{
    if (NULL != TuGenericDomain) {
        if (PROCESSOR_AMD == TuProcessorType) {
            SvmUnprepareDomainSpace(TuGenericDomain, TuProcessorNumber);
        }
        else {
            VmxUnprepareDomainSpace(TuGenericDomain, TuProcessorNumber);
        }

        TuGenericDomain = NULL;

        if (NULL != TuPageDirectoryPointer) {
            CmFreeContiguousMemory(TuPageDirectoryPointer);
            TuPageDirectoryPointer = NULL;
        }
    }
}