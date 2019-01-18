;dane
;public fontcol
;public x1adder
;public x2adder
;public y1adder
;public y2adder


;zdefiniowane
l40000 dd 40000.0
l190 dd 190.0
l100 dd 100.0
kory dd 100.0
korx dd 160.0
distance dd 400.0
l1000 dd 1000.0
l1_8 dd 0.25
l8 dd 8.0
MULT	    dd 65536	      ; mnoznik tablicy sinusa & cosinusa
;magic dd 0,42380000h
m1 dd -1,-1
pi180 dd 0.017453292519943296
;phxs dd 128.0			 ;\
;phys dd 128.0			 ; dla phongmapy
phrr dd 16384.0 		;/
l256 dd 256.0
l128 dd 128.0
radius dd 8000
l3 dw 3
old dw 0
vertexcount equ 6*16
facecount equ 6*20
;sumaZtbl dd VALsumaztbl
;pomsumaztbl dd VALpomsumaztbl

;texty do generacji
txttytul: db 'COMMUTATOR',0
txtendtxt: db 'MONOLITH',0
txtc1: db 'CODE',0
TXTC2: DB 'OMEN',0
TXTC3: DB 'VADER',0
txtc4: DB 'MUSIC (soon)',0
TXTC5: DB 'PROVOCATOR',0
TXTGP1: DB 'GREETS',0
TXTGP2: DB 'GOES',0
TXTGP3: DB 'TO',0
TXTG1: DB 'ALTAIR',0
;TXTG2: DB 'ANTIDOTHUM',0
TXTG3: DB 'DIMENSION',0
;TXTG4: DB 'KOROZONE',0
TXTG5: DB 'PLATOON',0
TXTG6: DB 'WIZZARTS',0
TXTG7: DB 'ZONE 51',0
;TXTGP1: DB 'GREETS',0
;TXTGP2: DB 'GOES',0
;TXTGP3: DB 'TO',0


;obiekt
include obfac.inc


;niezdefiniowane
;phxs dd 0
;phys dd 0
;ujnum dd 0
;dodnum dd 0
;facevis dd 0
offseteluj label dword
dd 4 dup(0)
oldseg8h dw 0
oldoff8h dw 0
oldseg9h dw 0
oldoff9h dw 0
counter dw 0
fpuout dd 0,0
;fpu1 dd 0
;fpu2 dd 0
fonty dd 0
fontcol dd 0,0
faddr equ offset fontcol	;dla procek mmxowych
;temp_s dd 0
;vesabufor db 256 dup(0)
vesabufor dd 0
;macierz obrotu
macierz: dd 9 dup(0)
x1adder db 0
y1adder db 0
x2adder db 0
y2adder db 0
;x dd 0
;y dd 0
xt dd 0
yt dd 0
wz dd 0
;radius dd 0
startN dd 0
;lA dd 0
;lB dd 0
;lC dd 0
;lD dd 0
;llE dd 0
;dodonum dd 0
alfa dd 0
beta dd 0
gamma dd 0
verttbl dd 6*16*6*2 dup (0)
facetbl dd 8*20*6*2 dup (0)
wsp3d	dd 9*16*6*2 dup (0)
;verttbl equ wsp3d+4*9*16*6*2
;facetbl equ verttbl+4*6*16*6*2
;wezly equ facetbl+4*8*20*6*2	;rozmiar 41x26x8 bajtow


;tablica do flashuf fontuf
flashcol label byte
db 10 dup(0)
fontflash dw 0
flashdir dw 0  ;0 - w dol (zciemnianie)
	       ;1 - w gore (rozjasnianie)

_sintable   dd 256 dup(0)
_costable   dd 256 dup(0)
usintbl     db 256 dup(0)
usintbl2    db 256 dup(0)
usintbl3    db 256 dup(0)


x	    dd 0
y	    dd 0
delty21     dd 3 dup (0)
delty31     dd 3 dup (0)
delty32     dd 3 dup (0)
const_u     dd 0
const_v     dd 0
deltyx	    dd 0
tr_part     dd 0
dr_konx     dd 0
dx32	    dw 0
dx21	    dw 0
dy32	    dw 0
dy21	    dw 0
pommat1: dd 3*4 dup(0)
pommat2: dd 3*4 dup(0)
pommat3: dd 3*4 dup(0)
sumaZtbl: dd 6*20*4 dup(0)
c1632 db 0
