%ifndef VBE_INC
%define VBE_INC

%define VBE_INFO_ADDRESS       0xA000
%define VBE_MODE_INFO_ADDRESS  0xA200

%define VBE_DATA_ADDRESS       0xA400

%define VBE_TARGET_WIDTH       1024
%define VBE_TARGET_HEIGHT      768
%define VBE_TARGET_BPP         32

%define vbe_mode_list_offset   VBE_DATA_ADDRESS
%define vbe_mode_list_segment  (VBE_DATA_ADDRESS + 2)
%define vbe_current_mode      (VBE_DATA_ADDRESS + 4)

%define vbe_pitch             (VBE_DATA_ADDRESS + 6)
%define vbe_width             (VBE_DATA_ADDRESS + 8)
%define vbe_height            (VBE_DATA_ADDRESS + 10)
%define vbe_bpp               (VBE_DATA_ADDRESS + 12)
%define vbe_framebuffer       (VBE_DATA_ADDRESS + 13)

%endif