#ifndef _VMX_H_
#define _VMX_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef union _VMX_BASIC {
    ULONGLONG Value;

    struct {
        ULONG Identifier;
        ULONG NumberOfBytes : 16;
        ULONG Limit : 1;
        ULONG DualMonitor : 1;
        ULONG Type : 4;
        ULONG InsReporting : 1;
        ULONG TrueCtls : 1;
        ULONG DeliverExcept : 1;
        ULONG NOTHING : 7;
    };

} VMX_BASIC, *PVMX_BASIC;

#ifdef __cplusplus
}
#endif

#endif
