#ifndef _VMXCORE_H_
#define _VMXCORE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define VMX_FEATURE_SUPPORT       0x00000001
#define VMX_FEATURE_ENABLE        0x00000002

typedef struct _VMX_REGION {
    ULONG Identifier;
    ULONG Abort;
    UCHAR Data[PAGE_SIZE - 8];
} VMX_REGION, *PVMX_REGION;

typedef struct _VMX_DOMAIN {
    PVMX_REGION Vmon;
    PVMX_REGION Vmcs;
    PUCHAR VmmStack;
    PUCHAR MsrBitmap;
    PUCHAR IoBitmap;
    PUCHAR XSaveArea;
    PKTSS Tss;

    KDESCRIPTOR Gdtr;
    KDESCRIPTOR Idtr;

    ULONG_PTR Cr0;
    ULONG_PTR Cr3;
    ULONG_PTR Cr4;

    VMX_BASIC BasicInfo;

    ULARGE_INTEGER PinFixed;
    ULARGE_INTEGER PrimaryFixed;
    ULARGE_INTEGER SecondaryFixed;
    ULARGE_INTEGER ExitFixed;
    ULARGE_INTEGER EntryFixed;

    ULONGLONG Features;
} VMX_DOMAIN, *PVMX_DOMAIN;

NTSTATUS NTAPI
VmxPrepareStartup(
    __in PVMX_DOMAIN Domain);

VOID NTAPI
VmxFreeDomain(
    __in ULONG Number,
    __in PVMX_DOMAIN Domain);

PVMX_DOMAIN NTAPI
VmxAllocateDomain(
    __in ULONG Number);

NTSTATUS NTAPI
VmxTaskDispatcher(
    __in PVMX_DOMAIN Domain,
    __in ULONG TaskCode,
    __inout_opt PVOID Context);

#ifdef __cplusplus
}
#endif

#endif
