bits 16



; ------------------------------------------------
; disk_load
;
; Reads sectors from disk using BIOS INT 13h
;
; INPUT
; DL = Boot drive
; ES:BX = Destination
; AL = Number of sectors
; CH = Cylinder
; CL = Sector
; DH = Head
;
; OUTPUT
; CF = Set on error
; ------------------------------------------------

disk_load:

    push ax
    push bx
    push cx
    push dx

    mov ah, 0x02
    int 0x13

    pop dx
    pop cx
    pop bx
    pop ax

    ret