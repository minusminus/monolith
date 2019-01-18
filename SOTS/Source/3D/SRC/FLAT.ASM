;SZABLON PROCKI NA TROJKAT
.386
code32 segment use32 public 'code' page
assume cs:code32,ds:code32,es:code32






;opis struktur
include scene.inc

;zmienne
include drawtr.inc



public trflat_
public trflatinit_


;we:
;esi - adres zbufora
;edi - adres bufora do rysowania
;edx - szerokosc bufora w pikselach*4
trflatinit_ proc
mov dword ptr[zbuf],esi
mov dword ptr[zbuf2],esi
mov dword ptr[buf],edi
mov dword ptr[scrX],edx
mov dword ptr[scrX2],edx
mov dword ptr[scrlen],edx
ret
endp



;procedura na trojkat
;we:
trflat_ proc
pushad

;laduj potrzebnych rzeczy
mov esi,tr
mov eax,[esi].f_texaddy
mov kolor,eax

;**************************************************************************
;tu liczenie innych potrzebnych delt dla trojkata


;liczymy stale delty [powiny byc tu liczone wszystkie lacznie z Z]

;zmiana delt

;**************************************************************************
;ladowanie delt
;pamietac o deltach dodatkowych dla trojkata
cmp byte ptr[dir],0
jne swapd
;tu mniejsza (normalnie trojkat)
noswap:
mov eax,dx12
mov dl1,eax
mov ecx,dx23
mov edx,dx13
mov dl2,ecx
mov dp1,edx
mov dp2,edx
mov eax,dz12
mov ecx,dz23
mov dz1,eax
mov dz2,ecx
jmp ladujZ
swapd:
;zmaina delt (rysowanie odwrotnego trojkata)
mov eax,dx12
mov dp1,eax
mov ecx,dx13
mov edx,dx23
mov dp2,edx
mov dl1,ecx
mov dl2,ecx
mov eax,dz13
mov dz1,eax
mov dz2,eax
ladujZ:
;stale deltaZ w linii poziomej
mov eax,dzstale
mov dword ptr[stalez],eax







;**************************************************************************
;czesc 1->2
mov esi,w1
mov edi,w2
test byte ptr[flags+3],80h	  ;bit 31 [czesc 12]
jz nopart12

;rysowanie 1->2
;inicjalizacja rejestrow i zmiennych przed rysowaniem danej czesci
mov eax,dl1
mov edx,dp1
mov deltal,eax
mov deltap,edx
mov eax,dz1
mov deltaz,eax
fld dword ptr[esi].v_x2d
fmul dword ptr[l64k]
fistp dword ptr[temp]
mov ebx,temp		;xl
mov ecx,temp		;xp

mov edi,y1
mov ebp,y12
imul edi,12345678h	;adrs w buforze
     scrX = $-4

;tu inne wartosci do rejestrow


mov esi,z1		;1/z
mov eax,kolor
jmp goline		;nie trzeba stawiac pktu w pierwszym wierzcholku


;***********************************************************************
;inner loop
;z opisanymi rejestrami
;edi - koniec linii w buforze
;ecx - dlugosc linii zanegowana
;esi - wartosc zbufora
;eax - kolor
innerloop:
cmp esi,[edi+4*ecx+12345678h]
    zbuf = $-4
jbe notput
mov [edi+4*ecx+12345678h],esi		;wstaw do zbufora
    zbuf2 = $-4
mov [edi+4*ecx+12345678h],eax		;postaw pkt na ekranie
    buf = $-4
notput:
add esi,12345678h			;nast Z w linii
    stalez = $-4

inc ecx
js innerloop

;***********************************************************************

pop esi ebx edi ecx
goline:
add edi,12345678h	;dodaj dlugosc linii w bajtach
    scrlen = $-4
add esi,deltaz
add ecx,deltap
add ebx,deltal
dec ebp
jnz poczateklinii
jmp koniecczesci

poczateklinii:
push ecx edi ebx
sar ebx,16
push esi
sar ecx,16
lea edi,[edi+4*ecx]		;adres konca linii w buforze
sub ecx,ebx			;dlugosc linii
neg ecx
jmp innerloop

koniecczesci:






;koniec rysowania danej czesci trojkata - zachowanie wartosci itp
dec dword ptr[licznik]
jz koniec
cmp dir,0
je do23
xchg ebx,ecx		;to tylko gdy odwrotnie mamy trojkat
mov savez,esi
jmp do23
;jmp koniec

;do czesci 2->3
nopart12:
test byte ptr[flags+3],40h	  ;bit 30 [czesc 23]
jz koniec
mov ebp,w1
fld dword ptr[ebp].v_x2d
fmul dword ptr[l64k]
fistp dword ptr[temp]
mov ecx,temp		;poczatkowe xp jak nie bylo czesci 1->2
push esi
mov esi,z1
mov savez,esi
pop esi


;**************************************************************************
do23:		;normalna juz czesc 23
mov eax,dl2
mov edx,dp2
mov deltal,eax
mov deltap,edx
mov eax,dz2
mov deltaz,eax
mov esi,w2
mov edi,w3
fld dword ptr[esi].v_x2d
fmul dword ptr[l64k]
fistp dword ptr[temp]
mov ebx,temp	      ;xl
mov ebp,y23
mov edi,y2
imul edi,12345678h	;adres w buforze
     scrX2 = $-4

mov esi,z2		;1/z
mov eax,kolor
cmp dir,0
je poczateklinii	;tu juz trzeba narysowac pierwsza linie
xchg ebx,ecx
mov esi,savez
jmp poczateklinii



koniec:
popad
ret
endp


dl1 dd 0
dl2 dd 0
dp1 dd 0
dp2 dd 0
dz1 dd 0
dz2 dd 0
deltal dd 0
deltap dd 0
deltaz dd 0
savez dd 0
temp dd 0
kolor dd 0

code32 ends
end