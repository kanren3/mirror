#ifndef _SVM_H_
#define _SVM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SVM_INTERCEPT_READ_CR               0x00000000
#define SVM_INTERCEPT_WRITE_CR              0x00000002
#define SVM_INTERCEPT_READ_DR               0x00000004
#define SVM_INTERCEPT_WRITE_DR              0x00000006
#define SVM_INTERCEPT_EXCEPTION_VECTORS     0x00000008
#define SVM_INTERCEPT_CTLS1                 0x0000000C
#define SVM_INTERCEPT_CTLS2                 0x00000010
#define SVM_INTERCEPT_CTLS3                 0x00000014
#define SVM_PAUSE_FILTER_THRESHOLD          0x0000003C
#define SVM_PAUSE_FILTER_COUNT              0x0000003E
#define SVM_IOPM_BASE_PA                    0x00000040
#define SVM_MSRPM_BASE_PA                   0x00000048
#define SVM_TSC_OFFSET                      0x00000050
#define SVM_GUEST_ASID                      0x00000058
#define SVM_TLB_CONTROL                     0x0000005C
#define SVM_AVIC_CONTROL                    0x00000060
#define SVM_GUEST_INTERCEPT_CONTROL         0x00000068
#define SVM_EXIT_CODE                       0x00000070
#define SVM_EXIT_INFO1                      0x00000078
#define SVM_EXIT_INFO2                      0x00000080
#define SVM_EXIT_INTERCEPT_INFO             0x00000088
#define SVM_NPT_CONTROL                     0x00000090
#define SVM_AVIC_APIC_BASE                  0x00000098
#define SVM_GHCB_PA                         0x000000A0
#define SVM_EVENT_INJECTION                 0x000000A8
#define SVM_EVENT_ERROR_CODE                0x000000AC
#define SVM_NPT_CR3                         0x000000B0
#define SVM_LBR_VIRTUAL_CONTROL             0x000000B8
#define SVM_VMCB_CLEAN_BITS                 0x000000C0
#define SVM_NEXT_EIP                        0x000000C8
#define SVM_NEXT_RIP                        0x000000C8
#define SVM_NUMBER_OF_BYTES_FETCHED         0x000000D0
#define SVM_GUEST_INSTRUCTION_BYTES         0x000000D1
#define SVM_AVIC_BACKING_PAGE_POINTER       0x000000E0
#define SVM_AVIC_LOGICAL_TABLE_POINTER      0x000000F0
#define SVM_AVIC_PHYSICAL_TABLE_POINTER     0x000000F8
#define SVM_VMSA_POINTER                    0x00000108
#define SVM_GUEST_ES_SELECTOR               0x00000400
#define SVM_GUEST_ES_ATTRIB                 0x00000402
#define SVM_GUEST_ES_LIMIT                  0x00000404
#define SVM_GUEST_ES_BASE                   0x00000408
#define SVM_GUEST_CS_SELECTOR               0x00000410
#define SVM_GUEST_CS_ATTRIB                 0x00000412
#define SVM_GUEST_CS_LIMIT                  0x00000414
#define SVM_GUEST_CS_BASE                   0x00000418
#define SVM_GUEST_SS_SELECTOR               0x00000420
#define SVM_GUEST_SS_ATTRIB                 0x00000422
#define SVM_GUEST_SS_LIMIT                  0x00000424
#define SVM_GUEST_SS_BASE                   0x00000428
#define SVM_GUEST_DS_SELECTOR               0x00000430
#define SVM_GUEST_DS_ATTRIB                 0x00000432
#define SVM_GUEST_DS_LIMIT                  0x00000434
#define SVM_GUEST_DS_BASE                   0x00000438
#define SVM_GUEST_FS_SELECTOR               0x00000440
#define SVM_GUEST_FS_ATTRIB                 0x00000442
#define SVM_GUEST_FS_LIMIT                  0x00000444
#define SVM_GUEST_FS_BASE                   0x00000448
#define SVM_GUEST_GS_SELECTOR               0x00000450
#define SVM_GUEST_GS_ATTRIB                 0x00000452
#define SVM_GUEST_GS_LIMIT                  0x00000454
#define SVM_GUEST_GS_BASE                   0x00000458
#define SVM_GUEST_GDTR_SELECTOR             0x00000460
#define SVM_GUEST_GDTR_ATTRIB               0x00000462
#define SVM_GUEST_GDTR_LIMIT                0x00000464
#define SVM_GUEST_GDTR_BASE                 0x00000468
#define SVM_GUEST_LDTR_SELECTOR             0x00000470
#define SVM_GUEST_LDTR_ATTRIB               0x00000472
#define SVM_GUEST_LDTR_LIMIT                0x00000474
#define SVM_GUEST_LDTR_BASE                 0x00000478
#define SVM_GUEST_IDTR_SELECTOR             0x00000480
#define SVM_GUEST_IDTR_ATTRIB               0x00000482
#define SVM_GUEST_IDTR_LIMIT                0x00000484
#define SVM_GUEST_IDTR_BASE                 0x00000488
#define SVM_GUEST_TR_SELECTOR               0x00000490
#define SVM_GUEST_TR_ATTRIB                 0x00000492
#define SVM_GUEST_TR_LIMIT                  0x00000494
#define SVM_GUEST_TR_BASE                   0x00000498
#define SVM_GUEST_CPL                       0x000004CB
#define SVM_GUEST_EFER                      0x000004D0
#define SVM_GUEST_CR4                       0x00000548
#define SVM_GUEST_CR3                       0x00000550
#define SVM_GUEST_CR0                       0x00000558
#define SVM_GUEST_DR7                       0x00000560
#define SVM_GUEST_DR6                       0x00000568
#define SVM_GUEST_EFLAGS                    0x00000570
#define SVM_GUEST_RFLAGS                    0x00000570
#define SVM_GUEST_EIP                       0x00000578
#define SVM_GUEST_RIP                       0x00000578
#define SVM_GUEST_ESP                       0x000005D8
#define SVM_GUEST_RSP                       0x000005D8
#define SVM_GUEST_SCET                      0x000005E0
#define SVM_GUEST_SSP                       0x000005E8
#define SVM_GUEST_ISST                      0x000005F0
#define SVM_GUEST_EAX                       0x000005F8
#define SVM_GUEST_RAX                       0x000005F8
#define SVM_GUEST_STAR                      0x00000600
#define SVM_GUEST_LSTAR                     0x00000608
#define SVM_GUEST_CSTAR                     0x00000610
#define SVM_GUEST_SFMASK                    0x00000618
#define SVM_GUEST_KERNEL_GS_BASE            0x00000620
#define SVM_GUEST_SYSENTER_CS               0x00000628
#define SVM_GUEST_SYSENTER_ESP              0x00000630
#define SVM_GUEST_SYSENTER_EIP              0x00000638
#define SVM_GUEST_CR2                       0x00000640
#define SVM_GUEST_PAT                       0x00000668
#define SVM_GUEST_DBGCTL                    0x00000670
#define SVM_GUEST_BR_FROM                   0x00000678
#define SVM_GUEST_BR_TO                     0x00000680
#define SVM_GUEST_LASTEXCPFROM              0x00000688
#define SVM_GUEST_SPEC_CTRL                 0x000006E0

