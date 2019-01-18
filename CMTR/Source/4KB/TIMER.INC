newint8h:
       push ds
       push cs
       pop  ds
       inc  word ptr [counter]
       test word ptr [counter],1
       jne cvbnbv
       dec byte ptr [y1adder]
;       dec byte ptr [x1adder]
       dec byte ptr [x1adder]
       inc byte ptr [y2adder]
;       inc byte ptr [x2adder]
       inc byte ptr [x2adder]
cvbnbv:
       push ax
       mov al,20h
       out 20h,al
       pop ax
       pop ds
       iret
