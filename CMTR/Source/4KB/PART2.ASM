mov eax,tex3
call initbitmap
mov word ptr [counter],0
part2:
mov ax,offset kula
call generuj
call drawbitmap
call render
call show_screen

jmp part2
