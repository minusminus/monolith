#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "pread.h"
#include "vesa32.h"


#include "texman.h"


void main(void){
 long height,width,i;
 Texman *pics;
 unsigned long *pikczer;

 pics=new Texman(10);
 i=pics->addtex("tex.png");
 pikczer=(unsigned long *)(pics->gettexaddy(i));
 width=pics->textures[0].width;
 height=pics->textures[0].height;

 if(!vesa_set_mode(0x1b0,0)) {puts("Blad vesa!\n");exit(0);}
 vesa_screen_buffer=new long[vesa_buffer_size];
 for(long a=0;a<vesa_buffer_size;a++) vesa_screen_buffer[a]=0;
 for(a=0;(a<height)&&(a<vesa_screen_y);a++)
   for(long b=0;(b<width)&&(b<vesa_screen_x);b++)
     vesa_screen_buffer[(vesa_screen_x*a)+b]=pikczer[(width*a)+b];

 vesa_show_screen();
 getch();
 vesa_dos_mode();
 delete vesa_screen_buffer;

 delete pics;

};
