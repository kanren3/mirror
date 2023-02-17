#ifndef _HVM_H_
#define _HVM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MACHINE_NONE  0x00000000
#define MACHINE_INTEL 0x00000001
#define MACHINE_AMD   0x00000002

NTSTATUS NTAPI
HvInitializeProcessor();

#ifdef __cplusplus
}
#endif

#endif
