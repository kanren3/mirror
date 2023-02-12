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

    LEAF_ENTRY __ins_rdmsr, _TEXT$00

        rdmsr

        shl rdx, 20h
        or rax, rdx

        ret

    LEAF_END __ins_rdmsr, _TEXT$00

    LEAF_ENTRY __ins_wrmsr, _TEXT$00

        mov eax, edx
        shr rdx, 20h
        
        wrmsr
        
        ret

    LEAF_END __ins_wrmsr, _TEXT$00

    LEAF_ENTRY __ins_readcr, _TEXT$00

        xor rax, rax

        cmp ecx, 0
        jz Bcr0
        cmp ecx, 2
        jz Bcr2
        cmp ecx, 3
        jz Bcr3
        cmp ecx, 4
        jz Bcr4
        cmp ecx, 8
        jz Bcr8
        jmp Finish

Bcr0:
        mov rax, cr0
        jmp Finish
Bcr2:
        mov rax, cr2
        jmp Finish
Bcr3:
        mov rax, cr3
        jmp Finish
Bcr4:
        mov rax, cr4
        jmp Finish
Bcr8:
        mov rax, cr8

Finish:
        ret

    LEAF_END __ins_readcr, _TEXT$00

    LEAF_ENTRY __ins_writecr, _TEXT$00

        cmp ecx, 0
        jz Bcr0
        cmp ecx, 2
        jz Bcr2
        cmp ecx, 3
        jz Bcr3
        cmp ecx, 4
        jz Bcr4
        cmp ecx, 8
        jz Bcr8
        jmp Finish

Bcr0:
        mov cr0, rdx
        jmp Finish
Bcr2:
        mov cr2, rdx
        jmp Finish
Bcr3:
        mov cr3, rdx
        jmp Finish
Bcr4:
        mov cr4, rdx
        jmp Finish
Bcr8:
        mov cr8, rdx

Finish:
        ret

    LEAF_END __ins_writecr, _TEXT$00

    LEAF_ENTRY __ins_readdr, _TEXT$00

        xor rax, rax

        cmp ecx, 0
        jz Bdr0
        cmp ecx, 1
        jz Bdr1
        cmp ecx, 2
        jz Bdr2
        cmp ecx, 3
        jz Bdr3
        cmp ecx, 6
        jz Bdr6
        cmp ecx, 7
        jz Bdr7
        jmp Finish

Bdr0:
        mov rax, dr0
        jmp Finish
Bdr1:
        mov rax, dr1
        jmp Finish
Bdr2:
        mov rax, dr2
        jmp Finish
Bdr3:
        mov rax, dr3
        jmp Finish
Bdr6:
        mov rax, dr6
        jmp Finish
Bdr7:
        mov rax, dr7

Finish:
        ret

    LEAF_END __ins_readdr, _TEXT$00

    LEAF_ENTRY __ins_writedr, _TEXT$00

        cmp ecx, 0
        jz Bdr0
        cmp ecx, 1
        jz Bdr1
        cmp ecx, 2
        jz Bdr2
        cmp ecx, 3
        jz Bdr3
        cmp ecx, 6
        jz Bdr6
        cmp ecx, 7
        jz Bdr7
        jmp Finish

Bdr0:
        mov dr0, rdx
        jmp Finish
Bdr1:
        mov dr1, rdx
        jmp Finish
Bdr2:
        mov dr2, rdx
        jmp Finish
Bdr3:
        mov dr3, rdx
        jmp Finish
Bdr6:
        mov dr6, rdx
        jmp Finish
Bdr7:
        mov dr7, rdx

