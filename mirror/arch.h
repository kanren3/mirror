#ifndef _ARCH_H_
#define _ARCH_H_

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _WIN64
#define VGDT_NULL         (0 * 8)
#define VGDT_CODE         (1 * 8)
#define VGDT_DATA         (2 * 8)
#define VGDT_TSS          (3 * 8)
#define VGDT_LAST         (4 * 8)
#else
#define VGDT_NULL         (0 * 16)
#define VGDT_CODE         (1 * 16)
#define VGDT_DATA         (1 * 16) + 8
#define VGDT_TSS          (2 * 16)
#define VGDT_LAST         (3 * 16)
#endif

#define TYPE_CODE       0x1A
#define TYPE_DATA       0x12
#define TYPE_TSS        0x09

#define GRANULARITY_BYTE 0
#define GRANULARITY_PAGE 1

#define DPL_USER    3
#define DPL_SYSTEM  0

#define MSR_FEATURE_CONTROL             0x0000003A  // only intel
#define MSR_SYSENTER_CS                 0x00000174
#define MSR_SYSENTER_ESP                0x00000175
#define MSR_SYSENTER_EIP                0x00000176
#define MSR_DEBUGCTL                    0x000001D9
#define MSR_PAT                         0x00000277
#define MSR_VMX_BASIC                   0x00000480  // only intel
#define MSR_VMX_PINBASED_CTLS           0x00000481  // only intel
#define MSR_VMX_PROCBASED_CTLS          0x00000482  // only intel
#define MSR_VMX_EXIT_CTLS               0x00000483  // only intel
#define MSR_VMX_ENTRY_CTLS              0x00000484  // only intel
#define MSR_VMX_MISC                    0x00000485  // only intel
#define MSR_VMX_CR0_FIXED0              0x00000486  // only intel
#define MSR_VMX_CR0_FIXED1              0x00000487  // only intel
#define MSR_VMX_CR4_FIXED0              0x00000488  // only intel
#define MSR_VMX_CR4_FIXED1              0x00000489  // only intel
#define MSR_VMX_VMCS_ENUM               0x0000048A  // only intel
#define MSR_VMX_SECONDARY_CTLS          0x0000048B  // only intel
#define MSR_VMX_SECONDARY_CTLS          0x0000048B  // only intel
#define MSR_VMX_EPT_VPID_CAP            0x0000048C  // only intel
#define MSR_VMX_TRUE_PINBASED_CTLS      0x0000048D  // only intel
#define MSR_VMX_TRUE_PROCBASED_CTLS     0x0000048E  // only intel
#define MSR_VMX_TRUE_EXIT_CTLS          0x0000048F  // only intel
#define MSR_VMX_TRUE_ENTRY_CTLS         0x00000490  // only intel
#define MSR_EFER                        0xC0000080
#define MSR_STAR                        0xC0000081
#define MSR_LSTAR                       0xC0000082
#define MSR_CSTAR                       0xC0000083
#define MSR_SFMASK                      0xC0000084
#define MSR_FS_BASE                     0xC0000100
#define MSR_GS_BASE                     0xC0000101
#define MSR_KERNEL_GS_BASE              0xC0000102
#define MSR_VM_CR                       0xC0010114  // only amd
#define MSR_VM_HSAVE_PA		            0xC0010117  // only amd

typedef struct _CPU_INFO {
    ULONG Eax;
    ULONG Ebx;
    ULONG Ecx;
    ULONG Edx;
} CPU_INFO, *PCPU_INFO;

typedef union _KGDT_LIMIT {
    ULONG Limit;
    struct {
        USHORT LimitLow;
        UCHAR LimitHigh;
    };
} KGDT_LIMIT, *PKGDT_LIMIT;

typedef union _KGDT_BASE {
    ULONG_PTR Base;
    struct {
        USHORT BaseLow;
        UCHAR BaseMiddle;
        UCHAR BaseHigh;
#ifdef _WIN64
        ULONG BaseUpper;
#endif
    };
} KGDT_BASE, *PKGDT_BASE;

typedef struct _KGDTENTRY32 {
    USHORT LimitLow;
    USHORT BaseLow;

    union {
        struct {
            UCHAR BaseMiddle;
            UCHAR Flags1;
            UCHAR Flags2;
            UCHAR BaseHigh;
        } Bytes;

        struct {
            ULONG BaseMiddle : 8;
            ULONG Type : 5;
            ULONG Dpl : 2;
            ULONG Present : 1;
            ULONG LimitHigh : 4;
            ULONG System : 1;
            ULONG NOTHING : 1;
            ULONG DefaultBig : 1;
            ULONG Granularity : 1;
            ULONG BaseHigh : 8;
        } Bits;
    };
} KGDTENTRY32, *PKGDTENTRY32;

typedef union _KGDTENTRY64 {
    struct {
        USHORT LimitLow;
        USHORT BaseLow;

        union {
            struct {
                UCHAR BaseMiddle;
                UCHAR Flags1;
                UCHAR Flags2;
                UCHAR BaseHigh;
            } Bytes;

            struct {
                UCHAR BaseMiddle : 8;
                UCHAR Type : 5;
                UCHAR Dpl : 2;
                UCHAR Present : 1;
                UCHAR LimitHigh : 4;
                UCHAR System : 1;
                UCHAR LongMode : 1;
                UCHAR DefaultBig : 1;
                UCHAR Granularity : 1;
                UCHAR BaseHigh : 8;
            } Bits;
        };

        ULONG BaseUpper;
        ULONG MustBeZero;
    };

    ULONG64 Alignment;
} KGDTENTRY64, *PKGDTENTRY64;

