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

_TEXT ends

end