Finish:
        ret

    LEAF_END __ins_writedr, _TEXT$00

    LEAF_ENTRY __ins_rdtsc, _TEXT$00

        rdtsc
        
        shl rdx, 20h
        or rax, rdx
        
        ret

    LEAF_END __ins_rdtsc, _TEXT$00

    LEAF_ENTRY __ins_rdtscp, _TEXT$00

        mov r8, rcx

        rdtscp
        
        mov [r8], ecx

        shl rdx, 20h
        or rax, rdx
        
        ret

    LEAF_END __ins_rdtscp, _TEXT$00

    LEAF_ENTRY __ins_xsetbv, _TEXT$00

        mov eax, edx
        shr rdx, 20h

        xsetbv

        ret

    LEAF_END __ins_xsetbv, _TEXT$00

    LEAF_ENTRY __ins_invd, _TEXT$00

        invd
        ret

    LEAF_END __ins_invd, _TEXT$00

    LEAF_ENTRY __ins_wbinvd, _TEXT$00

        wbinvd
        ret

    LEAF_END __ins_wbinvd, _TEXT$00

    LEAF_ENTRY __ins_sgdt, _TEXT$00

        sgdt fword ptr [rcx]
        ret

    LEAF_END __ins_sgdt, _TEXT$00

    LEAF_ENTRY __ins_lgdt, _TEXT$00

        lgdt fword ptr [rcx]
        ret

    LEAF_END __ins_lgdt, _TEXT$00

    LEAF_ENTRY __ins_sidt, _TEXT$00

        sidt fword ptr [rcx]
        ret

    LEAF_END __ins_sidt, _TEXT$00

    LEAF_ENTRY __ins_lidt, _TEXT$00

        lidt fword ptr [rcx]
        ret

    LEAF_END __ins_lidt, _TEXT$00

    LEAF_ENTRY __ins_vmxon, _TEXT$00

        vmxon qword ptr [rcx]
        
        setz al
        setb ah
        adc al, ah
        and rax, 3

        ret

    LEAF_END __ins_vmxon, _TEXT$00

    LEAF_ENTRY __ins_vmxoff, _TEXT$00

        vmxoff
        
        setz al
        setb ah
        adc al, ah
        and rax, 3

        ret

    LEAF_END __ins_vmxoff, _TEXT$00

    LEAF_ENTRY __ins_vmclear, _TEXT$00

        vmclear qword ptr [rcx]
        
        setz al
        setb ah
        adc al, ah
        and rax, 3
        
        ret

    LEAF_END __ins_vmclear, _TEXT$00

    LEAF_ENTRY __ins_vmptrld, _TEXT$00

        vmptrld qword ptr [rcx]
        
        setz al
        setb ah
        adc al, ah
        and rax, 3
        
        ret

    LEAF_END __ins_vmptrld, _TEXT$00

    LEAF_ENTRY __ins_vmread, _TEXT$00

        xor rax, rax
        vmread rax, rcx
        mov [rdx], rax
        
        setz al
        setb ah
        adc al, ah
        and rax, 3
        
        ret

    LEAF_END __ins_vmread, _TEXT$00

    LEAF_ENTRY __ins_vmwrite, _TEXT$00

        vmwrite rcx, rdx
    
        setz al
        setb ah
        adc al, ah
        and rax, 3

        ret

    LEAF_END __ins_vmwrite, _TEXT$00

    LEAF_ENTRY __ins_vmlaunch, _TEXT$00

        vmlaunch
        
        setz al
        setb ah
        adc al, ah
        and rax, 3
        
        ret

    LEAF_END __ins_vmlaunch, _TEXT$00

    LEAF_ENTRY __ins_vmresume, _TEXT$00

        vmresume
        
        setz al
        setb ah
        adc al, ah
        and rax, 3
        
        ret

    LEAF_END __ins_vmresume, _TEXT$00

    LEAF_ENTRY __ins_vmcall, _TEXT$00

        vmcall
        ret

    LEAF_END __ins_vmcall, _TEXT$00

    LEAF_ENTRY __ins_clgi, _TEXT$00

        clgi
        ret

    LEAF_END __ins_clgi, _TEXT$00

    LEAF_ENTRY __ins_stgi, _TEXT$00

        stgi
        ret

    LEAF_END __ins_stgi, _TEXT$00

    LEAF_ENTRY __ins_svmon, _TEXT$00

        mov ecx, 0C0000080h
        rdmsr

        or eax, 01000h
        wrmsr
        ret

    LEAF_END __ins_svmon, _TEXT$00

    LEAF_ENTRY __ins_svmoff, _TEXT$00

        mov ecx, 0C0000080h
        rdmsr

        and eax, 0FFFFEFFFh
        wrmsr
        ret

    LEAF_END __ins_svmoff, _TEXT$00

    LEAF_ENTRY __ins_vmmcall, _TEXT$00

        vmmcall
        ret

    LEAF_END __ins_vmmcall, _TEXT$00

end
