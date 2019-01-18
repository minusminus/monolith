#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include "memory.h"
#include ".\midas\include\midasdll.h"
#include "vesa32.h"
#include "bufor.h"
#include "pread.h"
#include "3d.h"


int k,i,j;
long l;



//==========================================
//ZMIENNE DLA SCENY Z MIASTEM
Scene *sc;
Texman *tex;
float *fastdivtbl;
unsigned long *bufor;
unsigned long *zbufor;


//==========================================
//dla midasa i synchronizacji
static unsigned refresh;      //czestotliwosc
volatile unsigned  frame;     //licznik ramek
volatile unsigned  extra;     //extra licznik ramek
MIDASmodule module;	      //i sam modulek
MIDASmodulePlayHandle playhandle;
long position,row;
float fps=15000.0;
long rowcnt;
long pause;

//==========================================
//inne zmienne
int koniec=0;
float klatka;
valun vu;
long maxframe;
long kamera=0;
long part=0;


//==========================================
//grafika
unsigned long *logo;


//==========================================
//swiatlo
float sx,sy,sz,spow;	//pozycja i jasnosc [natezenie]




//==========================================
//synchronizacja
float fadedir;	 //kierunek 1 lub -1
float fadeval;	 //aktualna wartosc fade'a
float fadepower; //wzmocnienie fade'a poczatkowo 1.0
float fadedelta; //wartosc dodawana do fade'a [zmiana na 1 sekunde]
float fadetimes; //krotnosc fadeval [co by sie zgralo z zegarem]
long f3d,fout3d,flogo,flogofade;



//==========================================
//specjalnie dla double bufferingu
long buffer_number=0;

void MIDAS_CALL timer_proc(void)	//wywolywany na poczatku ramki
{
  if(vesa_buffer_flag)
    vesa_show_buffer(buffer_number^1);

    if(pause==1) frame++;    //zwiekszamy licznik klatek
    extra++;
};

void show_buffer(){
  while(vesa_buffer_flag);
  vesa_set_buffer(buffer_number++);
  vesa_show_screen();


};

void MIDAS_CALL key_proc(void)	//wywolane na koncu ramki
{

if(kbhit())	//sprawdz od razu czy nie byl wcisniety ESC
{
int c=getch();
if(c==27) koniec=1;
};

};





//==========================================
//PROCKI DLA SYNCHRONIZACJI
void MIDAS_CALL SyncCallback(unsigned syncNum, unsigned position, unsigned row)
{
    /* Prevent warnings: */
    position = position;
    row = row;

    /* Check if the infobyte is interesting - do something only when command
       "W42" is encountered: */

    switch(syncNum)
    {
    case 0x00 : koniec=1;break; 	//koniec

#ifndef testing

//duperele

    case 0xf0 : fadeval=0.0; break;	//ustawia wartosc fade'a
    case 0xf1 : fadeval=255.0; break;
    case 0xf2 : fadedir*=-1.0; break;	//kierunek fade'owania
    case 0xf3 : kamera=(kamera+1)%sc->camnum; break; //zmiana kamery
    case 0xf4 : fadeval=64.0; break;
    case 0xf5 : fadeval=128.0; break;
    case 0xf6 : fadeval=192.0; break;
    case 0xf7 : f3d=f3d^1; flogo=flogo^1; break; //zmiana wyswietlania

//kolejne czesci [ustawienia zmiennych]

    case 0x01 : f3d=0;			//poczatek
		fout3d=0;
		flogo=1;
		flogofade=1;
		fadedir=-1.0;
		fadeval=255.0;
		fadepower=1.0;
		fadedelta=12.75;	//ok 20 sekund
		extra=0;
		fps=15000.0;
		break;

    case 0x02 : f3d=0;			//pomrugamy sobie
		fout3d=0;
		flogo=1;
		flogofade=1;
		fadedir=1.0;
		fadeval=0.0;
		fadepower=1.0;
		fadedelta=1024.0;	 //ok 0.25 sek
		extra=0;
		pause=0;
		break;

    case 0x03 : f3d=0;			//leca texty
		fout3d=1;
		flogo=1;
		flogofade=1;
		fadedir=1.0;
		fadeval=0.0;
		fadepower=1.0;
		fadedelta=0.0;	      //ok 0.25 sek
		pause=1;
		fps=30000.0;
		break;

    case 0x04 : f3d=0;			//zciemnimy teraz
		fout3d=0;
		flogo=1;
		flogofade=1;
		fadedir=1.0;
		fadeval=0.0;
		fadepower=1.0;
		fadedelta=51.0;        //ok 5 sek
		extra=0;
		break;

    case 0x05 : f3d=1;			//pomrugamy logosem
		fout3d=1;
		flogo=0;
		flogofade=0;
		fadedir=1.0;
		fadeval=0.0;
		fadepower=1.0;
		fadedelta=255.0;	//ok 2 sek
		extra=0;
		break;

    case 0x06 : f3d=0;			//koncowka
		fout3d=1;
		flogo=0;
		flogofade=0;
		fadedir=1.0;
		fadeval=64.0;
		fadepower=1.0;
		fadedelta=0.0;	      //staly fade na logosie
		extra=0;
		kamera=2;
		fps=15000.0;
		break;

    case 0x07 : f3d=1;			//jeszcze tylko fragmencik
		fout3d=1;		//bedziemy jechac na zmiane
		flogo=0;
		flogofade=1;
		fadedir=1.0;
		fadeval=64.0;
		fadepower=1.0;
		fadedelta=0.0;	      //staly fade na logosie
		extra=0;
		kamera=2;
		break;



#endif

    };

}





















