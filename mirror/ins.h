#ifndef _INS_H_
#define _INS_H_

#ifdef __cplusplus
extern "C" {
#endif

__MACHINEX64(void __stdcall __ins_cpuidex(int func, int subfunc, int* info))
__MACHINEX86(void __stdcall __ins_cpuidex(int func, int subfunc, int* info))

__MACHINEX64(unsigned __int64 __stdcall __ins_rdmsr(int reg))
__MACHINEX86(unsigned __int64 __stdcall __ins_rdmsr(int reg))

__MACHINEX64(void __stdcall __ins_wrmsr(int reg, unsigned __int64 value))
__MACHINEX86(void __stdcall __ins_wrmsr(int reg, unsigned __int64 value))

__MACHINEX64(unsigned __int64 __stdcall __ins_readcr(int id))
__MACHINEX86(unsigned int __stdcall __ins_readcr(int id))

__MACHINEX64(void __stdcall __ins_writecr(int id, unsigned __int64 value))
__MACHINEX86(void __stdcall __ins_writecr(int id, unsigned int value))

__MACHINEX64(unsigned __int64 __stdcall __ins_readdr(int id))
__MACHINEX86(unsigned int __stdcall __ins_readdr(int id))

__MACHINEX64(void __stdcall __ins_writedr(int id, unsigned __int64 value))
__MACHINEX86(void __stdcall __ins_writedr(int id, unsigned int value))

__MACHINEX64(unsigned __int64 __stdcall __ins_rdtsc(void))
__MACHINEX86(unsigned __int64 __stdcall __ins_rdtsc(void))

__MACHINEX64(unsigned __int64 __stdcall __ins_rdtscp(unsigned int aux))
__MACHINEX86(unsigned __int64 __stdcall __ins_rdtscp(unsigned int aux))

__MACHINEX64(unsigned __int64 __stdcall __ins_xgetbv(unsigned int xcr))
__MACHINEX86(unsigned __int64 __stdcall __ins_xgetbv(unsigned int xcr))

__MACHINEX64(void __stdcall __ins_xsetbv(unsigned int xcr, unsigned __int64 value))
__MACHINEX86(void __stdcall __ins_xsetbv(unsigned int xcr, unsigned __int64 value))

__MACHINEX64(void __stdcall __ins_invd(void))
__MACHINEX86(void __stdcall __ins_invd(void))

__MACHINEX64(void __stdcall __ins_wbinvd(void))
__MACHINEX86(void __stdcall __ins_wbinvd(void))

__MACHINEX64(void __stdcall __ins_sgdt(void* gdtr))
__MACHINEX86(void __stdcall __ins_sgdt(void* gdtr))

__MACHINEX64(void __stdcall __ins_lgdt(void* gdtr))
__MACHINEX86(void __stdcall __ins_lgdt(void* gdtr))

__MACHINEX64(void __stdcall __ins_sidt(void* idtr))
__MACHINEX86(void __stdcall __ins_sidt(void* idtr))

__MACHINEX64(void __stdcall __ins_lidt(void* idtr))
__MACHINEX86(void __stdcall __ins_lidt(void* idtr))

__MACHINEX64(int __stdcall __ins_vmxon(unsigned __int64* vmon))
__MACHINEX86(int __stdcall __ins_vmxon(unsigned __int64* vmon))

__MACHINEX64(int __stdcall __ins_vmxoff(void))
__MACHINEX86(int __stdcall __ins_vmxoff(void))

__MACHINEX64(int __stdcall __ins_vmclear(unsigned __int64* vmcs))
__MACHINEX86(int __stdcall __ins_vmclear(unsigned __int64* vmcs))

__MACHINEX64(int __stdcall __ins_vmptrld(unsigned __int64* vmcs))
__MACHINEX86(int __stdcall __ins_vmptrld(unsigned __int64* vmcs))

__MACHINEX64(int __stdcall __ins_vmread(int field, void* value))
__MACHINEX86(int __stdcall __ins_vmread(int field, void* value))

__MACHINEX64(int __stdcall __ins_vmwrite(int field, void* value))
__MACHINEX86(int __stdcall __ins_vmwrite(int field, void* value))

__MACHINEX64(int __stdcall __ins_vmlaunch(void))
__MACHINEX86(int __stdcall __ins_vmlaunch(void))

__MACHINEX64(int __stdcall __ins_vmresume(void))
__MACHINEX86(int __stdcall __ins_vmresume(void))

__MACHINEX64(void __stdcall __ins_vmcall(int, void*))
__MACHINEX86(void __stdcall __ins_vmcall(int, void*))

__MACHINEX64(void __stdcall __ins_clgi(void))
__MACHINEX86(void __stdcall __ins_clgi(void))

__MACHINEX64(void __stdcall __ins_stgi(void))
__MACHINEX86(void __stdcall __ins_stgi(void))

__MACHINEX64(void __stdcall __ins_svmon(void))
__MACHINEX86(void __stdcall __ins_svmon(void))

__MACHINEX64(void __stdcall __ins_svmoff(void))
__MACHINEX86(void __stdcall __ins_svmoff(void))

__MACHINEX64(void __stdcall __ins_vmmcall(int, void*))
__MACHINEX86(void __stdcall __ins_vmmcall(int, void*))

#ifdef __cplusplus
}
#endif

#endif
