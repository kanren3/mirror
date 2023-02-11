.686p
    .xlist
include ks386.inc
include callconv.inc
include mac386.inc
    .list

_TEXT   SEGMENT DWORD PUBLIC 'CODE'
    ASSUME  DS:FLAT, ES:FLAT, SS:NOTHING, FS:NOTHING, GS:NOTHING

cPublicProc _ins_cpuidex, 3

        mov edi, edi
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
        stdRET _ins_cpuidex

stdENDP _ins_cpuidex

_TEXT ends

end
