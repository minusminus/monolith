base_addy equ 800000h
screen_buffer equ base_addy         ; size 320*200*4
tytul equ screen_buffer+320*200*4   ; size 320*32*4
pomtxt equ tytul+320*32*4           ; size 320*32*4
pomtxt2 equ pomtxt+32*320*4         ; size 320*32*4
temp_seg1 equ pomtxt2+32*320*4      ; size 256*256
temp_seg2 equ temp_seg1+256*256     ; size 256*256
temp_seg3 equ temp_seg2+256*256     ; size 256*256
textunel  equ temp_seg3+256*256     ; size 256*256*4
phmap equ textunel+256*256*4        ; size 256*256*4
bumpmap equ phmap+256*256*4         ; size 256*256*4
tablicexy equ bumpmap+256*256*4     ; size 320*200*4
phmapext equ tablicexy+320*200*4    ; size 256*256*8
wezly equ phmapext+256*256*8        ; size 41*26*8
tex1n equ wezly+41*26*8             ; size 256*256*4
tex1 equ tex1n+256*256*4            ; size 256*256*4
tex3 equ tex1+256*256*4             ; size 256*256*4
