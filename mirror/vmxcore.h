#ifndef _VMXCORE_H_
#define _VMXCORE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _VMX_DOMAIN {
    PUCHAR Vmon;
    PUCHAR Vmcs;
    PUCHAR VmmStack;
    PUCHAR MsrBitmap;
    PUCHAR IoBitmap;
    PUCHAR Tss;
    PUCHAR XSaveArea;

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
VmxTaskDispatcher(
    __in PVMX_DOMAIN Domain,
    __in ULONG TaskCode,
    __inout_opt PVOID Context);

#ifdef __cplusplus
}
#endif

#endif
