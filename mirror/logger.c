#include "idefs.h"
#include "logger.h"

ULONG LogMsgFlushTime = 0;
ULONG LogMsgSpinLock = 0;

PVOID LogMsgStorePool = NULL;
ULONG LogMsgStoreLength = 0;

PVOID LogMsgHandlerPool = NULL;
ULONG LogMsgHandlerLength = 0;

ULONG LogMsgWorkerState = 0;
PETHREAD LogMsgWorkerThread = NULL;

VOID NTAPI
LogSyncPrint(
    __in PCSTR Format,
    __in...
)
{
    va_list ArgList;

    va_start(ArgList, Format);

    vDbgPrintExWithPrefix("[mirror]\t",
                          DPFLTR_IHVDRIVER_ID,
                          DPFLTR_ERROR_LEVEL,
                          Format,
                          ArgList);

    va_end(ArgList);
}

VOID NTAPI
LogMsgSingleHandler(
    __in PMESSAGE_HEADER Message
)
{
    switch (Message->Type) {
    case MSG_TYPE_UNICODE:
        LogSyncPrint("%ws", Message->Body);
        break;
    case MSG_TYPE_ANSI:
        LogSyncPrint("%s", Message->Body);
        break;
    }
}

VOID NTAPI
LogMsgMultipleHandler()
{
    PMESSAGE_HEADER Message;

    Message = LogMsgHandlerPool;

    while (0 != LogMsgHandlerLength) {
        LogMsgSingleHandler(Message);
        LogMsgHandlerLength -= GetMessageLength(Message);
        Message = GetNextMessage(Message);
    }
}

VOID NTAPI
LogAcquireSpinLock(
    __inout volatile PULONG SpinLock,
    __out PKIRQL Irql
)
{
    KeRaiseIrql(HIGH_LEVEL, Irql);

    while (InterlockedBitTestAndSet(SpinLock, 0)) {
        YieldProcessor();
    }
}

VOID NTAPI
LogReleaseSpinLock(
    __inout volatile PULONG SpinLock,
    __in KIRQL Irql
)
{
    InterlockedAnd(SpinLock, 0);
    KeLowerIrql(Irql);
}

VOID NTAPI
LogSendMessage(
    __in PVOID Data,
    __in ULONG Type,
    __in ULONG Length
)
{
    KIRQL Irql;
    PMESSAGE_HEADER Message;
    ULONG MessageLength;

    LogAcquireSpinLock(&LogMsgSpinLock, &Irql);

    if (NULL != LogMsgStorePool) {
        if (Length <= MSG_POOL_SIZE - LogMsgStoreLength) {

            Message = IdlePoolToMessage(LogMsgStorePool, LogMsgStoreLength);

            Message->Type = Type;
            Message->Length = Length;
            KeQuerySystemTime(&Message->Time);
            LogMemoryCopy(Message->Body, Data, Length);

            MessageLength = Length + MESSAGE_HEADER_LENGTH;
            LogMsgStoreLength += MessageLength;
        }
    }

    LogReleaseSpinLock(&LogMsgSpinLock, Irql);
}

VOID NTAPI
LogAsyncPrint(
    __in PCSTR Format,
    __in...
)
{
    va_list ArgList;
    char Buffer[512];
    int Length;

    va_start(ArgList, Format);

    Length = _vsnprintf(Buffer, sizeof(Buffer), Format, ArgList);

    va_end(ArgList);

    if (-1 == Length || sizeof(Buffer) == Length) {
        Buffer[sizeof(Buffer) - 1] = '\0';
        LogSendMessage(Buffer, MSG_TYPE_ANSI, sizeof(Buffer));
    }
    else {
        LogSendMessage(Buffer, MSG_TYPE_ANSI, Length + 1);
    }
}

VOID NTAPI
LogMsgWorker(
    __in PVOID StartContext
)
{
    KIRQL Irql;
    LARGE_INTEGER Interval;

    while (0 == LogMsgWorkerState) {
        LogAcquireSpinLock(&LogMsgSpinLock, &Irql);
        LogMsgHandlerLength = LogMsgStoreLength;

        LogMemoryCopy(LogMsgHandlerPool,
                      LogMsgStorePool,
                      LogMsgStoreLength);

        LogMsgStoreLength = 0;
        LogReleaseSpinLock(&LogMsgSpinLock, Irql);

        LogMsgMultipleHandler();

        Interval.QuadPart = Int32x32To64(LogMsgFlushTime, -10000);
        KeDelayExecutionThread(KernelMode, TRUE, &Interval);
    }

    PsTerminateSystemThread(STATUS_SUCCESS);
}

VOID NTAPI
LogUninitialize()
{
    KIRQL Irql;
    PVOID MsgStorePool, MsgHandlerPool;

    if (NULL != LogMsgWorkerThread) {
        InterlockedExchange(&LogMsgWorkerState, 1);
        KeAlertThread(LogMsgWorkerThread, KernelMode);

        KeWaitForSingleObject(LogMsgWorkerThread,
                              Executive,
                              KernelMode,
                              FALSE,
                              NULL);

        MsgStorePool = LogMsgStorePool;
        MsgHandlerPool = LogMsgHandlerPool;

        LogAcquireSpinLock(&LogMsgSpinLock, &Irql);
        LogMsgHandlerPool = LogMsgStorePool = NULL;
        LogReleaseSpinLock(&LogMsgSpinLock, Irql);

        LogFreePool(MsgHandlerPool);
        LogFreePool(MsgStorePool);
    }
}

NTSTATUS NTAPI
LogInitialize(
    __in ULONG FlushTime
)
{
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    HANDLE ThreadHandle;

    LogMsgFlushTime = FlushTime;
    LogMsgSpinLock = 0;
    LogMsgStoreLength = 0;
    LogMsgHandlerLength = 0;
    LogMsgWorkerState = 0;

    LogMsgStorePool = LogAllocateNonPagePool(MSG_POOL_SIZE);

    if (NULL == LogMsgStorePool) {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    LogMsgHandlerPool = LogAllocateNonPagePool(MSG_POOL_SIZE);

    if (NULL == LogMsgHandlerPool) {
        LogFreePool(LogMsgStorePool);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    InitializeObjectAttributes(&ObjectAttributes, NULL, 0, NULL, NULL);

    Status = PsCreateSystemThread(&ThreadHandle,
                                  THREAD_ALL_ACCESS,
                                  &ObjectAttributes,
                                  NULL,
                                  NULL,
                                  LogMsgWorker,
                                  NULL);

    if (FALSE == NT_SUCCESS(Status)) {
        LogFreePool(LogMsgHandlerPool);
        LogFreePool(LogMsgStorePool);
        return Status;
    }

    ObReferenceObjectByHandle(ThreadHandle,
                              SYNCHRONIZE,
                              NULL,
                              KernelMode,
                              &LogMsgWorkerThread,
                              NULL);

    ZwClose(ThreadHandle);
    return STATUS_SUCCESS;
}