#ifndef _WIN64
typedef struct _KDESCRIPTOR {
    USHORT Pad;
    USHORT Limit;
    PUCHAR Base;
} KDESCRIPTOR, *PKDESCRIPTOR;

typedef struct _KTSS {

    USHORT Backlink;
    USHORT NOTHING : 16;

    ULONG  Esp0;
    USHORT Ss0;
    USHORT NOTHING : 16;

    ULONG  Esp1;
    USHORT Ss1;
    USHORT NOTHING : 16;

    ULONG  Esp2;
    USHORT Ss2;
    USHORT NOTHING : 16;

    ULONG CR3;
    ULONG Eip;
    ULONG EFlags;
    ULONG Eax;
    ULONG Ecx;
    ULONG Edx;
    ULONG Ebx;
    ULONG Esp;
    ULONG Ebp;
    ULONG Esi;
    ULONG Edi;

    USHORT Es;
    USHORT NOTHING : 16;

    USHORT Cs;
    USHORT NOTHING : 16;

    USHORT Ss;
    USHORT NOTHING : 16;

    USHORT Ds;
    USHORT NOTHING : 16;

    USHORT Fs;
    USHORT NOTHING : 16;

    USHORT Gs;
    USHORT NOTHING : 16;

    USHORT LDT;
    USHORT NOTHING : 16;

    USHORT Flags;
    USHORT IoMapBase;

    ULONG ShadowStack;
} KTSS, *PKTSS;

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

#pragma pack(push, 4)
typedef struct _KTSS {
    ULONG NOTHING : 32;

    ULONGLONG Rsp0;
    ULONGLONG Rsp1;
    ULONGLONG Rsp2;

    ULONG NOTHING : 32;
    ULONG NOTHING : 32;

    union {
        struct {
            ULONGLONG Ist1;
            ULONGLONG Ist2;
            ULONGLONG Ist3;
            ULONGLONG Ist4;
            ULONGLONG Ist5;
            ULONGLONG Ist6;
            ULONGLONG Ist7;
        };

        ULONGLONG Ist[7];
    };

    ULONG NOTHING : 32;
    ULONG NOTHING : 32;

    USHORT NOTHING : 16;
    USHORT IoMapBase;
} KTSS, *PKTSS;
#pragma pack(pop)

typedef struct DECLSPEC_ALIGN(16) _GUEST_CONTEXT {
    union {
        ULONGLONG GPR[16];
        struct {
            union {
                ULONGLONG Rax;
                ULONG Eax;
                USHORT Ax;
                struct {
                    UCHAR Al;
                    UCHAR Ah;
                };
            };

            union {
                ULONGLONG Rcx;
                ULONG Ecx;
                USHORT Cx;
                struct {
                    UCHAR Cl;
                    UCHAR Ch;
                };
            };

            union {
                ULONGLONG Rdx;
                ULONG Edx;
                USHORT Dx;
                struct {
                    UCHAR Dl;
                    UCHAR Dh;
                };
            };

            union {
                ULONGLONG Rbx;
                ULONG Ebx;
                USHORT Bx;
                struct {
                    UCHAR Bl;
                    UCHAR Bh;
                };
            };

            union {
                ULONGLONG Rsp;
                ULONG Esp;
                USHORT Sp;
                UCHAR Spl;
            };

            union {
                ULONGLONG Rbp;
                ULONG Ebp;
                USHORT Bp;
                UCHAR Bpl;
            };

            union {
                ULONGLONG Rsi;
                ULONG Esi;
                USHORT Si;
                UCHAR Sil;
            };

            union {
                ULONGLONG Rdi;
                ULONG Edi;
                USHORT Di;
                UCHAR Dil;
            };

            union {
                ULONGLONG R8;
                ULONG R8d;
                USHORT R8w;
                UCHAR R8b;
            };

            union {
                ULONGLONG R9;
                ULONG R9d;
                USHORT R9w;
                UCHAR R9b;
            };

            union {
                ULONGLONG R10;
                ULONG R10d;
                USHORT R10w;
                UCHAR R10b;
            };

            union {
                ULONGLONG R11;
                ULONG R11d;
                USHORT R11w;
                UCHAR R11b;
            };

            union {
                ULONGLONG R12;
                ULONG R12d;
                USHORT R12w;
                UCHAR R12b;
            };

            union {
                ULONGLONG R13;
                ULONG R13d;
                USHORT R13w;
                UCHAR R13b;
            };

            union {
                ULONGLONG R14;
                ULONG R14d;
                USHORT R14w;
                UCHAR R14b;
            };

            union {
                ULONGLONG R15;
                ULONG R15d;
                USHORT R15w;
                UCHAR R15b;
            };
        };
    };

    ULONGLONG Rip;

    union {
        ULONGLONG RFlags;
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
        ULONGLONG CR[9];
        struct {
            ULONGLONG Cr0;
            ULONGLONG NOTHING : 64;
            ULONGLONG Cr2;
            ULONGLONG Cr3;
            ULONGLONG Cr4;
            ULONGLONG NOTHING : 64;
            ULONGLONG NOTHING : 64;
            ULONGLONG NOTHING : 64;
            ULONGLONG Cr8;
        };
    };

    union {
        ULONGLONG DR[8];
        struct {
            ULONGLONG Dr0;
            ULONGLONG Dr1;
            ULONGLONG Dr2;
            ULONGLONG Dr3;
            ULONGLONG NOTHING : 64;
            ULONGLONG NOTHING : 64;
            ULONGLONG Dr6;
            ULONGLONG Dr7;
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
