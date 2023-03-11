#ifndef _VMX_H_
#define _VMX_H_

#ifdef __cplusplus
extern "C" {
#endif

// 16-Bit Control Fields
#define VMX_VPID                                0x00000000
#define VMX_PINV                                0x00000002
#define VMX_EPTP_INDEX                          0x00000004

// 32-Bit Control Fields
#define VMX_PIN_CONTROLS                        0x00004000
#define VMX_PRIMARY_PROCESSOR_CONTROLS          0x00004002
#define VMX_EXCEPTION_BITMAP                    0x00004004
#define VMX_PAGE_FAULT_ERROR_CODE_MASK          0x00004006
#define VMX_PAGE_FAULT_ERROR_CODE_MATCH         0x00004008
#define VMX_CR3_TARGET_COUNT                    0x0000400A
#define VMX_EXIT_CONTROLS                       0x0000400C
#define VMX_EXIT_MSR_STORE_COUNT                0x0000400E
#define VMX_EXIT_MSR_LOAD_COUNT                 0x00004010
#define VMX_ENTRY_CONTROLS                      0x00004012
#define VMX_ENTRY_MSR_LOAD_COUNT                0x00004014
#define VMX_ENTRY_INTERRUPT_INFO                0x00004016
#define VMX_ENTRY_EXCEPTION_ERROR_CODE          0x00004018
#define VMX_ENTRY_INSTRUCTION_LENGTH            0x0000401A
#define VMX_TPR_THRESHOLD                       0x0000401C
#define VMX_SECONDARY_PROCESSOR_CONTROLS        0x0000401E
#define VMX_PLE_GAP                             0x00004020
#define VMX_PLE_WINDOW                          0x00004022

// 64-Bit Control Fields
#define VMX_IO_BITMAP_A                         0x00002000
#define VMX_IO_BITMAP_B                         0x00002002
#define VMX_MSR_BITMAP                          0x00002004
#define VMX_EXIT_MSR_STORE_ADDRESS              0x00002006
#define VMX_EXIT_MSR_LOAD_ADDRESS               0x00002008
#define VMX_ENTRY_MSR_LOAD_ADDRESS              0x0000200A
#define VMX_EX_VMCS_POINTER                     0x0000200C
#define VMX_PML_ADDRESS                         0x0000200E
#define VMX_TSC_OFFSET                          0x00002010
#define VMX_VIRTUAL_APIC_ADDRESS                0x00002012
#define VMX_APIC_ACCESS_ADDRESS                 0x00002014
#define VMX_PIDA                                0x00002016
#define VMX_VM_FUNCTION_CONTROLS                0x00002018
#define VMX_EPT_POINTER                         0x0000201A
#define VMX_EOI_EXIT_BITMAP0                    0x0000201C
#define VMX_EOI_EXIT_BITMAP1                    0x0000201E
#define VMX_EOI_EXIT_BITMAP2                    0x00002020
#define VMX_EOI_EXIT_BITMAP3                    0x00002022
#define VMX_EPTP_LIST_ADDRESS                   0x00002024
#define VMX_VMREAD_BITMAP_ADDRESS               0x00002026
#define VMX_VMWRITE_BITMAP_ADDRESS              0x00002028
#define VMX_VIRTUAL_EXCEPTION_INFO_ADDRESS      0x0000202A
#define VMX_XSS_EXITING_BITMAP                  0x0000202C
#define VMX_ENCLS_EXITING_BITMAP                0x0000202E
#define VMX_SUB_PAGE_PERMISSION_TABLE_POINTER   0x00002030
#define VMX_TSC_MULTIPLIER                      0x00002032
#define VMX_TERTIARY_PROCESSOR_CONTROLS         0x00002034
#define VMX_ENCLV_EXITING_BITMAP                0x00002036

// Natural-Width Control Fields
#define VMX_CR0_MASK                            0x00006000
#define VMX_CR4_MASK                            0x00006002
#define VMX_CR0_READ_SHADOW                     0x00006004
#define VMX_CR4_READ_SHADOW                     0x00006006
#define VMX_CR3_TARGET_VALUE0                   0x00006008
#define VMX_CR3_TARGET_VALUE1                   0x0000600A
#define VMX_CR3_TARGET_VALUE2                   0x0000600C
#define VMX_CR3_TARGET_VALUE3                   0x0000600E

// 16-Bit Guest-State Fields
#define VMX_GUEST_ES_SELECTOR                   0x00000800
#define VMX_GUEST_CS_SELECTOR                   0x00000802
#define VMX_GUEST_SS_SELECTOR                   0x00000804
#define VMX_GUEST_DS_SELECTOR                   0x00000806
#define VMX_GUEST_FS_SELECTOR                   0x00000808
#define VMX_GUEST_GS_SELECTOR                   0x0000080A
#define VMX_GUEST_LDTR_SELECTOR                 0x0000080C
#define VMX_GUEST_TR_SELECTOR                   0x0000080E
#define VMX_GUEST_INTERRUPT_STATUS              0x00000810
#define VMX_PML_INDEX                           0x00000812

// 32-Bit Guest-State Fields
#define VMX_GUEST_ES_LIMIT                      0x00004800
#define VMX_GUEST_CS_LIMIT                      0x00004802
#define VMX_GUEST_SS_LIMIT                      0x00004804
#define VMX_GUEST_DS_LIMIT                      0x00004806
#define VMX_GUEST_FS_LIMIT                      0x00004808
#define VMX_GUEST_GS_LIMIT                      0x0000480A
#define VMX_GUEST_LDTR_LIMIT                    0x0000480C
#define VMX_GUEST_TR_LIMIT                      0x0000480E
#define VMX_GUEST_GDTR_LIMIT                    0x00004810
#define VMX_GUEST_IDTR_LIMIT                    0x00004812
#define VMX_GUEST_ES_AR                         0x00004814
#define VMX_GUEST_CS_AR                         0x00004816
#define VMX_GUEST_SS_AR                         0x00004818
#define VMX_GUEST_DS_AR                         0x0000481A
#define VMX_GUEST_FS_AR                         0x0000481C
#define VMX_GUEST_GS_AR                         0x0000481E
#define VMX_GUEST_LDTR_AR                       0x00004820
#define VMX_GUEST_TR_AR                         0x00004822
#define VMX_GUEST_INTERRUPTIBILITY_STATE        0x00004824
#define VMX_GUEST_ACTIVITY_STATE                0x00004826
#define VMX_GUEST_SMBASE                        0x00004828
#define VMX_GUEST_IA32_SYSENTER_CS              0x0000482A
#define VMX_PREEMPTION_TIMER_VALUE              0x0000482E

// 64-Bit Guest-State Fields
#define VMX_GUEST_VMCS_LINK_POINTER             0x00002800
#define VMX_GUEST_IA32_DEBUGCTL                 0x00002802
#define VMX_GUEST_IA32_PAT                      0x00002804
#define VMX_GUEST_IA32_EFER                     0x00002806
#define VMX_GUEST_IA32_PERF_GLOBAL_CTRL         0x00002808
#define VMX_GUEST_PDPTE0                        0x0000280A
#define VMX_GUEST_PDPTE1                        0x0000280C
#define VMX_GUEST_PDPTE2                        0x0000280E
#define VMX_GUEST_PDPTE3                        0x00002810
#define VMX_GUEST_IA32_BNDCFGS                  0x00002812
#define VMX_GUEST_IA32_RTIT_CTL                 0x00002814
#define VMX_GUEST_IA32_PKRS                     0x00002818

// Natural-Width Guest-State Fields
#define VMX_GUEST_CR0                           0x00006800
#define VMX_GUEST_CR3                           0x00006802
#define VMX_GUEST_CR4                           0x00006804
#define VMX_GUEST_ES_BASE                       0x00006806 
#define VMX_GUEST_CS_BASE                       0x00006808
#define VMX_GUEST_SS_BASE                       0x0000680A
#define VMX_GUEST_DS_BASE                       0x0000680C
#define VMX_GUEST_FS_BASE                       0x0000680E
#define VMX_GUEST_GS_BASE                       0x00006810
#define VMX_GUEST_LDTR_BASE                     0x00006812
#define VMX_GUEST_TR_BASE                       0x00006814
#define VMX_GUEST_GDTR_BASE                     0x00006816
#define VMX_GUEST_IDTR_BASE                     0x00006818
#define VMX_GUEST_DR7                           0x0000681A
#define VMX_GUEST_ESP                           0x0000681C
#define VMX_GUEST_RSP                           0x0000681C
#define VMX_GUEST_EIP                           0x0000681E
#define VMX_GUEST_RIP                           0x0000681E
#define VMX_GUEST_EFLAGS                        0x00006820
#define VMX_GUEST_RFLAGS                        0x00006820
#define VMX_GUEST_PENDING_DEBUG_EXCEPTIONS      0x00006822
#define VMX_GUEST_IA32_SYSENTER_ESP             0x00006824
#define VMX_GUEST_IA32_SYSENTER_EIP             0x00006826
#define VMX_GUEST_IA32_S_CET                    0x00006828
#define VMX_GUEST_SSP                           0x0000682A
#define VMX_GUEST_IA32_IST_ADDRESS              0x0000682C

// 16-Bit Host-State Fields
#define VMX_HOST_ES_SELECTOR                    0x00000C00
#define VMX_HOST_CS_SELECTOR                    0x00000C02
#define VMX_HOST_SS_SELECTOR                    0x00000C04
#define VMX_HOST_DS_SELECTOR                    0x00000C06
#define VMX_HOST_FS_SELECTOR                    0x00000C08
#define VMX_HOST_GS_SELECTOR                    0x00000C0A
#define VMX_HOST_TR_SELECTOR                    0x00000C0C

// 32-Bit Host-State Fields
#define VMX_HOST_IA32_SYSENTER_CS               0x00004C00

// 64-Bit Host-State Fields
#define VMX_HOST_IA32_PAT                       0x00002C00
#define VMX_HOST_IA32_EFER                      0x00002C02
#define VMX_HOST_IA32_PERF_GLOBAL_CTRL          0x00002C04
#define VMX_HOST_IA32_PKRS                      0x00002C06

// Natural-Width Host-State Fields
#define VMX_HOST_CR0                            0x00006C00
#define VMX_HOST_CR3                            0x00006C02
#define VMX_HOST_CR4                            0x00006C04
#define VMX_HOST_FS_BASE                        0x00006C06
#define VMX_HOST_GS_BASE                        0x00006C08
#define VMX_HOST_TR_BASE                        0x00006C0A
#define VMX_HOST_GDTR_BASE                      0x00006C0C
#define VMX_HOST_IDTR_BASE                      0x00006C0E
#define VMX_HOST_IA32_SYSENTER_ESP              0x00006C10
#define VMX_HOST_IA32_SYSENTER_EIP              0x00006C12
#define VMX_HOST_RSP                            0x00006C14
#define VMX_HOST_RIP                            0x00006C16
#define VMX_HOST_IA32_S_CET                     0x00006C18
#define VMX_HOST_SSP                            0x00006C1A
#define VMX_IA32_IST_ADDRESS                    0x00006C1C

// 32-Bit Read-Only Data Fields
#define VMX_INSTRUCTION_ERROR_CODE              0x00004400
#define VMX_EXIT_REASON                         0x00004402
#define VMX_EXIT_INTERRUPT_INFO                 0x00004404
#define VMX_EXIT_EXCEPTION_ERROR_CODE           0x00004406
#define VMX_IDT_VECTORING_INFO                  0x00004408
#define VMX_IDT_VECTORING_ERROR_CODE            0x0000440A
#define VMX_EXIT_INSTRUCTION_LENGTH             0x0000440C
#define VMX_EXIT_INSTRUCTION_INFO               0x0000440E

// 64-Bit Read-Only Data Fields
#define VMX_GUEST_PHYSICAL_ADDRESS              0x00002400

// Natural-Width Read-Only Data Fields
#define VMX_EXIT_INFO_QUALIFICATION             0x00006400
#define VMX_IO_RCX                              0x00006402
#define VMX_IO_RSI                              0x00006404
#define VMX_IO_RDI                              0x00006406
#define VMX_IO_RIP                              0x00006408
#define VMX_GUEST_LINEAR_ADDRESS                0x0000640A

// Pin Controls
#define PIN_EXT_INTERRUPT_EXITING                       0x00000001
#define PIN_NMI_EXITING                                 0x00000008
#define PIN_VIRTUAL_NMIS                                0x00000020
#define PIN_VMX_TIMER_EXITING                           0x00000040
#define PIN_PROCESS_POSTED_INTERRUPTS                   0x00000080

// Primary Controls
#define PRIMARY_INTERRUPT_WINDOW_EXITING                0x00000004
#define PRIMARY_USE_TSC_OFFSETTING                      0x00000008
#define PRIMARY_HLT_EXITING                             0x00000080
#define PRIMARY_INVLPG_EXITING                          0x00000200
#define PRIMARY_MWAIT_EXITING                           0x00000400
#define PRIMARY_RDPMC_EXITING                           0x00000800
#define PRIMARY_RDTSC_EXITING                           0x00001000
#define PRIMARY_CR3_LOAD_EXITING                        0x00008000
#define PRIMARY_CR3_STORE_EXITING                       0x00010000
#define PRIMARY_TERTIARY_CONTROLS                       0x00020000
#define PRIMARY_CR8_LOAD_EXITING                        0x00080000
#define PRIMARY_CR8_STORE_EXITING                       0x00100000
#define PRIMARY_USE_TPR_SHADOW                          0x00200000
#define PRIMARY_NMI_WINDOW_EXITING                      0x00400000
#define PRIMARY_DR_EXITING                              0x00800000
#define PRIMARY_IO_EXITING                              0x01000000
#define PRIMARY_IO_BITMAP_ACTIVE                        0x02000000
#define PRIMARY_MONITOR_TRAP_FLAG                       0x08000000
#define PRIMARY_MSR_BITMAP_ACTIVE                       0x10000000
#define PRIMARY_MONITOR_EXITING                         0x20000000
#define PRIMARY_PAUSE_EXITING                           0x40000000
#define PRIMARY_SECONDARY_CONTROLS                      0x80000000

// Secondary Controls
#define SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES         0x00000001
#define SECONDARY_EXEC_ENABLE_EPT                       0x00000002
#define SECONDARY_EXEC_DESCRIPTOR_TABLE_EXITING         0x00000004
#define SECONDARY_EXEC_RDTSCP					        0x00000008
#define SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE           0x00000010
#define SECONDARY_EXEC_ENABLE_VPID                      0x00000020
#define SECONDARY_EXEC_WBINVD_EXITING			        0x00000040
#define SECONDARY_EXEC_UNRESTRICTED_GUEST		        0x00000080
#define SECONDARY_EXEC_APIC_REGISTER_VIRT               0x00000100
#define SECONDARY_EXEC_VIRTUAL_INTR_DELIVERY            0x00000200
#define SECONDARY_EXEC_PAUSE_LOOP_EXITING		        0x00000400
#define SECONDARY_EXEC_RDRAND_EXITING		            0x00000800
#define SECONDARY_EXEC_ENABLE_INVPCID			        0x00001000
#define SECONDARY_EXEC_ENABLE_VMFUNCTIONS		        0x00002000
#define SECONDARY_EXEC_SHADOW_VMCS                      0x00004000
#define SECONDARY_EXEC_ENCLS_EXITING                    0x00008000
#define SECONDARY_EXEC_RDSEED_EXITING                   0x00010000
#define SECONDARY_EXEC_ENABLE_PML                       0x00020000
#define SECONDARY_EXEC_EPT_VIOLATION_VE                 0x00040000
#define SECONDARY_EXEC_CONCEAL_VMX_FROM_PT              0x00080000
#define SECONDARY_EXEC_ENABLE_XSAVES			        0x00100000
#define SECONDARY_EXEC_MODE_BASED_FOR_EPT			    0x00400000
#define SECONDARY_EXEC_SUBPAGE_WRITE_FOR_EPT			0x00800000
#define SECONDARY_EXEC_PA_USES_GUEST_PA			        0x01000000
#define SECONDARY_EXEC_USE_TSC_SCALING			        0x02000000
#define SECONDARY_EXEC_ENABLE_USER_WAIT_PAUSE			0x04000000
#define SECONDARY_EXEC_ENABLE_ENCLV_EXITING			    0x10000000

// Exit Controls
#define EXIT_CONTROL_SAVE_DEBUG_CONTROLS                0x00000004
#define EXIT_CONTROL_HOST_ADDR_SPACE_SIZE               0x00000200
#define EXIT_CONTROL_LOAD_PERF_GLOBAL_CTRL              0x00001000
#define EXIT_CONTROL_ACKNOWLEDGE_INTERRUPT              0x00008000
#define EXIT_CONTROL_SAVE_PAT                           0x00040000
#define EXIT_CONTROL_LOAD_PAT                           0x00080000
#define EXIT_CONTROL_SAVE_EFER                          0x00100000
#define EXIT_CONTROL_LOAD_EFER                          0x00200000
#define EXIT_CONTROL_SAVE_VMX_TIMER                     0x00400000
#define EXIT_CONTROL_CLEAR_BNDCFGS                      0x00800000
#define EXIT_CONTROL_CONCEAL_VMX_FROM_PT                0x01000000
#define EXIT_CONTROL_CLEAR_RTIT_CTL                     0x02000000
#define EXIT_CONTROL_LOAD_CET_STATE                     0x04000000
#define EXIT_CONTROL_LOAD_PKRS                          0x08000000

// Entry Controls
#define ENTRY_CONTROL_LOAD_DEBUG_CONTROLS               0x00000004
#define ENTRY_CONTROL_LONG_MODE_GUEST                   0x00000200
#define ENTRY_CONTROL_ENTRY_TO_SMM                      0x00000400
#define ENTRY_CONTROL_TEAR_DOWN_SMM_MONITOR             0x00000800
#define ENTRY_CONTROL_LOAD_PERF_GLOBAL_CTRL             0x00002000
#define ENTRY_CONTROL_LOAD_PAT                          0x00004000
#define ENTRY_CONTROL_LOAD_EFER                         0x00008000
#define ENTRY_CONTROL_LOAD_BNDCFGS                      0x00010000
#define ENTRY_CONTROL_CONCEAL_VMX_FROM_PT               0x00020000
#define ENTRY_CONTROL_LOAD_RTIT_CTL                     0x00040000
#define ENTRY_CONTROL_LOAD_CET_STATE                    0x00080000
#define ENTRY_CONTROL_LOAD_PKRS                         0x00100000

// Interruptibility State
#define INTERRUPTIBILITY_BLOCKING_STI      0x00000001
#define INTERRUPTIBILITY_BLOCKING_MOV_SS   0x00000002
#define INTERRUPTIBILITY_BLOCKING_SMI      0x00000004
#define INTERRUPTIBILITY_BLOCKING_NMI      0x00000008
#define INTERRUPTIBILITY_ENCLAVE_INT       0x00000010

// Pending Debug Exceptions
#define PENDING_DEBUG_B0                   0x00000001
#define PENDING_DEBUG_B1                   0x00000002
#define PENDING_DEBUG_B2                   0x00000004
#define PENDING_DEBUG_B3                   0x00000008
#define PENDING_DEBUG_ENABLED_BREAKPOINT   0x00001000
#define PENDING_DEBUG_BS                   0x00004000

#define VmxAccessRights(AR) \
    ((AR & 0x80) == 0 ? (AR | 0x10000) : AR)

#define ENCODE_16           0
#define ENCODE_64           1
#define ENCODE_32           2
#define ENCODE_NATURAL      3

#define ENCODE_MASK         3
#define ENCODE_SHIFT        13

#define VMX_SUCCEED         0
#define VMX_FAIL_INVALID    1
#define VMX_FAIL_VALID      2

__inline int __vmx_read_auto(int field, void* pointer)
{
    unsigned int state;
    unsigned __int64 value;

    state = __ins_vmread(field, &value);
    
    if (VMX_SUCCEED == state) {
        switch ((field >> ENCODE_SHIFT) & ENCODE_MASK) {
        case ENCODE_16:
            *(unsigned __int16*)pointer = value & 0xFFFF;
            break;
        case ENCODE_32:
            *(unsigned __int32*)pointer = value & 0xFFFFFFFF;
            break;
#ifndef _WIN64
        case ENCODE_NATURAL:
            *(unsigned __int32*)pointer = value & 0xFFFFFFFF;
            break;
        case ENCODE_64:
            __ins_vmread(field + 1, (unsigned __int32*)&value + 1);
            *(unsigned __int64*)pointer = value;
            break;
#else
        case ENCODE_NATURAL:
            *(unsigned __int64*)pointer = value;
            break;
        case ENCODE_64:
            *(unsigned __int64*)pointer = value;
            break;
#endif
        default:
            state = VMX_FAIL_INVALID;
            break;
        }
    }

    return state;
}

__inline int __vmx_write_auto(int field, unsigned __int64 value)
{
    unsigned int state;

    if (VMX_SUCCEED == state) {
        switch ((field >> ENCODE_SHIFT) & ENCODE_MASK) {
        case ENCODE_16:
            state = __ins_vmwrite(field, value & 0xFFFF);
            break;
        case ENCODE_32:
            state = __ins_vmwrite(field, value & 0xFFFFFFFF);
            break;
#ifndef _WIN64
        case ENCODE_NATURAL:
            state = __ins_vmwrite(field, value & 0xFFFFFFFF);
            break;
        case ENCODE_64:
            state = __ins_vmwrite(field, value & 0xFFFFFFFF);
            __ins_vmwrite(field + 1, value >> 32);
            break;
#else
        case ENCODE_NATURAL:
            state = __ins_vmwrite(field, value);
            break;
        case ENCODE_64:
            state = __ins_vmwrite(field, value);
            break;
#endif
        default:
            state = VMX_FAIL_INVALID;
            break;
        }
    }

    return state;
}

#define __vmx_read __vmx_read_auto
#define __vmx_write __vmx_write_auto

#define VmxEnableMsrRead(Bitmap, Msr) \
            *((PUCHAR)Bitmap + \
                (((Msr) & 0xC0000000) == 0 ? 0 : 0x400) + \
                    (((Msr) & 0x1FFF) >> 3)) |= 1 << ((Msr) & 7)

#define VmxEnableMsrWrite(Bitmap, Msr) \
            *((PUCHAR)Bitmap + \
                (((Msr) & 0xC0000000) == 0 ? 0x800 : 0xC00) + \
                    (((Msr) & 0x1FFF) >> 3)) |= 1 << ((Msr) & 7)

#define VmxDisableMsrRead(Bitmap, Msr) \
            *((PUCHAR)Bitmap + \
                (((Msr) & 0xC0000000) == 0 ? 0 : 0x400) + \
                    (((Msr) & 0x1FFF) >> 3)) &= ~(1 << ((Msr) & 7))

#define VmxDisableMsrWrite(Bitmap, Msr) \
            *((PUCHAR)Bitmap + \
                (((Msr) & 0xC0000000) == 0 ? 0x800 : 0xC00) + \
                    (((Msr) & 0x1FFF) >> 3)) &= ~(1 << ((Msr) & 7))

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

} VMX_BASIC, * PVMX_BASIC;

#ifdef __cplusplus
}
#endif

#endif
