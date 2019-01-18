//tu jedziemy z intrem




part=1;


//czesc 1
fadeval=255.0;
fadedir=-1.0;
rowcnt=0;

while((koniec==0)&&(part==1))
{

vu.l=0x0;
MEMFILL(bufor,vu,320*240);     //czysc bufor
vu.l=(int)(256.0*65535.0/10000.0);  // 1/maxZ
MEMFILL(zbufor,vu,320*240);	   //czysc zbufor


//klatka=(float)(frame%maxframe);
klatka=(float)(frame);
klatka*=fps/(float)(refresh);
l=(long)(klatka);
klatka=(float)(l%maxframe);

sc->activecam=kamera;
render(sc,bufor,zbufor,klatka);      //wersja dla deusa
vu.l=0x0;
MEMFILL(&bufor[320*29],vu,320);      //pierwsza linijka renderingu :)


//fadeval-=(float)(rowcnt)*(255.0/189.0);
k=(long)(fadeval-(float)(rowcnt)*(255.0/189.0));
if(k<0) k=0;
FADEOUT(&bufor[320*30],k,320*180);



show_buffer();


};


//czesc 2
rowcnt=0;
extra=0;

while((koniec==0)&&(part==2))
{

vu.l=0x0;
MEMFILL(bufor,vu,320*240);     //czysc bufor
vu.l=(int)(256.0*65535.0/10000.0);  // 1/maxZ
MEMFILL(zbufor,vu,320*240);	   //czysc zbufor


//klatka=(float)(frame%maxframe);
klatka=(float)(frame);
klatka*=fps/(float)(refresh);
l=(long)(klatka);
klatka=(float)(l%maxframe);

sc->activecam=kamera;
render(sc,bufor,zbufor,klatka);      //wersja dla deusa
vu.l=0x0;
MEMFILL(&bufor[320*29],vu,320);      //pierwsza linijka renderingu :)



if(rowcnt==1)
{
k=extra<<4;
if(k<0) k=0;
if(k>255) k=255;
FADEOUT(&bufor[320*30],k,320*180);
};



show_buffer();


};




//czesc 3
//tu mrugnie sobie obrazek
while((koniec==0)&&(part==3))
{

show_buffer();
};





//czesc 4
//tu jedziemy dalej
while((koniec==0)&&(part==4))
{

vu.l=0x0;
MEMFILL(bufor,vu,320*240);     //czysc bufor
vu.l=(int)(256.0*65535.0/10000.0);  // 1/maxZ
MEMFILL(zbufor,vu,320*240);	   //czysc zbufor


//klatka=(float)(frame%maxframe);
klatka=(float)(frame);
klatka*=fps/(float)(refresh);
l=(long)(klatka);
klatka=(float)(l%maxframe);

sc->activecam=kamera;
render(sc,bufor,zbufor,klatka);      //wersja dla deusa
vu.l=0x0;
MEMFILL(&bufor[320*29],vu,320);      //pierwsza linijka renderingu :)




show_buffer();


};

