;czesc druga

mov eax,tex1n
call initbitmap
mov counter,0
mov fontflash,0

pp2:
mov ax,offset kula
call generuj
call drawbitmap
mov dword ptr[fontcol],0
call render

mov bx,5
mov ax,fontflash
shr ax,6
cwd
idiv bx
mov bx,dx
mov byte ptr flashcol[bx],0ffh
;mov dword ptr fontcol[0],00ff00ffh
;mov dword ptr fontcol[4],00ff00ffh
;mov bx,0
xor bx,bx
mov edi,bufor+320*4*10
mov esi,c1
credloop:
push bx
call makefontcolor
sub byte ptr flashcol[bx],2
;mov esi,c1
;mov edi,bufor+320*4*10
push edi esi
call printfonttbl
pop esi edi
add edi,320*4*40
add esi,c2-c1
pop bx
inc bx
cmp bx,5
jb credloop
;;mov dword ptr fontcol[0],00ff00ffh
;;mov dword ptr fontcol[4],00ff00ffh
;mov bx,1
;call makefontcolor
;sub byte ptr flashcol[bx],2
;mov esi,c3
;mov edi,bufor+320*4*50
;call printfonttbl
;;mov dword ptr fontcol[0],00ff00ffh
;;mov dword ptr fontcol[4],00ff00ffh
;mov bx,2
;call makefontcolor
;sub byte ptr flashcol[bx],2
;mov esi,c4
;mov edi,bufor+320*4*90
;call printfonttbl
;;mov dword ptr fontcol[0],00ff00ffh
;;mov dword ptr fontcol[4],00ff00ffh
;mov bx,3
;call makefontcolor
;sub byte ptr flashcol[bx],2
;mov esi,c2
;mov edi,bufor+320*4*130
;call printfonttbl
;;mov dword ptr fontcol[0],00ff00ffh
;;mov dword ptr fontcol[4],00ff00ffh
;mov bx,4
;call makefontcolor
;sub byte ptr flashcol[bx],2
;mov esi,c5
;mov edi,bufor+320*4*170
;call printfonttbl


call drop

mov ax,counter
cmp ax,4*80
jl pp2
