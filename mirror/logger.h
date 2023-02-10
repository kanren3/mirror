#ifndef _LOGGER_H_
#define _LOGGER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LogMemoryCopy __movsb

#define LogAllocateNonPagePool(NumberOfBytes) \
    ExAllocatePoolWithTag(NonPagedPool, NumberOfBytes, 'LOG')

#define LogFreePool(Pointer) \
    ExFreePoolWithTag(Pointer, 'LOG')

#define MSG_POOL_SIZE (PAGE_SIZE * 10)

#define MSG_TYPE_UNICODE 0x00000001
#define MSG_TYPE_ANSI    0x00000002

typedef struct _MESSAGE_HEADER {
    LARGE_INTEGER Time;
    ULONG Type;
    ULONG Length;
    UCHAR Body[1];
} MESSAGE_HEADER, *PMESSAGE_HEADER;

#define MESSAGE_HEADER_LENGTH \
    FIELD_OFFSET(MESSAGE_HEADER, Body)

#define GetMessageLength(Header) \
    (MESSAGE_HEADER_LENGTH + Header->Length)

#define GetNextMessage(Header) \
    ((PMESSAGE_HEADER)((PUCHAR)(Header) + GetMessageLength(Header)))

#define IdlePoolToMessage(Pool, Length) \
    ((PMESSAGE_HEADER)((PUCHAR)(Pool) + Length))

VOID NTAPI
LogSyncPrint(
    __in PCSTR Format,
    __in...);

VOID NTAPI
LogAsyncPrint(
    __in PCSTR Format,
    __in...);

VOID NTAPI
LogUninitialize();

NTSTATUS NTAPI
LogInitialize(
    __in ULONG FlushTime);

#ifdef __cplusplus
}
#endif

#endif
