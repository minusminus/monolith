//druga wersja synchronizacji [na flagach]


#ifdef testing
//testy poszczegolnych czesci

//f3d=0;
//fout3d=0;
flogo=0;
//flogofade=0;

fadedir=1.0;
fadeval=64.0;
fadepower=1.0;
fadedelta=0.0;	      //ok 4 sek

#endif

extra=0;

while(koniec==0)
{

vu.l=0x0;
MEMFILL(bufor,vu,320*240);     //czysc bufor



//render scenki
if(f3d==0)
{
vu.l=(int)(256.0*65535.0/10000.0);  // 1/maxZ
MEMFILL(zbufor,vu,320*240);	   //czysc zbufor

if(fps>0.0)
{
klatka=(float)(frame);
klatka*=fps/(float)(refresh);
};
if((long)(klatka)>=maxframe) frame=0;

sc->activecam=kamera;
//sc->activecam=2;
render(sc,bufor,zbufor,klatka);      //wersja dla deusa
vu.l=0x0;
MEMFILL(&bufor[320*29],vu,320);      //pierwsza linijka renderingu :)
};



//fading wyrenderowanej scenki
if(fout3d==0)
{

//parametr bedzie jakos ustawiany
fadetimes=(float)(extra)/((float)(refresh)/1000.0);
fadeval+=fadedir*fadepower*fadetimes*fadedelta;

k=(long)fadeval;
if(k<0) k=0;
if(k>255) k=255;
FADEOUT(&bufor[320*30],k,320*180);
extra=0;
};




//wyswietlenie logosa
if(flogo==0)
{

for(i=0;i<80;i++)
   {
   TRANSPUT(&logo[i*256],&bufor[i*320+32+80*320],256);
   };

};


//fadeing logosa [w buforze]
if(flogofade==0)
{
//parametr bedzie jakos ustawiany
fadetimes=(float)(extra)/((float)(refresh)/1000.0);
fadeval+=fadedir*fadepower*fadetimes*fadedelta;

k=(long)fadeval;
if(k<0) k=0;
if(k>255) k=255;
FADEOUT(&bufor[320*80],k,320*80);
extra=0;
};



show_buffer();

};