#define SVM_VMEXIT_CPUID        0x72
#define SVM_VMEXIT_MSR          0x7C
#define SVM_VMEXIT_VMRUN        0x80
#define SVM_VMEXIT_VMMCALL      0x81
#define SVM_VMEXIT_EXCP_FIRST   0x40
#define SVM_VMEXIT_EXCP_PF      0x4E
#define SVM_VMEXIT_EXCP_LAST    0x5F

#define SVM_INTERCEPT_CTLS1_CPUID                (1UL << 18)
#define SVM_INTERCEPT_CTLS1_MSR_PROT             (1UL << 28)

#define SVM_INTERCEPT_CTLS2_VMRUN                (1UL << 0)
#define SVM_INTERCEPT_CTLS2_VMMCALL              (1UL << 1)

#define SvmAccessRights(AR) \
    (USHORT)((AR & 0xFF) | ((AR & 0xF000) >> 4))

#define __svm_read8(Vmcb, Offset, Value) \
    *(PUCHAR)(Value) = *(PUCHAR)((PUCHAR)(Vmcb) + Offset)

#define __svm_read16(Vmcb, Offset, Value) \
    *(PUSHORT)(Value) = *(PUSHORT)((PUCHAR)(Vmcb) + Offset)

#define __svm_read32(Vmcb, Offset, Value) \
    *(PULONG)(Value) = *(PULONG)((PUCHAR)(Vmcb) + Offset)

