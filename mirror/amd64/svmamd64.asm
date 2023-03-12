include ksamd64.inc
include macamd64.inc

GsRax equ 0h
GsRcx equ 8h
GsRdx equ 10h
GsRbx equ 18h
GsRsp equ 20h
GsRbp equ 28h
GsRsi equ 30h
GsRdi equ 38h
GsR8 equ 40h
GsR9 equ 48h
GsR10 equ 50h
GsR11 equ 58h
GsR12 equ 60h
GsR13 equ 68h
GsR14 equ 70h
GsR15 equ 78h
GsRip equ 80h
GsRFlags equ 88h
GsSegEs equ 90h
GsSegCs equ 92h
GsSegSs equ 94h
GsSegDs equ 96h
GsSegFs equ 98h
GsSegGs equ 9Ah
GsLdtr equ 9Ch
GsTr equ 9Eh
GsGdtr equ 0A6h
GsIdtr equ 0B6h
GsCr0 equ 0C0h
GsCr2 equ 0D0h
GsCr3 equ 0D8h
GsCr4 equ 0E0h
GsCr8 equ 100h
GsDr0 equ 108h
GsDr1 equ 110h
GsDr2 equ 118h
GsDr3 equ 120h
GsDr6 equ 138h
GsDr7 equ 140h
GsMax equ 150h

extern SvmFirstEntry:proc

    LEAF_ENTRY SvmPrepareStartup, _TEXT$00

        push rbx
        push rbp
        push rsi
        push rdi
        push r12
        push r13
        push r14
        push r15
        sub rsp, GsMax + 28h

        lea rdx, [rsp + 28h]

        mov [rdx + GsRax], rax
        mov [rdx + GsRcx], rcx
        mov [rdx + GsRdx], rdx
        mov [rdx + GsRbx], rbx
        mov [rdx + GsRsp], rsp
        mov [rdx + GsRbp], rbp
        mov [rdx + GsRsi], rsi
        mov [rdx + GsRdi], rdi
        mov [rdx + GsR8], r8
        mov [rdx + GsR9], r9
        mov [rdx + GsR10], r10
        mov [rdx + GsR11], r11
        mov [rdx + GsR12], r12
        mov [rdx + GsR13], r13
        mov [rdx + GsR14], r14
        mov [rdx + GsR15], r15

        lea rax, Succeed
        mov [rdx + GsRip], rax
        
        pushfq
        pop [rdx + GsRFlags]

        mov [rdx + GsSegEs], es
        mov [rdx + GsSegCs], cs
        mov [rdx + GsSegSs], ss
        mov [rdx + GsSegDs], ds
        mov [rdx + GsSegFs], fs
        mov [rdx + GsSegGs], gs
        
        sldt word ptr [rdx + GsLdtr]
        str word ptr [rdx + GsTr]
        
        sgdt fword ptr [rdx + GsGdtr]
        sidt fword ptr [rdx + GsIdtr]

        mov rax, cr0
        mov [rdx + GsCr0], rax
        mov rax, cr2
        mov [rdx + GsCr2], rax
        mov rax, cr3
        mov [rdx + GsCr3], rax
        mov rax, cr4
        mov [rdx + GsCr4], rax
        mov rax, cr8
        mov [rdx + GsCr8], rax
        
        mov rax, dr0
        mov [rdx + GsDr0], rax
        mov rax, dr1
        mov [rdx + GsDr1], rax
        mov rax, dr2
        mov [rdx + GsDr2], rax
        mov rax, dr3
        mov [rdx + GsDr3], rax
        mov rax, dr6
        mov [rdx + GsDr6], rax
        mov rax, dr7
        mov [rdx + GsDr7], rax

        call SvmFirstEntry

Failed:
        jmp Complete
Succeed:
        xor eax, eax
Complete:
        add rsp, GsMax + 28h
        pop r15
        pop r14
        pop r13
        pop r12
        pop rdi
        pop rsi
        pop rbp
        pop rbx
        ret

    LEAF_END SvmPrepareStartup, _TEXT$00

end
