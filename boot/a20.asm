bits 16

;==========================================
; MyOS A20 Support
;==========================================

global enable_a20

enable_a20:

    ; Read System Control Port A (0x92)
    in  al, 0x92

    ; Is A20 already enabled?
    test al, 00000010b
    jnz .done

    ; Enable A20
    or  al, 00000010b

    ; Do NOT trigger reset (clear bit 0)
    and al, 11111110b

    out 0x92, al

.done:
    ret