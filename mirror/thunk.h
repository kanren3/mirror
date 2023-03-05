#ifndef _THUNK_H_
#define _THUNK_H_

#ifdef __cplusplus
extern "C" {
#endif

NTSTATUS NTAPI
TuInitialize();

VOID NTAPI
TuUninitialize();

#ifdef __cplusplus
}
#endif

#endif
