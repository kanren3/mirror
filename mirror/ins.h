#ifndef _INS_H_
#define _INS_H_

#ifdef __cplusplus
extern "C" {
#endif

    void __stdcall __ins_cpuidex(int function, int subfunction, int* cpuinfo);

#ifdef __cplusplus
}
#endif

#endif
