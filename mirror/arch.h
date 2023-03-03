#ifndef _ARCH_H_
#define _ARCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MSR_FEATURE_CONTROL 0x0000003A // Only Intel
#define MSR_VMX_BASIC       0x00000480 // Only Intel
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

typedef struct _GUEST_CONTEXT {
    union {
        ULONG GPR[8];
        struct {
            union {
                ULONG Eax;
                USHORT Ax;
                struct {
                    UCHAR Al;
                    UCHAR Ah;
                };
            };

            union {
                ULONG Ecx;
                USHORT Cx;
                struct {
                    UCHAR Cl;
                    UCHAR Ch;
                };
            };

            union {
                ULONG Edx;
                USHORT Dx;
                struct {
                    UCHAR Dl;
                    UCHAR Dh;
                };
            };

            union {
                ULONG Ebx;
                USHORT Bx;
                struct {
                    UCHAR Bl;
                    UCHAR Bh;
                };
            };

            union {
                ULONG Esp;
                USHORT Sp;
                UCHAR Spl;
            };

            union {
                ULONG Ebp;
                USHORT Bp;
                UCHAR Bpl;
            };

            union {
                ULONG Esi;
                USHORT Si;
                UCHAR Sil;
            };

            union {
                ULONG Edi;
                USHORT Di;
                UCHAR Dil;
            };
        };
    };

    ULONG Eip;
    ULONG EFlags;

    USHORT SegEs;
    USHORT SegCs;
    USHORT SegSs;
    USHORT SegDs;
    USHORT SegFs;
    USHORT SegGs;
    USHORT Ldtr;
    USHORT Tr;

    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;

    union {
        ULONG CR[5];
        struct {
            ULONG Cr0;
            ULONG NOTHING : 32;
            ULONG Cr2;
            ULONG Cr3;
            ULONG Cr4;
        };
    };

    union {
        ULONG DR[8];
        struct {
            ULONG Dr0;
            ULONG Dr1;
            ULONG Dr2;
            ULONG Dr3;
            ULONG NOTHING : 32;
            ULONG NOTHING : 32;
            ULONG Dr6;
            ULONG Dr7;
        };
    };
} GUEST_CONTEXT, *PGUEST_CONTEXT;

C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Eax) == 0x0);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Ecx) == 0x4);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Edx) == 0x8);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Ebx) == 0xC);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Esp) == 0x10);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Ebp) == 0x14);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Esi) == 0x18);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Edi) == 0x1C);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Eip) == 0x20);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, EFlags) == 0x24);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegEs) == 0x28);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegCs) == 0x2A);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegSs) == 0x2C);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegDs) == 0x2E);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegFs) == 0x30);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegGs) == 0x32);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Ldtr) == 0x34);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Tr) == 0x36);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Gdtr.Limit) == 0x3A);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Idtr.Limit) == 0x42);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr0) == 0x48);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr2) == 0x50);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr3) == 0x54);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr4) == 0x58);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr0) == 0x5C);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr1) == 0x60);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr2) == 0x64);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr3) == 0x68);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr6) == 0x74);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr7) == 0x78);
C_ASSERT(sizeof(GUEST_CONTEXT) == 0x7C);
#else
typedef struct _KDESCRIPTOR {
    USHORT Pad[3];
    USHORT Limit;
    PUCHAR Base;
} KDESCRIPTOR, *PKDESCRIPTOR;

