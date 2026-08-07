bits 16

org 0x8000



start:


cli



; --------------------
; Load kernel
; --------------------


mov ax,0x1000
mov es,ax

xor bx,bx


mov dl,0x80


mov al,10        ; kernel sectors

mov ch,0
mov cl,6         ; kernel starts sector 6
mov dh,0


call disk_load




; --------------------
; Enable A20
; --------------------

in al,0x92

or al,00000010b

out 0x92,al




; --------------------
; Load GDT
; --------------------

lgdt [gdt_descriptor]



; --------------------
; Protected Mode
; --------------------

mov eax,cr0

or eax,1

mov cr0,eax



jmp 0x08:protected_mode




bits 32



protected_mode:


mov ax,0x10


mov ds,ax
mov es,ax
mov fs,ax
mov gs,ax
mov ss,ax



mov esp,0x90000



; jump kernel

jmp 0x10000




; =====================
; GDT
; =====================


gdt_start:


dq 0



; code

dw 0xffff
dw 0

db 0

db 10011010b

db 11001111b

db 0



; data

dw 0xffff
dw 0

db 0

db 10010010b

db 11001111b

db 0



gdt_end:



gdt_descriptor:


dw gdt_end-gdt_start-1

dd gdt_start



%include "boot/disk.asm"