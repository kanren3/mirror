#include "midefs.h"
#include "logger.h"

VOID NTAPI
DriverUnload(
    __in PDRIVER_OBJECT DriverObject)
{
    LogUninitialize();
}

VOID TestIns()
{
    LONG CpuInfo[4] = { 0 };
    KDESCRIPTOR Gdtr = { 0 };
    KDESCRIPTOR Idtr = { 0 };
    ULONG_PTR Cr0, Cr2, Cr3, Cr4;
    ULONG_PTR Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
    ULONGLONG MsrValue = 0;

    _disable();

    __ins_cpuidex(0, 0, CpuInfo);
    __ins_sgdt(&Gdtr.Limit);
    __ins_sidt(&Idtr.Limit);

    Cr0 = __ins_readcr(0);
    Cr2 = __ins_readcr(2);
    Cr3 = __ins_readcr(3);
    Cr4 = __ins_readcr(4);

    Dr0 = __ins_readdr(0);
    Dr1 = __ins_readdr(1);
    Dr2 = __ins_readdr(2);
    Dr3 = __ins_readdr(3);
    Dr6 = __ins_readdr(6);
    Dr7 = __ins_readdr(7);

    __ins_writecr(0, Cr0);
    __ins_writecr(2, Cr2);
    __ins_writecr(3, Cr3);
    __ins_writecr(4, Cr4);

    __ins_writedr(0, Dr0);
    __ins_writedr(1, Dr1);
    __ins_writedr(2, Dr2);
    __ins_writedr(3, Dr3);
    __ins_writedr(6, Dr6);
    __ins_writedr(7, Dr7);

    MsrValue = __ins_rdmsr(MSR_EFER);
    __ins_wrmsr(MSR_EFER, MsrValue);

    __ins_lgdt(&Gdtr.Limit);
    __ins_lidt(&Idtr.Limit);

    _enable();
}

NTSTATUS NTAPI
DriverEntry(
    __in PDRIVER_OBJECT DriverObject,
    __in PUNICODE_STRING RegistryPath)
{
    NTSTATUS Status = STATUS_SUCCESS;

    DriverObject->DriverUnload = DriverUnload;

    Status = LogInitialize(1);

    if (FALSE == NT_SUCCESS(Status)) {
        return Status;
    }

    LogAsyncPrint("hello world.\n");

    TestIns();

    return STATUS_SUCCESS;
}