//==========================================
//GLOWNY PROGRAM
void main(void)
{




//midas init
MIDASstartup();

if(MIDASloadConfig("deus.cfg")==0)
  {
  MIDASclose();
  printf("run SETUP.EXE first\n");
  return;
  };





//inicjalizacja 3d i texturek
//tex=new Texman(5);
sc=new Scene("deus.vds",tex);
sc->activecam=0;
preprocesskeys(sc);  //przygotowanie kluczy
maxframe=sc->lastfr;
sc->zmin=10;
sc->setresolution(320,180,320,240,0,0);


//init buforow
bufor=new unsigned long[320*240];
zbufor=new unsigned long[320*240];
vesa_screen_buffer=(long *)(bufor);

//init fastdivtable
fastdivtbl=new float[240];
for(i=0;i<240;i++)
   {
   if(i==0) { fastdivtbl[i]=0.0; }
   else { fastdivtbl[i]=1.0/(float)(i); };
   };
INITTRENG(fastdivtbl);



//ladujemy grafiki
//i=tex->addtex("logo1.png");
//logo=(unsigned long *)tex->gettexaddy(i);
long width,height;
char *logos="logo1.png";
logo=(unsigned long *)read_png(logos,&width,&height);
for(i=0;i<256*80;i++)
   {
   logo[i]&=0xffffff;
   };


printf("\n");
printf("    [ d  e  u  s  .  e	x  .  m  a  c  h  i  n	a  .  r  e  c  o  r  d	s ]\n\n\n");
printf("		   [...simplicity_of_the_statement...]\n\n\n");



//init swiatla
sx=100.0;
sy=200.0;
sz=100.0;
spow=10000.0;

//tu mozna mieszac ze scenka i inne takie
long col;
float wx,wy,wz,lgh,tlgh,tl2;
float tr,tg,tb;
for(i=0;i<sc->obnum;i++)	//nadaj kolory obiektom
   {
   Object *o=sc->obtbl[i];
   if((o->flags&0xff)==0)
   {
   for(j=0;j<o->facenum;j++)
      {
      Face *f=&o->facetbl[j];
      col=((j&0xff)<<16)|((i&0xff)<<8)|(0xff);	//kolor danego face'a
      tr=(float)(j&0xff);
      tg=(float)(i&0xff);
      tb=(float)(0xff);


      //liczymy wektor do pktu w ktorym jest swiatlo
      wx=f->p1->vorig.x-sx;
      wy=f->p1->vorig.y-sy;
      wz=f->p1->vorig.z-sz;
      //dlugosc wektora to natezenie swiatla dla wierzcholka
      lgh=sqrt(wx*wx+wy*wy+wz*wz);
      lgh/=spow;
      lgh=1.0-lgh;	//1 - max, 0 - min natezenie
      if(lgh<0) lgh=0.0;
      //liczymy wektor do pktu w ktorym jest swiatlo
      wx=f->p2->vorig.x-sx;
      wy=f->p2->vorig.y-sy;
      wz=f->p2->vorig.z-sz;
      //dlugosc wektora to natezenie swiatla dla wierzcholka
      tlgh=sqrt(wx*wx+wy*wy+wz*wz);
      tlgh/=spow;
      tlgh=1.0-tlgh;	  //1 - max, 0 - min natezenie
      if(tlgh>0) lgh+=tlgh;
      //liczymy wektor do pktu w ktorym jest swiatlo
      wx=f->p3->vorig.x-sx;
      wy=f->p3->vorig.y-sy;
      wz=f->p3->vorig.z-sz;
      //dlugosc wektora to natezenie swiatla dla wierzcholka
      tlgh=sqrt(wx*wx+wy*wy+wz*wz);
      tlgh/=spow;
      tlgh=1.0-tlgh;	  //1 - max, 0 - min natezenie
      if(tlgh>0) lgh+=tlgh;
      lgh/=3.0;  //natezenie srednie po 3 wierzcholkach face'a


      //korekcja natezenia w zaleznosci od kierunku face'a
      //zaczniemy od pktu srodkowego face'a
      wx=(f->p1->vorig.x+f->p2->vorig.x+f->p3->vorig.x)/3.0;
      wy=(f->p1->vorig.y+f->p2->vorig.y+f->p3->vorig.y)/3.0;
      wz=(f->p1->vorig.z+f->p2->vorig.z+f->p3->vorig.z)/3.0;
      wx-=sx;
      wy-=sy;
      wz-=sz;
      tlgh=sqrt(wx*wx+wy*wy+wz*wz);	//dlugosci wektorow
      tl2=sqrt(f->normals.x*f->normals.x+f->normals.y*f->normals.y+
	       f->normals.z*f->normals.z);
      tlgh=(wx*f->normals.x+wy*f->normals.y+wz*f->normals.z)/(tlgh*tl2);
      if(tlgh>0) {lgh=0.0;} else
		 {	    //to korekcja natezenia
		 lgh*=-tlgh;
		 };


      //odpowiednia do natezenia konwersja koloru
      tr*=lgh;
      tg*=lgh;
      tb*=lgh;

      //laczymy kolorek
      col=((long)(tr))<<16;
      col|=((long)(tg))<<8;
      col|=((long)(tb));
      f->texaddr=(unsigned long *)(col);
      };
   };
   };












//inicjalizacja zmiennych synchronizujacych
fadedir=1.0;
fadeval=255.0;
fadepower=1.0;
fadedelta=1.0;
f3d=fout3d=flogo=flogofade=1;
pause=1;





//odpalamy tryb graficzny
long depth,vesaflags,resx,resy;
depth=vesaflags=0;
resx=320;
resy=240;
unsigned char cc;
printf("Give us your favourite colour depth :\n1. 16 bits\n2. 24 bits\n3. 32 bits\n");
while(depth==0)
{
cc=getch();
if(cc=='1') depth=16;
if(cc=='2') depth=24;
if(cc=='3') depth=32;
};
printf("Give us your special preferences :\n1. double buffering\n2. double pixeling\n3. both of above\n");
cc=0;
while(cc==0)
{
cc=getch();
if(cc=='1')
  {
  vesaflags|=VESA_DOUBLE;
  cc='V';
  };
if(cc=='2')
  {
  vesaflags|=VESA_DPIXEL;
  resx*=2;
  resy*=2;
  cc='V';
  };
if(cc=='3')
  {
  vesaflags|=VESA_DOUBLE;
  vesaflags|=VESA_DPIXEL;
  resx*=2;
  resy*=2;
  cc='V';
  };
if(cc!='V') cc=0;
};

if(!vesa_set_mode(vesa_get_mode(resx,resy,depth),vesaflags))
  {
   MIDASclose();
   printf("We can't initialize your graphics card in chosen mode...\n");
   printf("Probably your card can't handle ");
   if((vesaflags&VESA_DPIXEL)!=0)
     {
     printf("640x480 ");
     } else printf("320x240 ");
   printf("in %d bpp ",depth);
   if((vesaflags&VESA_DOUBLE)!=0)
     {
     printf("with double buffering\n");
     } else printf("\n");
   printf("Sorry\n");
   return;
  };





//synchronizujemy midasa
refresh=MIDASgetDisplayRefreshRate();

if ( !MIDASinit() )
   {
   MIDASclose();
   vesa_dos_mode();
   printf("MIDAS can't be initialized...\n");
   printf("Strange thing...\nSorry\n");
   return;
   };

if ( (module = MIDASloadModule("deus.xm")) == NULL )
   {
   MIDASclose();
   vesa_dos_mode();
   printf("Error while loading music...\n");
   return;
   };


	//podlaczamy procki do midasa
if ( !MIDASsetTimerCallbacks(refresh, TRUE, &timer_proc, NULL, &key_proc) )
   {
   MIDASclose();
   vesa_dos_mode();
   printf("Strange error has occured...\nSorry\n");
   return;
   };


//odpalamy odtwarzanie
if ( ( playhandle=MIDASplayModule(module, TRUE) )==0)
   {
   MIDASclose();
   vesa_dos_mode();
   printf("Can't play the music...\nSorry\n");
   return;
   };

//to mozna wrzucic dopiero po wlaczeniu odtwarzania
if ( !MIDASsetMusicSyncCallback(playhandle,&SyncCallback) ) //synchronizator do paternuf
   {
   MIDASclose();
   vesa_dos_mode();
   printf("Strange error has occured...\nSorry\n");
   return;
   };










//jedziemy z tym koksem
#include "staf2.cpp"





//ending
    /* Remove music sync callback: */
MIDASsetMusicSyncCallback(playhandle,NULL);

    /* Stop playing module: */
MIDASstopModule(playhandle);

    /* Deallocate the module: */
MIDASfreeModule(module);

    /* Remove timer callback: */
MIDASremoveTimerCallbacks();

    /* and finally close the midas */
MIDASclose();



//powrot do trybu textowego
vesa_dos_mode();

//usuniecie 3d i texturek
//delete tex;
delete sc;

delete logo;
//usuniecie buforow
delete bufor;
delete zbufor;
delete fastdivtbl;


printf("All ok\n");



};

