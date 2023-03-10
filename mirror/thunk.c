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

VOID NTAPI
TuDpcDispatcher(
    __in PKDPC Dpc,
    __in PTHUNK_TASK Task,
    __in PKEVENT Event,
    __in PVOID SystemArgument2
)
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
    __inout_opt PVOID Context
)
{
    THUNK_TASK Task;
    ULONG Index;
    KEVENT Event;
    KDPC Dpc;
    PROCESSOR_NUMBER Number;

    Task.TaskCode = TaskCode;
    Task.Context = Context;
    Task.Status = STATUS_SUCCESS;

    if (NULL == TuGenericDomain) {
        return STATUS_MEMORY_NOT_ALLOCATED;
    }

    KeInitializeEvent(&Event, NotificationEvent, FALSE);

    for (Index = 0; Index < TuProcessorNumber; Index++) {
        KeInitializeDpc(&Dpc, TuDpcDispatcher, &Task);

        KeGetProcessorNumberFromIndex(Index, &Number);
        KeSetTargetProcessorDpcEx(&Dpc, &Number);
        KeSetImportanceDpc(&Dpc, HighImportance);

        KeClearEvent(&Event);

        if (FALSE != KeInsertQueueDpc(&Dpc, &Event, NULL)) {
            KeWaitForSingleObject(&Event, Executive, KernelMode, FALSE, NULL);
        }
    }

    return Task.Status;
}

NTSTATUS NTAPI
TuInitialize()
{
    NTSTATUS Status;
    PVOID PageDirectoryPointer = NULL;
    PVOID GenericDomain = NULL;

    TuProcessorType = FeaGetProcessorType();

    if (PROCESSOR_OTHERS == TuProcessorType) {
        Status = STATUS_NOT_SUPPORTED;
        goto Cleanup;
    }

    PageDirectoryPointer = CmAllocateContiguousMemory(PAGE_SIZE);

    if (NULL == PageDirectoryPointer) {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto Cleanup;
    }

    Status = CmBuildPageDirectory(PageDirectoryPointer);

    if (FALSE == NT_SUCCESS(Status)) {
        goto Cleanup;
    }

    TuProcessorNumber = FeaGetProcessorNumber();

    if (PROCESSOR_AMD == TuProcessorType) {
        GenericDomain = SvmAllocateDomain(TuProcessorNumber);
    }
    else {
        GenericDomain = VmxAllocateDomain(TuProcessorNumber);
    }

    if (NULL == GenericDomain) {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto Cleanup;
    }

    TuPageDirectoryPointer = PageDirectoryPointer;
    TuGenericDomain = GenericDomain;

    return STATUS_SUCCESS;

Cleanup:

    if (NULL != PageDirectoryPointer) {
        CmFreeContiguousMemory(PageDirectoryPointer);
    }

    if (NULL != GenericDomain) {
        CmFreeContiguousMemory(GenericDomain);
    }

    return Status;
}

NTSTATUS NTAPI
TuUninitialize()
{
    if (NULL == TuGenericDomain) {
        return STATUS_MEMORY_NOT_ALLOCATED;
    }

    CmFreeContiguousMemory(TuPageDirectoryPointer);
    TuPageDirectoryPointer = NULL;

    if (PROCESSOR_AMD == TuProcessorType) {
        SvmFreeDomain(TuProcessorNumber, TuGenericDomain);
        TuGenericDomain = NULL;
    }
    else {
        VmxFreeDomain(TuProcessorNumber, TuGenericDomain);
        TuGenericDomain = NULL;
    }

    return STATUS_SUCCESS;
}