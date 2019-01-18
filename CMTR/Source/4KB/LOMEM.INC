txttytul    db 'COMMUTATOR',0
c1632       db 1
MULT        dd 65536          ; mnoznik tablicy sinusa & cosinusa
text_color  dd 07f7f7fh
phrr        dw 16384
l3          dw 3
t100        dw -100
t160        dw -160
tpi128      dd 0.024543693
radius      dd 8000
pi180       dd 0.017453292519943296
m1          dd -1,-1
include obfac.inc
dy32        dw 0
dy21        dw 0
counter     dw 0
fpuout      dd 0,0
x           dd 0
y           dd 0
deltax      dd 0
deltay      dd 0
deltadx     dd 0
deltady     dd 0
ll          dd 0
matrix      dd 9 dup(0)
matrixX     dd 9 dup(0)
matrixY     dd 9 dup(0)
matrixZ     dd 9 dup(0)
vertices    dd  vertexcount*13 dup (0)
faces       dd  facecount*6 dup(0)
delty21     dd 3 dup (0)
delty31     dd 3 dup (0)
delty32     dd 3 dup (0)
const_u     dd 0
const_v     dd 0
deltyx      dd 0
tr_part     dd 0
dr_konx     dd 0
;alfa        dd 0.0
;beta        dd 0.0
;gama        dd 0.0
l40000 dd 40000.0
l190 dd 190.0
l100 dd 100.0
l1000 dd 1000.0
l256 dd 256.0
l128 dd 128.0
l8 dd 8.0
scale_3d dd 600.0

oldseg9h    dw ?
oldoff9h    dw ?
vesa_buffer db 256 dup(?)
sintbl      dd 450 dup(?)
_sintable   dd 256 dup(?)
_costable   dd 256 dup(?)
usintbl     db 256 dup(?)
usintbl2    db 256 dup(?)
usintbl3    db 256 dup(?)