#define __svm_read64(Vmcb, Offset, Value) \
    *(PULONG64)(Value) = *(PULONG64)((PUCHAR)(Vmcb) + Offset)

#define __svm_read_ptr(Vmcb, Offset, Value) \
    *(PULONG_PTR)(Value) = *(PULONG_PTR)((PUCHAR)(Vmcb) + Offset)

#define __svm_write8(Vmcb, Offset, Value) \
    *(PUCHAR)((PUCHAR)(Vmcb) + Offset) = (UCHAR)(Value)

#define __svm_write16(Vmcb, Offset, Value) \
    *(PUSHORT)((PUCHAR)(Vmcb) + Offset) = (USHORT)(Value)

#define __svm_write32(Vmcb, Offset, Value) \
    *(PULONG)((PUCHAR)(Vmcb) + Offset) = (ULONG)(Value)

#define __svm_write64(Vmcb, Offset, Value) \
    *(PULONG64)((PUCHAR)(Vmcb) + Offset) = (ULONG64)(Value)

#define __svm_write_ptr(Vmcb, Offset, Value) \
    *(PULONG_PTR)((PUCHAR)(Vmcb) + Offset) = (ULONG_PTR)(Value)

#define SvmEnableMsrRead(Bitmap, Msr) \
            *((PUCHAR)Bitmap + \
                (((Msr) & 0xC0010000) == 0xC0010000 ? 0x1000 : \
                    ((Msr) & 0xC0000000) == 0xC0000000 ? 0x800 : 0) + \
                        (((Msr) & 0x1FFF) >> 2)) |= 1 << (((Msr) & 3) << 1)

#define SvmEnableMsrWrite(Bitmap, Msr) \
            *((PUCHAR)Bitmap + \
                (((Msr) & 0xC0010000) == 0xC0010000 ? 0x1000 : \
                    ((Msr) & 0xC0000000) == 0xC0000000 ? 0x800 : 0) + \
                        (((Msr) & 0x1FFF) >> 2)) |= 2 << (((Msr) & 3) << 1)

#define SvmDisableMsrRead(Bitmap, Msr) \
            *((PUCHAR)Bitmap + \
                (((Msr) & 0xC0010000) == 0xC0010000 ? 0x1000 : \
                    ((Msr) & 0xC0000000) == 0xC0000000 ? 0x800 : 0) + \
                        (((Msr) & 0x1FFF) >> 2)) &= ~(1 << (((Msr) & 3) << 1))

#define SvmDisableMsrWrite(Bitmap, Msr) \
            *((PUCHAR)Bitmap + \
                (((Msr) & 0xC0010000) == 0xC0010000 ? 0x1000 : \
                    ((Msr) & 0xC0000000) == 0xC0000000 ? 0x800 : 0) + \
                        (((Msr) & 0x1FFF) >> 2)) &= ~(2 << (((Msr) & 3) << 1))

#ifdef __cplusplus
}
#endif

#endif
