#ifndef INTERP_CPP
 #define INTERP_CPP
//=========================================================================
//procedury do interpolacji track'ow



//=========================================================================
#define M_PI 3.14159265358979324
#define EPSILON 1.0e-3



//=========================================================================
//ease
float ease (float t, float a, float b)
{
  float k;
  float s = a+b;

  if (s == 0.0) return t;
  if (s > 1.0) {
    a = a/s;
    b = b/s;
  }
  k = 1.0/(2.0-a-b);
  if (t < a) return ((k/a)*t*t);
    else {
      if (t < 1.0-b) return (k*(2*t-a));
	else {
	  t = 1.0-t;
	  return (1.0-(k/b)*t*t);
	}
    }
}




//quateriony
#include "quats.cpp"




//=========================================================================
//TRACK3
void InterpolateT3(Track3 *track,float frame,Vector *vector,
		   unsigned long *actkey,unsigned long trnum)
{
  float t,t1,t2,t3,t4;
  Track3 *key;
  long iframe;

  iframe=floor(frame);
   //jak ostatni wpis to przepisac
   if(iframe>=track[trnum-1].frame)
     {
     vector->x=track[trnum-1].vala;
     vector->y=track[trnum-1].valb;
     vector->z=track[trnum-1].valc;
     return;
     };


    //szukamy klucza z ktorego beda obliczenia
    key=&track[actkey[0]];	   //na poczatek to bedzie ostatnio uzywany klucz
    if(key->frame>=iframe)
      {
      key=track; //jak numer klatki mniejszy to szukamy od poczatku
      actkey[0]=0;
      };
    while(iframe>=key[1].frame)
	 {
	 key=&(key[1]);
	 actkey[0]++;		//odpowiedni numer trzeba tez miec
	 };
    if(key->frame>iframe)
    {
      vector->x=key[0].vala;vector->y=key[0].valb;vector->z=key[0].valc;
      return;
    }

    //obliczanie wartosci
    t=((float)(frame-key[0].frame))/(key[1].frame-key[0].frame);
    t=ease(t,key[0].ease_from,key[1].ease_to);
    t1=2*t*t*t-3*t*t+1;
    t2=t*t*t-2*t*t+t;
    t3=-2*t*t*t+3*t*t;
    t4=t*t*t-t*t;
    vector->x=(key[0].vala*t1)+(key[0].der1a*t2)+(key[1].vala*t3)+(key[0].der2a*t4);
    vector->y=(key[0].valb*t1)+(key[0].der1b*t2)+(key[1].valb*t3)+(key[0].der2b*t4);
    vector->z=(key[0].valc*t1)+(key[0].der1c*t2)+(key[1].valc*t3)+(key[0].der2c*t4);
};




//=========================================================================
//TRACK1
void InterpolateT1(Track1 *track,float frame,float *w,
		   unsigned long *actkey,unsigned long trnum)
{
  float t;
  long iframe;
  Track1 *key;


  iframe=floor(frame);
   if(iframe>=track[trnum-1].frame)
   {
     w[0]=track[trnum-1].val;
     return;
   };


    //szukamy klucza z ktorego beda obliczenia
    key=&track[actkey[0]];	   //na poczatek to bedzie ostatnio uzywany klucz
    if(key->frame>=iframe)
      {
      key=track; //jak numer klatki mniejszy to szukamy od poczatku
      actkey[0]=0;
      };
    while(iframe>=key[1].frame)
	 {
	 key=&(key[1]);
	 actkey[0]++;		//odpowiedni numer trzeba tez miec
	 };
    if(key->frame>iframe)
    {
      w[0]=key[0].val;
      return;
    }

    //obliczenia
    t=((float)(frame-key[0].frame))/(key[1].frame-key[0].frame);
    t=ease(t,key[0].ease_from,key[1].ease_to);
    w[0]=key[0].val*(2*t*t*t-3*t*t+1)+key[0].der1*(t*t*t-2*t*t+t)+key[1].val*(-2*t*t*t+3*t*t)+key[0].der2*(t*t*t-t*t);

};






