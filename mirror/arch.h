#ifndef _ARCH_H_
#define _ARCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MSR_FEATURE_CONTROL 0x0000003A // Only Intel
#define MSR_EFER            0xC0000080
#define MSR_VM_CR           0xC0010114 // Only AMD

typedef struct _CPU_INFO {
    ULONG Eax;
    ULONG Ebx;
    ULONG Ecx;
    ULONG Edx;
} CPU_INFO, *PCPU_INFO;

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
