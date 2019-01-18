;bitsort na 4 bitach = 8 przejsc procedury
;dziala na sumach Z typu DD
;sumy Z w tablicy sumaZtbl, pomsumaZtbl wypelniona 0
bitsort proc
;mov edi,sumaZtbl
;mov esi,pomsumaZtbl
;;xor ecx,ecx		  ;offset kolejnego faca
;;xor edx,edx		  ;numer faca


;sortowanie wlasciwe <offsety>
;mov ecx,8
xor ecx,ecx
mov cl,8

sortlup:
;wypelnienie tabel zerami
xor ebp,ebp
;mov eax,16
xor eax,eax
mov al,16
ujfil:
mov offseteluj[4*eax-4],ebp
dec ax
jnz ujfil

push ecx
push edi
;tu juz obliczanie ilosci danych zmiennych
mov edx,facevis
cmp dx,0
jle dodatniesort
shl cl,2       ;\
sub cl,32      ; przesuniecie dla maski
neg cl	       ;/

ujlup:
mov eax,[edi]			;pobierz liczbe
mov eax,[eax+12]
shr eax,cl			;przesun dla maski
and eax,0fh			;maska -> oblicz offset w tablicy ilosci
add offseteluj[4*eax],4 	;zwieksz offset w tablicy ilosci
add edi,4			;nast liczba
dec dx
jnz ujlup

dodatniesort:

;dodawanie offsetow -> powstaje tablica przesuniec dla danego typu danych
dodawanieoffsetow:
xor edi,edi
;mov edx,16
xor edx,edx
mov dl,16
xor ebx,ebx			;bo pierwsze jest zero

sumujlup:
mov eax,offseteluj[edi] 	;pobierz element
mov offseteluj[edi],ebx 	;zaladuj poprzednia sume
add edi,4
add ebx,eax			;sumuj poprzedni+aktualny
;add edi,4
dec dx
jnz sumujlup



;przepisanie sum z tablicy edi do esi
pop edi
push edi
push esi
mov edx,facevis
cmp dx,0
jle koniecuj

pujlup:
mov eax,[edi]			;pobierz liczbe
mov ebx,[eax+12]		     ;to dla maski
shr ebx,cl
and ebx,0fh
mov ebp,offseteluj[4*ebx]	  ;wez offset wzgledem poczatku tablicy
add offseteluj[4*ebx],4 	  ;od razu niech wskazuje nast miejsce
mov ds:[esi+ebp],eax		   ;zapisz liczbe
add edi,4
dec edx
jnz pujlup


koniecuj:
pop edi 			;\szybki xchg edi,esi
pop esi 			;/
pop ecx
dec cx
jnz sortlup


mov esi,sumaZtbl
mov edi,pomsumaZtbl
mov ecx,ujnum
cmp cx,0
jle nocpy
mov edx,dodnum
cpl1:
mov eax,[esi+4*edx]
mov [edi],eax
add edi,4
inc edx
dec cx
jnz cpl1
mov ecx,dodnum
cmp cx,0
jle nocpy
cpl2:
mov eax,[esi]
mov [edi],eax
add esi,4
add edi,4
dec cx
jnz cpl2
mov esi,sumaZtbl
mov edi,pomsumaZtbl
mov sumaZtbl,edi
mov pomsumaZtbl,esi

nocpy:
ret
endp