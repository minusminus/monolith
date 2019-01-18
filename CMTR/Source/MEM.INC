;bezwzgledne adresy w pamieci

;zmienne pomocnicze
begin equ 8000000
stex equ 256*256*4	;textura
stexE equ 256*256*8	;textura extended
sbuf equ 320*200*4	;bufor ekranu
stxt32 equ 32*320*4	;tekst 32x32
stxt16 equ 32*320*4	;tekst 16x16 ale w takim samym buforze


;adresy
textunel equ begin
tex1 equ textunel+stex	;tekstura 1
tex1n equ tex1+stex	  ;w negatywie
tex1ext equ tex1n+stex	  ;extended
tex2 equ tex1ext+stexE	  ;textura 2
tex3 equ tex2+stex	  ;textura 3
temp_seg1 equ tex3+stex
temp_seg2 equ temp_seg1+256*256
temp_seg3 equ temp_seg2+256*256
phmap equ temp_seg3+256*256	  ;phongmapa
phmapext equ phmap+stex   ;phongmapa rozszerzona
bumpmap equ phmapext+stexE	     ;bumpmapa do tunelu
bufor equ bumpmap+stex		     ;bufor ekranu

;teksty
pomtxt equ bufor+2*sbuf     ;\pomocnicze bufory do textuf
pomtxt2 equ pomtxt+stxt32 ;/
tytul equ pomtxt2+stxt32    ;tytul
endtxt equ tytul+stxt32        ;koncowy napis

;creditsy
c1 equ endtxt+stxt32
c2 equ c1+stxt16
c3 equ c2+stxt16
c4 equ c3+stxt16
c5 equ c4+stxt16

;greetsy
gp1 equ c5+stxt16
gp2 equ gp1+stxt16
gp3 equ gp2+stxt16
g1 equ gp3+stxt16
g2 equ g1+stxt16
g3 equ g2+stxt16
g4 equ g3+stxt16
g5 equ g4+stxt16
g6 equ g5+stxt16
g7 equ g6+stxt16
;gp1 equ g7+stxt16
;gp2 equ gp1+stxt16
;gp3 equ gp2+stxt16

;inne
sintbl equ g7+stxt16	       ;tablica sinusow
Ssin equ (360+90)*4
fdt equ sintbl+Ssin	  ;fastdivtbl
Sfdt equ (2*1024+1)*4
fastdivtbl equ fdt+4*1024	;wskaznik do fdt

;_sintable equ fdt+Sfdt
;_costable equ _sintable+256*4
;usintbl equ _costable+256*4
;usintbl2 equ usintbl+256
;usintbl3 equ usintbl2+256
;tablicexy equ usintbl3+256	 ;tablica tunelu 320x200x4
tablicexy equ fdt+Sfdt	    ;tablica tunelu 320x200x4
;wsp3d equ tablicexy+320*200*4
;verttbl equ wsp3d+4*9*16*6*2
;facetbl equ verttbl+4*6*16*6*2
;wezly equ facetbl+4*8*20*6*2	;rozmiar 41x26x8 bajtow
wezly equ tablicexy+320*200*4
VALsumaZtbl equ wezly+41*26*8
VALpomsumaztbl equ VALsumaztbl+6*20*4*2  ;tez x2
