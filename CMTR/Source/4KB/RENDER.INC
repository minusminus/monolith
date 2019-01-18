init_3d:
; inicjalizacja macierzy obrotow
         fld1
         fst     dword ptr [matrixX]
         fst     dword ptr [matrixY+16]
         fstp    dword ptr [matrixZ+32]
; utworzenie obiektow
 ; tworzenie tablicy wierzcholkow
         mov     cx,vertexcount
         mov     si,offset cubepoints
         mov     di,offset vertices
create_vertices:
         mov     dx,3
vertice_loop:
         movsx   ax,byte ptr [si]
         mov     word ptr [fpuout],ax
         fild    word ptr [fpuout]
         fstp    dword ptr [di]
         inc     si
         add     di,4
         dec     dx
         jnz     vertice_loop
         add     di,40               ; nastepny wierzcholek
         loop create_vertices
  ; tworzenie fejsow i liczenie normalsow
         mov     word ptr [matrix],5*16         ; liczba skladowych obiektu
         mov     di,offset faces
subobject_loop:
         mov     si,offset mainface
         mov     cx,20        ; liczba fejsow na skladowa
create_face_loop2:
         mov     bp,3         ; 3 wierzcholki na fejsa
create_face_loop:
         movzx   ax,byte ptr [si]     ; numer wierzcholka
         add     ax,word ptr [matrix] ; + liczba wierzcholkow na skladowa
         mov     dx,13*4
         mul     dx
         add     ax,offset vertices
         mov     word ptr [di],ax
         add     di,4
         inc     si
         dec     bp
         jnz     create_face_loop
; liczenie normalsa dla fejsa
         pusha
         mov     bx,word ptr [di-12] ; p1
         mov     si,word ptr [di-8]  ; p2
         mov     dx,2
normals_loop_2:
         mov     cx,3
normals_loop_1:
         fld     dword ptr [bx]
         fsub    dword ptr [si]
         add     si,4
         add     bx,4
         loop    normals_loop_1
         mov     bx,word ptr [di-8]
         mov     si,word ptr [di-4]  ; p3
         dec     dx
         jnz     normals_loop_2
         fld     st(0)
         fld     st(2)
         fmul    st(0),st(5)
         fxch
         fmul    st(0),st(6)
         fsubp   st(1),st(0)
         fxch    st(4)
         fmul    st(0),st(3)
         fxch
         fmul    st(0),st(6)
         fsubrp  st(1),st(0)
         fxch    st(4)
         fmulp   st(2),st(0)
         fmulp   st(4),st(0)
         fsubrp  st(3),st(0)
         fstp    dword ptr [di]
         fstp    dword ptr [di+4]
         fstp    dword ptr [di+8]
         popa
         add     di,12
         loop    create_face_loop2
         sub     word ptr [matrix],16
         jns     subobject_loop
; liczenie wersorow
         mov     di,offset vertices
         mov     cx,vertexcount
wersory_loop:
         fldz
         fldz
         fldz
         mov     dx,facecount
         mov     si,offset faces
w_face_loop:
         cmp     word ptr [si],di
         je      w_face_jest
         cmp     word ptr [si+4],di
         je      w_face_jest
         cmp     word ptr [si+8],di
         jne     w_face_brak
w_face_jest:
         fld     dword ptr [si+20]
         fld     dword ptr [si+16]
         fld     dword ptr [si+12]
         faddp   st(3),st(0)
         faddp   st(3),st(0)
         faddp   st(3),st(0)
w_face_brak:
         add     si,24
         dec     dx
         jnz     w_face_loop
         ; normalizuj
         fld     st(2)
         fmul    st(0),st(0)
         fld     st(2)
         fmul    st(0),st(0)
         fld     st(2)
         fmul    st(0),st(0)
         faddp   st(1),st(0)
         faddp   st(1),st(0)
         fsqrt
         fdiv    st(3),st(0)
         fdiv    st(2),st(0)
         fdivp   st(1),st(0)
         fstp    dword ptr [di+12]
         fstp    dword ptr [di+16]
         fstp    dword ptr [di+20]
         add     di,13*4
         loop    wersory_loop
         ret

render:
; wypelnienie macierzy obrotow
         fild    word ptr [counter]
         fmul    dword ptr [pi180]
         fsincos
         fst     dword ptr [matrixX+16]
         fstp    dword ptr [matrixX+32]
         fst     dword ptr [matrixX+20]
         fchs
         fstp    dword ptr [matrixX+28]
         fild   word ptr [counter]
         fmul   dword ptr [tpi128]
         fsincos
         fst     dword ptr [matrixY]
         fstp    dword ptr [matrixY+32]
         fst     dword ptr [matrixY+24]
         fchs
         fstp    dword ptr [matrixY+8]
         fldpi
         fimul   word ptr [counter]
         fmul    dword ptr [pi180]
         fsincos
         fst     dword ptr [matrixZ]
         fstp    dword ptr [matrixZ+16]
         fst     dword ptr [matrixZ+4]
         fchs
         fstp    dword ptr [matrixZ+12]
         mov     si,offset matrixZ
         mov     bx,offset matrixY
         mov     di,offset matrix
         call    matrix_mul
         mov     si,offset matrix
         mov     bx,offset matrixX
         mov     di,offset matrix
         call    matrix_mul
