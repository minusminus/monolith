;sortowanie babelkowe
;we:
;esi - tablica do posortowania
;ecx - ilosc elementow
;wersja specjalna so tego formatu
bubblesort proc


bos:
mov bp,cx	      ;licznik wewnetrzny

mov di,[si]	      ;\bierzemy 1 element z tablicy
mov eax,[di+12] 	;/i jego wartosc

push si 	       ;dla nastepnej petli

bis:
mov bx,[si]	      ;wez adres akt sprawdzanego elementu
cmp eax,[bx+12] 	;porownaj zapamietana wartosc z nim
jg nochs

;mov [esi],edi		 ;wstaw adres porownujacego elementu [mniejszego]
;mov edi,ebx		 ;wez nowy adres najwiekszego elementu
xchg di,[si]
mov eax,[di+12] 	 ;pobranie nowej wartosci max elementu

nochs:
add si,4	       ;nast element
dec bp
jnz bis

pop si		       ;od razu przesuniety o 1 w dol

;wymiana aktualnie bedacego w rejestrze z pierwszym
xchg di,[si]	;\wstawienie max el na pierwsza pozycje w tablicy
;mov eax,[edi+0]   ;/

add si,4
dec cx
jnz bos


ret
endp