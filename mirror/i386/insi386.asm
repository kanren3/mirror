.686p
    .xlist
include ks386.inc
include callconv.inc
include mac386.inc
    .list

_TEXT   SEGMENT DWORD PUBLIC 'CODE'
    ASSUME  DS:FLAT, ES:FLAT, SS:NOTHING, FS:NOTHING, GS:NOTHING

cPublicProc ___ins_cpuidex, 3

        push ebp
        mov ebp, esp

        push ebx
        push esi

        mov eax, [ebp + 8]
        mov ecx, [ebp + 0ch]
        mov esi, [ebp + 10h]

        cpuid

        mov [esi], eax
        mov [esi + 4], ebx
        mov [esi + 8], ecx
        mov [esi + 0ch], edx

        pop esi
        pop ebx

        mov esp, ebp
        pop ebp

        stdRET ___ins_cpuidex

stdENDP ___ins_cpuidex

cPublicProc ___ins_rdmsr, 1

        mov ecx, [esp + 4]
        rdmsr
        
        stdRET ___ins_rdmsr

stdENDP ___ins_rdmsr

cPublicProc ___ins_wrmsr, 3

        mov ecx, [esp + 4]
        mov eax, [esp + 8]
        mov edx, [esp + 0ch]

        wrmsr

        stdRET ___ins_wrmsr

stdENDP ___ins_wrmsr

cPublicProc ___ins_readcr, 1

        mov ecx, [esp + 4]
        xor eax, eax

        cmp ecx, 0
        jz Bcr0

        cmp ecx, 2
        jz Bcr2

        cmp ecx, 3
        jz Bcr3

        cmp ecx, 4
        jz Bcr4

        jmp Finish

Bcr0:
        mov eax, cr0
        jmp Finish
Bcr2:
        mov eax, cr2
        jmp Finish
Bcr3:
        mov eax, cr3
        jmp Finish
Bcr4:
        mov eax, cr4

Finish:
        stdRET ___ins_readcr

stdENDP ___ins_readcr

cPublicProc ___ins_writecr, 2

        mov ecx, [esp + 4]
        mov eax, [esp + 8]

        cmp ecx, 0
        jz Bcr0

        cmp ecx, 2
        jz Bcr2

        cmp ecx, 3
        jz Bcr3

        cmp ecx, 4
        jz Bcr4

        jmp Finish

Bcr0:
        mov cr0, eax
        jmp Finish
Bcr2:
        mov cr2, eax
        jmp Finish
Bcr3:
        mov cr3, eax
        jmp Finish
Bcr4:
        mov cr4, eax

Finish:
        stdRET ___ins_writecr

stdENDP ___ins_writecr

cPublicProc ___ins_readdr, 1

        mov ecx, [esp + 4]
        xor eax, eax

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
        mov eax, dr0
        jmp Finish

Bdr1:
        mov eax, dr1
        jmp Finish

Bdr2:
        mov eax, dr2
        jmp Finish

Bdr3:
        mov eax, dr3
        jmp Finish

Bdr6:
        mov eax, dr6
        jmp Finish

Bdr7:
        mov eax, dr7
        jmp Finish

Finish:
        stdRET ___ins_readdr

stdENDP ___ins_readdr

cPublicProc ___ins_writedr, 2

        mov ecx, [esp + 4]
        mov eax, [esp + 8]

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
        mov dr0, eax
        jmp Finish

Bdr1:
        mov dr1, eax
        jmp Finish

Bdr2:
        mov dr2, eax
        jmp Finish

Bdr3:
        mov dr3, eax
        jmp Finish

Bdr6:
        mov dr6, eax
        jmp Finish

Bdr7:
        mov dr7, eax
        jmp Finish

Finish:
        stdRET ___ins_writedr

stdENDP ___ins_writedr

cPublicProc ___ins_rdtsc, 0

        rdtsc

        stdRET ___ins_rdtsc

stdENDP ___ins_rdtsc

cPublicProc ___ins_rdtscp, 1

        push ebp
        mov ebp, esp

        push esi

        xor ecx, ecx
        rdtscp

        mov esi, [ebp + 8]
        mov [esi], ecx

        pop esi

        mov esp, ebp
        pop ebp

        stdRET ___ins_rdtscp

stdENDP ___ins_rdtscp

cPublicProc ___ins_xgetbv, 1

        mov ecx, [esp + 4]

        xsetbv

        stdRET ___ins_xgetbv

stdENDP ___ins_xgetbv