; przetwarzanie wierzcholkow
         mov     si,offset vertices
         mov     cx,vertexcount
process_vertices:
         pusha
         mov     bx,offset matrix
         lea     di,[si+24]
         call    mul_vector_matrix
         fld     dword ptr [si+32]
         fadd    dword ptr [l1000]
         fld     dword ptr [scale_3d]
         fdivrp  st(1),st(0)
         fld     dword ptr [si+24]
         fmul    st(0),st(1)
         fisub   word ptr [t160]
         fistp   dword ptr [si+36]
         fld     dword ptr [si+28]
         fmulp   st(1),st(0)
         fiadd   word ptr [t100]
         fchs
         fistp   dword ptr [si+40]
; liczenie wspolrzednych textury
         mov     bx,offset matrix
         add     si,12
         mov     di,offset vesa_buffer
         call    mul_vector_matrix
         fld     dword ptr [l128]
         fld     dword ptr [vesa_buffer]
         fmul    st(0),st(1)
         fadd    st(0),st(1)
         fistp   dword ptr [si+44-12]
         fld     dword ptr [vesa_buffer+4]
         fmul    st(0),st(1)
         faddp   st(1),st(0)
         fistp   dword ptr [si+48-12]
         popa
         add     si,13*4
         loop    process_vertices
; sortowanie fejsow

         mov     si,offset faces
sort_loop2:
         lea     di,[si+24]
sort_loop:
         fldz
         mov     cx,3
sumaZ:
         mov     bx,word ptr [si]
         fadd    dword ptr [bx+32]
         mov     bx,word ptr [di]
         fsub    dword ptr [bx+32]
         add     si,4
         add     di,4
         loop    sumaZ
         sub     si,12
         sub     di,12
         fstp    dword ptr [fpuout]
         test    byte ptr [fpuout+3],80h
         jz      no_swap
         mov     cx,12
swap_loop:
         mov     ax,word ptr [si]
         mov     dx,word ptr [di]
         mov     word ptr [si],dx
         mov     word ptr [di],ax
         add     si,2
         add     di,2
         loop    swap_loop
         sub     si,24
         sub     di,24
no_swap:
         add     di,24
         cmp     di,facecount*24+offset faces
         jne     sort_loop
         add     si,24
         cmp     si,facecount*24+offset faces-24
         jne     sort_loop2
sort_end:
; rysowanie fejsow
         mov     si,offset faces
         mov     cx,facecount
draw_faces:
         pusha
;อออออออออออออออออออออ    Texturowanko    อออออออออออออออออออออออออออออออออออ
; z grubsza optymalizowane na _dlugosc_ wiec prosze sie nie nabijac :)
; si - fejs
         mov     word ptr [tr_part],1
         mov     bx,word ptr [si]
         mov     di,word ptr [si+8]
         mov     si,word ptr [si+4]
         mov     ax,word ptr [bx+40]
         mov     bp,word ptr [di+40]
         mov     dx,word ptr [si+40]
         cmp     ax,bp
         jl      dr_xchg01
         xchg    ax,bp
         xchg    bx,di
dr_xchg01:
         cmp     ax,dx
         jl      dr_xchg02
         xchg    ax,dx
         xchg    bx,si
dr_xchg02:
         cmp     dx,bp
         jl      dr_xchg03
         xchg    dx,bp
         xchg    si,di
dr_xchg03:
         cmp     ax,bp
         je      dr_skip
         sub     bp,dx
         sub     dx,ax
         mov     word ptr [dy32],bp
         mov     word ptr [dy21],dx
         jnz     no_chk_swap
         mov     ax,word ptr [si+36]
         cmp     ax,word ptr [bx+36]
         jge     no_chk_swap_2
         xchg    si,bx
no_chk_swap_2:
         mov     byte ptr [tr_part+1],1
         mov     eax,dword ptr [si+36]
         shl     eax,8
         add     eax,80h
         mov     dword ptr [dr_konx],eax
no_chk_swap:
         push    bx
         push    si
         push    di
         mov     di,offset delty21
         call    dr_delta
         pop     si
         mov     di,offset delty31
         call    dr_delta
         pop     bx
         mov     di,offset delty32
         call    dr_delta
         mov     si,bx
         pop     bx
         ; bx  - pierwszy punkt
         ; si  - drugi punkt
         test    word ptr [dy21],-1
         jz      calc_slope_2
         fild    dword ptr [delty31]
         fisub   dword ptr [delty21]
         fdivr   dword ptr [l256]
         fild    dword ptr [delty31+4]
         fisub   dword ptr [delty21+4]
         fild    dword ptr [delty31+8]
         fisub   dword ptr [delty21+8]
