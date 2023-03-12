.686p
    .xlist
include ks386.inc
include callconv.inc
    .list

_TEXT   SEGMENT DWORD PUBLIC 'CODE'
    ASSUME  DS:FLAT, ES:FLAT, SS:NOTHING, FS:NOTHING, GS:NOTHING

GsEax equ 0h
GsEcx equ 4h
GsEdx equ 8h
GsEbx equ 0Ch
GsEsp equ 10h
GsEbp equ 14h
GsEsi equ 18h
GsEdi equ 1Ch
GsEip equ 20h
GsEFlags equ 24h
GsSegEs equ 28h
GsSegCs equ 2Ah
GsSegSs equ 2Ch
GsSegDs equ 2Eh
GsSegFs equ 30h
GsSegGs equ 32h
GsLdtr equ 34h
GsTr equ 36h
GsGdtr equ 3Ah
GsIdtr equ 42h
GsCr0 equ 48h
GsCr2 equ 50h
GsCr3 equ 54h
GsCr4 equ 58h
GsDr0 equ 5Ch
GsDr1 equ 60h
GsDr2 equ 64h
GsDr3 equ 68h
GsDr6 equ 74h
GsDr7 equ 78h
GsMax equ 7Ch

extern _VmxFirstEntry@8:proc

cPublicProc _VmxPrepareStartup, 1

        push ebp
        mov ebp, esp
        sub esp, GsMax

        mov ecx, [ebp + 8]
        mov edx, esp

        mov [edx + GsEax], eax
        mov [edx + GsEcx], ecx
        mov [edx + GsEdx], edx
        mov [edx + GsEbx], ebx
        mov [edx + GsEsp], esp
        mov [edx + GsEbp], ebp
        mov [edx + GsEsi], esi
        mov [edx + GsEdi], edi
        
        lea eax, Succeed
        mov [edx + GsEip], eax
        
        pushfd
        pop [edx + GsEFlags]
        
        mov [edx + GsSegEs], es
        mov [edx + GsSegCs], cs
        mov [edx + GsSegSs], ss
        mov [edx + GsSegDs], ds
        mov [edx + GsSegFs], fs
        mov [edx + GsSegGs], gs
        
        sldt word ptr [edx + GsLdtr]
        str word ptr [edx + GsTr]
        
        sgdt fword ptr [edx + GsGdtr]
        sidt fword ptr [edx + GsIdtr]
        
        mov eax, cr0
        mov [edx + GsCr0], eax
        mov eax, cr2
        mov [edx + GsCr2], eax
        mov eax, cr3
        mov [edx + GsCr3], eax
        mov eax, cr4
        mov [edx + GsCr4], eax
        
        mov eax, dr0
        mov [edx + GsDr0], eax
        mov eax, dr1
        mov [edx + GsDr1], eax
        mov eax, dr2
        mov [edx + GsDr2], eax
        mov eax, dr3
        mov [edx + GsDr3], eax
        mov eax, dr6
        mov [edx + GsDr6], eax
        mov eax, dr7
        mov [edx + GsDr7], eax

        push edx
        push ecx
        call _VmxFirstEntry@8

Failed:
        jmp Complete
Succeed:
        xor eax, eax
Complete:
        add esp, GsMax
        mov esp, ebp
        pop ebp

        stdRET _VmxPrepareStartup

stdENDP _VmxPrepareStartup

_TEXT ends

end
