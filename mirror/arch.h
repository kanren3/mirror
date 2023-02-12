#ifndef _ARCH_H_
#define _ARCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MSR_EFER 0xC0000080

#ifndef _WIN64
typedef struct _KDESCRIPTOR {
    USHORT Pad;
    USHORT Limit;
    PUCHAR Base;
} KDESCRIPTOR, *PKDESCRIPTOR;
#else
typedef struct _KDESCRIPTOR {
    USHORT Pad[3];
    USHORT Limit;
    PUCHAR Base;
} KDESCRIPTOR, *PKDESCRIPTOR;
#endif

#ifdef __cplusplus
}
#endif

#endif