typedef struct DECLSPEC_ALIGN(16) _GUEST_CONTEXT {
    union {
        ULONG64 GPR[16];
        struct {
            union {
                ULONG64 Rax;
                ULONG Eax;
                USHORT Ax;
                struct {
                    UCHAR Al;
                    UCHAR Ah;
                };
            };

            union {
                ULONG64 Rcx;
                ULONG Ecx;
                USHORT Cx;
                struct {
                    UCHAR Cl;
                    UCHAR Ch;
                };
            };

            union {
                ULONG64 Rdx;
                ULONG Edx;
                USHORT Dx;
                struct {
                    UCHAR Dl;
                    UCHAR Dh;
                };
            };

            union {
                ULONG64 Rbx;
                ULONG Ebx;
                USHORT Bx;
                struct {
                    UCHAR Bl;
                    UCHAR Bh;
                };
            };

            union {
                ULONG64 Rsp;
                ULONG Esp;
                USHORT Sp;
                UCHAR Spl;
            };

            union {
                ULONG64 Rbp;
                ULONG Ebp;
                USHORT Bp;
                UCHAR Bpl;
            };

            union {
                ULONG64 Rsi;
                ULONG Esi;
                USHORT Si;
                UCHAR Sil;
            };

            union {
                ULONG64 Rdi;
                ULONG Edi;
                USHORT Di;
                UCHAR Dil;
            };

            union {
                ULONG64 R8;
                ULONG R8d;
                USHORT R8w;
                UCHAR R8b;
            };

            union {
                ULONG64 R9;
                ULONG R9d;
                USHORT R9w;
                UCHAR R9b;
            };

            union {
                ULONG64 R10;
                ULONG R10d;
                USHORT R10w;
                UCHAR R10b;
            };

            union {
                ULONG64 R11;
                ULONG R11d;
                USHORT R11w;
                UCHAR R11b;
            };

            union {
                ULONG64 R12;
                ULONG R12d;
                USHORT R12w;
                UCHAR R12b;
            };

            union {
                ULONG64 R13;
                ULONG R13d;
                USHORT R13w;
                UCHAR R13b;
            };

            union {
                ULONG64 R14;
                ULONG R14d;
                USHORT R14w;
                UCHAR R14b;
            };

            union {
                ULONG64 R15;
                ULONG R15d;
                USHORT R15w;
                UCHAR R15b;
            };
        };
    };

    ULONG64 Rip;

    union {
        ULONG64 RFlags;
        ULONG EFlags;
    };

    USHORT SegEs;
    USHORT SegCs;
    USHORT SegSs;
    USHORT SegDs;
    USHORT SegFs;
    USHORT SegGs;
    USHORT Ldtr;
    USHORT Tr;

    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;

    union {
        ULONG64 CR[9];
        struct {
            ULONG64 Cr0;
            ULONG64 NOTHING : 64;
            ULONG64 Cr2;
            ULONG64 Cr3;
            ULONG64 Cr4;
            ULONG64 NOTHING : 64;
            ULONG64 NOTHING : 64;
            ULONG64 NOTHING : 64;
            ULONG64 Cr8;
        };
    };

    union {
        ULONG64 DR[8];
        struct {
            ULONG64 Dr0;
            ULONG64 Dr1;
            ULONG64 Dr2;
            ULONG64 Dr3;
            ULONG64 NOTHING : 64;
            ULONG64 NOTHING : 64;
            ULONG64 Dr6;
            ULONG64 Dr7;
        };
    };

} GUEST_CONTEXT, *PGUEST_CONTEXT;

C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rax) == 0x0);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rcx) == 0x8);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rdx) == 0x10);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rbx) == 0x18);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rsp) == 0x20);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rbp) == 0x28);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rsi) == 0x30);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rdi) == 0x38);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, R8) == 0x40);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, R9) == 0x48);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, R10) == 0x50);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, R11) == 0x58);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, R12) == 0x60);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, R13) == 0x68);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, R14) == 0x70);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, R15) == 0x78);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Rip) == 0x80);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, RFlags) == 0x88);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegEs) == 0x90);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegCs) == 0x92);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegSs) == 0x94);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegDs) == 0x96);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegFs) == 0x98);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, SegGs) == 0x9A);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Ldtr) == 0x9C);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Tr) == 0x9E);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Gdtr.Limit) == 0xA6);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Idtr.Limit) == 0xB6);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr0) == 0xC0);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr2) == 0xD0);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr3) == 0xD8);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr4) == 0xE0);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Cr8) == 0x100);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr0) == 0x108);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr1) == 0x110);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr2) == 0x118);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr3) == 0x120);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr6) == 0x138);
C_ASSERT(FIELD_OFFSET(GUEST_CONTEXT, Dr7) == 0x140);
C_ASSERT(sizeof(GUEST_CONTEXT) == 0x150);
#endif

#ifdef __cplusplus
}
#endif

#endif
