include ksamd64.inc
include macamd64.inc

    LEAF_ENTRY __ins_cpuidex, _TEXT$00

    push rbx

    mov eax, ecx
    mov ecx, edx
    
    cpuid

    mov [r8], eax
    mov [r8 + 4], ebx
    mov [r8 + 8], ecx
    mov [r8 + 0ch], edx

    pop rbx
    ret

    LEAF_END __ins_cpuidex, _TEXT$00

end