//=========================================================================
//TRACKQ
void InterpolateTQ(TrackQ *track,float frame,quat *quater,
		   unsigned long *actkey,unsigned long trnum)
{
  TrackQ *key;
  float t,spin;
  quat p,q;
  long iframe;


  iframe=floor(frame);
   if(iframe>=track[trnum-1].frame){
     quater->w=track[trnum-1].q.w;
     quater->x=track[trnum-1].q.x;
     quater->y=track[trnum-1].q.y;
     quater->z=track[trnum-1].q.z;
     return;
   };

    //szukamy klucza z ktorego beda obliczenia
    key=&track[actkey[0]];	   //na poczatek to bedzie ostatnio uzywany klucz
    if(key->frame>=iframe)
      {
      key=track; //jak numer klatki mniejszy to szukamy od poczatku
      actkey[0]=0;
      };
    while(iframe>=key[1].frame)
	 {
	 key=&(key[1]);
	 actkey[0]++;		//odpowiedni numer trzeba tez miec
	 };
    if(key->frame>iframe) {
      quater->w=key->q.w;
      quater->x=key->q.x;
      quater->y=key->q.y;
      quater->z=key->q.z;
      return;
    }

    //obliczenia
    t=((float)(frame-key[0].frame))/((float)(key[1].frame-key[0].frame));
    t=ease(t,key[0].ease_from,key[1].ease_to);
    qt_slerplextraspin(&key[0].q,&key[1].q,t,&p,key[0].extraspin);
    qt_slerplextraspin(&key[0].qb, &key[1].qa,t,&q,key[0].extraspin);
//    qt_slerpl(&key[0].q,&key[1].q,t,&p);
//    qt_slerpl(&key[0].qb, &key[1].qa,t,&q);
    t = (((1.0-t)*2.0)*t);
    qt_slerpl (&p,&q,t,quater);

};


//=========================================================================
//TRACKM
void InterpolateTM(TrackM *track,float frame,Object *o,mptr *mtbl,
		   unsigned long *actkey,unsigned long trnum)
{
  float t;
  long iframe,i,j,k;
  TrackM *key;
  Morpher *morph;


  iframe=floor(frame);
   if(iframe>=track[trnum-1].frame)   //jak wiekszy numer klatki od
   {				      //ilosci wpisow to ostatni
   morph=mtbl[track[trnum-1].number];	      //odpowieni wpis
   for(i=0;i<morph->mnum;i++)
      { 		      //kopiowanie ostatniego wpisu
      o->vertbl[i].vorig=morph->mtbl[i].coords;
      o->vertbl[i].norig=morph->mtbl[i].norms;
      };
   return;
   };


    //szukamy klucza z ktorego beda obliczenia
    key=&track[actkey[0]];	   //na poczatek to bedzie ostatnio uzywany klucz
    if(key->frame>=iframe)
      {
      key=track; //jak numer klatki mniejszy to szukamy od poczatku
      actkey[0]=0;
      };
    while(iframe>=key[1].frame)
	 {
	 key=&(key[1]);
	 actkey[0]++;		//odpowiedni numer trzeba tez miec
	 };
    if(key->frame>iframe)
    {
   morph=mtbl[key[0].number];	      //odpowieni wpis
   for(i=0;i<morph->mnum;i++)
      { 		      //kopiowanie wpisu
      o->vertbl[i].vorig=morph->mtbl[i].coords;
      o->vertbl[i].norig=morph->mtbl[i].norms;
      };
      return;
    }

    //obliczenia
//    t=(frame-key[0].frame)/(key[1].frame-key[0].frame);
    t=(frame-key[0].frame);
    morph=mtbl[key[0].number];
    for(i=0;i<morph->mnum;i++)
       {
      o->vertbl[i].vorig.x=(t*morph->mtbl[i].dv.x)+morph->mtbl[i].coords.x;
      o->vertbl[i].vorig.y=(t*morph->mtbl[i].dv.y)+morph->mtbl[i].coords.y;
      o->vertbl[i].vorig.z=(t*morph->mtbl[i].dv.z)+morph->mtbl[i].coords.z;
      o->vertbl[i].norig.x=(t*morph->mtbl[i].dn.x)+morph->mtbl[i].norms.x;
      o->vertbl[i].norig.y=(t*morph->mtbl[i].dn.y)+morph->mtbl[i].norms.y;
      o->vertbl[i].norig.z=(t*morph->mtbl[i].dn.z)+morph->mtbl[i].norms.z;
       };
    for(i=0;i<8;i++)
       {	     //przepisz boundbox zmorfowany
       o->box[i].x=(t*morph->dbox[i].x)+morph->box[i].x;
       o->box[i].y=(t*morph->dbox[i].y)+morph->box[i].y;
       o->box[i].z=(t*morph->dbox[i].z)+morph->box[i].z;
       };

};



//=========================================================================
#endif