cPublicProc ___ins_xsetbv, 3

        mov ecx, [esp + 4]
        mov eax, [esp + 8]
        mov edx, [esp + 0ch]

        xsetbv

        stdRET ___ins_xsetbv

stdENDP ___ins_xsetbv

cPublicProc ___ins_invd, 0

        invd

        stdRET ___ins_invd

stdENDP ___ins_invd

cPublicProc ___ins_wbinvd, 0

        wbinvd

        stdRET ___ins_wbinvd

stdENDP ___ins_wbinvd

cPublicProc ___ins_sgdt, 1

        mov ecx, [esp + 4]

        sgdt fword ptr [ecx]

        stdRET ___ins_sgdt

stdENDP ___ins_sgdt

cPublicProc ___ins_lgdt, 1

        mov ecx, [esp + 4]

        lgdt fword ptr [ecx]

        stdRET ___ins_lgdt

stdENDP ___ins_lgdt

cPublicProc ___ins_sidt, 1

        mov ecx, [esp + 4]

        sidt fword ptr [ecx]

        stdRET ___ins_sidt

stdENDP ___ins_sidt

cPublicProc ___ins_lidt, 1

        mov ecx, [esp + 4]

        lidt fword ptr [ecx]

        stdRET ___ins_lidt

stdENDP ___ins_lidt

cPublicProc ___ins_vmxon, 1

        mov ecx, [esp + 4]

        vmxon qword ptr [ecx]

        setz al
        setb cl
        adc al, cl
        and eax, 3

        stdRET ___ins_vmxon

stdENDP ___ins_vmxon

cPublicProc ___ins_vmxoff, 0

        vmxoff

        setz al
        setb cl
        adc al, cl
        and eax, 3

        stdRET ___ins_vmxoff

stdENDP ___ins_vmxoff

cPublicProc ___ins_vmclear, 1

        mov ecx, [esp + 4]

        vmclear qword ptr [ecx]

        setz al
        setb cl
        adc al, cl
        and eax, 3

        stdRET ___ins_vmclear

stdENDP ___ins_vmclear

cPublicProc ___ins_vmptrld, 1

        mov ecx, [esp + 4]

        vmptrld qword ptr [ecx]

        setz al
        setb cl
        adc al, cl
        and eax, 3

        stdRET ___ins_vmptrld

stdENDP ___ins_vmptrld

cPublicProc ___ins_vmread, 2

        mov ecx, [esp + 4]
        xor eax, eax

        vmread eax, ecx

        mov edx, [esp + 8]
        mov [edx], eax

        setz al
        setb cl
        adc al, cl
        and eax, 3

        stdRET ___ins_vmread

stdENDP ___ins_vmread

cPublicProc ___ins_vmwrite, 2

        mov ecx, [esp + 4]
        mov eax, [esp + 8]

        vmwrite ecx, eax

        setz al
        setb cl
        adc al, cl
        and eax, 3

        stdRET ___ins_vmwrite

stdENDP ___ins_vmwrite

cPublicProc ___ins_vmlaunch, 0

        vmlaunch

        setz al
        setb cl
        adc al, cl
        and eax, 3

        stdRET ___ins_vmlaunch

stdENDP ___ins_vmlaunch

cPublicProc ___ins_vmresume, 0

        vmresume

        setz al
        setb cl
        adc al, cl
        and eax, 3

        stdRET ___ins_vmresume

stdENDP ___ins_vmresume

cPublicProc ___ins_vmcall, 2

        mov ecx, [esp + 4]
        mov eax, [esp + 8]

        vmcall

        stdRET ___ins_vmcall

stdENDP ___ins_vmcall

cPublicProc ___ins_clgi, 0

        clgi

        stdRET ___ins_clgi

stdENDP ___ins_clgi

cPublicProc ___ins_stgi, 0

        stgi

        stdRET ___ins_stgi

stdENDP ___ins_stgi

cPublicProc ___ins_svmon, 0

        mov ecx, 0C0000080h
        rdmsr

        or eax, 01000h
        wrmsr

        stdRET ___ins_svmon

stdENDP ___ins_svmon

cPublicProc ___ins_svmoff, 0

        mov ecx, 0C0000080h
        rdmsr

        and eax, 0FFFFEFFFh
        wrmsr

        stdRET ___ins_svmoff

stdENDP ___ins_svmoff

cPublicProc ___ins_vmmcall, 2

        mov ecx, [esp + 4]
        mov eax, [esp + 8]

        vmmcall
        
        stdRET ___ins_vmmcall

stdENDP ___ins_vmmcall

_TEXT ends

end