calc_slope_ret:
         fxch    st(2)
         fmul    st(2),st(0)
         fmulp   st(1),st(0)
         fistp   dword ptr [const_u]
         fistp   dword ptr [const_v]
; zamiany delt
         mov     eax,dword ptr [delty21]
         mov     edx,dword ptr [delty31]
         cmp     eax,edx
         jle     dr_xchg04
         mov     dword ptr [delty21],edx
         mov     cx,word ptr [delty31+4]
         mov     dx,word ptr [delty31+8]
         mov     word ptr [delty21+4],cx
         mov     word ptr [delty21+8],dx
         mov     edx,eax
dr_xchg04:
         mov     dword ptr [deltyx],edx
         mov     eax,dword ptr [delty31]
         mov     edx,dword ptr [delty32]
         cmp     eax,edx
         jge     dr_xchg05
         mov     dword ptr [delty31],edx
         mov     dword ptr [delty32],eax
         mov     cx,word ptr [delty32+4]
         mov     dx,word ptr [delty32+8]
         mov     word ptr [delty31+4],cx
         mov     word ptr [delty31+8],dx
dr_xchg05:
; policz wartosci poczatkowe
         mov     ax,word ptr [bx+40]
         mov     dx,320
         mul     dx
         movzx   edi,ax
         shl     edi,2
         mov     esi,dword ptr [bx+36]
         shl     esi,8
         add     esi,60h
         mov     eax,dword ptr [bx+44]
         mov     edx,dword ptr [bx+48]
         shl     eax,8
         shl     edx,8
         mov     cx,word ptr [dy21]
         lea     ebx,[esi+40h]
         jmp     outer_start
outer_loop:
         pushad
         sar     esi,8
         sar     ebx,8
         sub     bx,si
         jmp     inner_start
inner_loop:
         xor     ecx,ecx
         mov     ch,dh
         mov     cl,ah
         mov     ebp,dword ptr [4*ecx+tex3]
         mov     dword ptr [4*esi+edi+screen_buffer],ebp
         add     ax,word ptr [const_u]
         add     dx,word ptr [const_v]
         inc     si
inner_start:
         dec     bx
         jns     inner_loop
         popad
         add     ax,word ptr [delty21+4]
         add     dx,word ptr [delty21+8]
         add     edi,320*4
         add     esi,dword ptr [delty21]
         add     ebx,dword ptr [deltyx]
outer_start:
         dec     cx
         jns     outer_loop
         dec     byte ptr [tr_part]
         js      dr_skip
         mov     bp,word ptr [delty31+4]
         mov     word ptr [delty21+4],bp
         mov     bp,word ptr [delty31+8]
         mov     word ptr [delty21+8],bp
         mov     ebp,dword ptr [delty31]
         mov     dword ptr [delty21],ebp
         mov     ebp,dword ptr [delty32]
         mov     dword ptr [deltyx],ebp
         mov     cx,word ptr [dy32]
         test    byte ptr [tr_part+1],1
         jz      outer_start
         mov     ebx,dword ptr [dr_konx]
         jmp     outer_start
dr_skip:
;ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ
         fninit
         popa
         add     si,24
         dec     cx
         jnz     draw_faces
         ret

calc_slope_2:
         fild    word ptr [si+36]
         fisub   word ptr [bx+36]
         fdivr   dword ptr [l256]
         fild    word ptr [si+44]
         fisub   word ptr [bx+44]
         fild    word ptr [si+48]
         fisub   word ptr [bx+48]
         jmp     calc_slope_ret

dr_delta:
         pusha
         add     si,36
         add     bx,36
         mov     cx,4
dr_delta_loop:
         mov     ax,word ptr [si]
         sub     ax,word ptr [bx]
         mov     word ptr [fpuout],ax
         fild    word ptr [fpuout]
         add     si,4
         add     bx,4
         loop    dr_delta_loop
         fxch    st(2)
         fdivr   dword ptr [l256]
         fmul    st(3),st(0)
         fmul    st(2),st(0)
         fmulp   st(1),st(0)
         fistp   dword ptr [di+4]
         fistp   dword ptr [di+8]
         fistp   dword ptr [di]
         popa
         ret

matrix_mul:
         mov     ch,3
matrix_mul_loop_y:
         call    mul_vector_matrix
         add    si,12
         sub    bx,12
         dec    ch
         jnz    matrix_mul_loop_y
         ret

mul_vector_matrix:
         mov     cl,3
matrix_mul_loop_x:
         fld     dword ptr [si]
         fmul    dword ptr [bx]
         fld     dword ptr [si+4]
         fmul    dword ptr [bx+12]
         fld     dword ptr [si+8]
         fmul    dword ptr [bx+24]
         faddp   st(1),st(0)
         faddp   st(1),st(0)
         fstp    dword ptr [di]
         add     di,4
         add     bx,4
         dec     cl
         jnz     matrix_mul_loop_x
         ret
