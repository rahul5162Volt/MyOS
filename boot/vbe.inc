%ifndef VBE_INC
%define VBE_INC

%define VBE_INFO_ADDRESS       0xA000
%define VBE_MODE_INFO_ADDRESS  0xA200

%define VBE_TARGET_WIDTH       1024
%define VBE_TARGET_HEIGHT      768
%define VBE_TARGET_BPP         32

vbe_mode_list_offset:
    dw 0

vbe_mode_list_segment:
    dw 0

vbe_current_mode:
    dw 0

%endif