#ifndef _EXT_H_
#define _EXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PtrToUlongPtr() ((ULONG_PTR)(p))
#define UlongPtrToPtr() ((PVOID)(p))

#define PtrToUlong64() ((ULONGLONG)(p))
#define Ulong64ToPtr() ((PVOID)(p))

BOOLEAN NTAPI
KeAlertThread(
    __in PKTHREAD Thread,
    __in KPROCESSOR_MODE AlertMode);

VOID NTAPI
KeGenericCallDpc(
    __in PKDEFERRED_ROUTINE Routine,
    __in_opt PVOID Context);

VOID NTAPI
KeSignalCallDpcDone(
    __in PVOID SystemArgument1);

LOGICAL NTAPI
KeSignalCallDpcSynchronize(
    __in PVOID SystemArgument2);

#ifdef __cplusplus
}
#endif

#endif
