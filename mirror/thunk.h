#ifndef _THUNK_H_
#define _THUNK_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TASK_STARTUP  0x00000001
#define TASK_SHUTDOWN 0x00000002

typedef struct _THUNK_TASK {
    ULONG TaskCode;
    PVOID Context;
    NTSTATUS Status;
} THUNK_TASK, *PTHUNK_TASK;

NTSTATUS NTAPI
TuGenericCall(
    __in ULONG TaskCode,
    __inout_opt PVOID Context);

NTSTATUS NTAPI
TuInitialize();

VOID NTAPI
TuUninitialize();

#ifdef __cplusplus
}
#endif

#endif
