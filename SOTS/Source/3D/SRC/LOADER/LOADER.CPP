#ifndef LOADER_CPP
 #define LOADER_CPP
//=========================================================================



//========================================================================
//procedury wczytujace sciezki, vertexy i face'y

void readquat(quat *q,FILE *f)
{
     fread(&q->w,4,1,f);
     fread(&q->x,4,1,f);
     fread(&q->y,4,1,f);
     fread(&q->z,4,1,f);

};


void readtrack3(Track3 *t,FILE *f)
{
unsigned long fr;
float eto,efrom,fl;

   fread(&fl,4,1,f);
   fread(&eto,4,1,f);			//\zawsze cos jest tu zapisane
   fread(&efrom,4,1,f); 		///nawet 0.0
   t->frame=fl;
   t->ease_to=eto;
   t->ease_from=efrom;
   fread(&t->vala,4,1,f);
   fread(&t->der1a,4,1,f);
   fread(&t->der2a,4,1,f);
   fread(&t->valb,4,1,f);
   fread(&t->der1b,4,1,f);
   fread(&t->der2b,4,1,f);
   fread(&t->valc,4,1,f);
   fread(&t->der1c,4,1,f);
   fread(&t->der2c,4,1,f);

};


void readtrack1(Track1 *t,FILE *f)
{
unsigned long fr;
float eto,efrom,fl;

   fread(&fl,4,1,f);
   fread(&eto,4,1,f);			//\zawsze cos jest tu zapisane
   fread(&efrom,4,1,f); 		///nawet 0.0
   t->frame=fl;
   t->ease_to=eto;
   t->ease_from=efrom;
//   fread(&t->val,4,1,f);
   fread(&fl,4,1,f);
   t->val=fl;
   fread(&t->der1,4,1,f);
   fread(&t->der2,4,1,f);

};



void readtrackQ(TrackQ *t,FILE *f)
{
unsigned long fr;
float eto,efrom,fl;

   fread(&fl,4,1,f);
   fread(&eto,4,1,f);			//\zawsze cos jest tu zapisane
   fread(&efrom,4,1,f); 		///nawet 0.0
   t->frame=fl;
   t->ease_to=eto;
   t->ease_from=efrom;
   readquat(&t->q,f);
   fread(&t->angle,4,1,f);
   readquat(&t->qa,f);
   readquat(&t->qb,f);

};


void readtrackM(TrackM *t,FILE *f)
{
float fr;
unsigned long num;

     fread(&fr,4,1,f);
     t->frame=fr;
     fread(&num,2,1,f);
     num&=0xffff;
     t->number=num;

};





void readvertex(Vertex *v,FILE *f)
{

   fread(&v->vorig.x,4,1,f);
   fread(&v->vorig.y,4,1,f);
   fread(&v->vorig.z,4,1,f);
   fread(&v->tex.tx,4,1,f);
   fread(&v->tex.ty,4,1,f);
   while(v->tex.tx>255.0) v->tex.tx/=255.0;	//niezbedna normalizacja
   while(v->tex.ty>255.0) v->tex.ty/=255.0;	//bo moga byc wspolrzedne
						//wieksze niz 255.0

};



void readface(Object *o,Face *fc,FILE *f)
{
int num;

    fread(&num,2,1,f);		 //ustalenie adresow pktow
    num&=0xffff;
    fc->p1=&(o->vertbl[num]);
    fread(&num,2,1,f);
    num&=0xffff;
    fc->p2=&(o->vertbl[num]);
    fread(&num,2,1,f);
    num&=0xffff;
    fc->p3=&(o->vertbl[num]);
			       //liczenie normalsa do face'a
    fc->normals.x=-((fc->p2->vorig.y-fc->p1->vorig.y)*(fc->p3->vorig.z-fc->p1->vorig.z)+
		  (fc->p3->vorig.y-fc->p1->vorig.y)*(fc->p2->vorig.z-fc->p1->vorig.z));
    fc->normals.y=(fc->p2->vorig.x-fc->p1->vorig.x)*(fc->p3->vorig.z-fc->p1->vorig.z)-
		  (fc->p3->vorig.x-fc->p1->vorig.x)*(fc->p2->vorig.z-fc->p1->vorig.z);
    fc->normals.z=-((fc->p2->vorig.y-fc->p1->vorig.y)*(fc->p3->vorig.x-fc->p1->vorig.x)-
		  (fc->p3->vorig.y-fc->p1->vorig.y)*(fc->p2->vorig.x-fc->p1->vorig.x));

    fread(&num,2,1,f);		//numer textury
    num&=0xffff;
    fc->texaddr=(unsigned long *)(num);

};



//=======================================================================
//wczytanie elementu bufora morphingu

Morpher::Morpher(FILE *f)
{
long l,i;
float fl;

    fread(&l,2,1,f);	    //ilosc wpisow
    l&=0xffff;
    this->mnum=l;
    this->mtbl=new Morphex[l];	    //tablica pktow
    for(i=0;i<l;i++)
       {
       fread(&fl,4,1,f);
       this->mtbl[i].coords.x=fl;
       fread(&fl,4,1,f);
       this->mtbl[i].coords.y=fl;
       fread(&fl,4,1,f);
       this->mtbl[i].coords.z=fl;
       };
//zamkniecie w boundboxie
float maxx,maxy,maxz,minx,miny,minz;
maxx=minx=this->mtbl[0].coords.x;   //pierwszy na poczatek
maxy=miny=this->mtbl[0].coords.y;
maxz=minz=this->mtbl[0].coords.z;
for(i=1;i<this->mnum;i++)
   {
   if(this->mtbl[i].coords.x>maxx) maxx=this->mtbl[i].coords.x;
   if(this->mtbl[i].coords.x<minx) minx=this->mtbl[i].coords.x;
   if(this->mtbl[i].coords.y>maxy) maxy=this->mtbl[i].coords.y;
   if(this->mtbl[i].coords.y<miny) miny=this->mtbl[i].coords.y;
   if(this->mtbl[i].coords.z>maxz) maxz=this->mtbl[i].coords.z;
   if(this->mtbl[i].coords.z<minz) minz=this->mtbl[i].coords.z;
   };
this->box[0].x=minx;	//wpisujemy box
this->box[0].y=maxy;
this->box[0].z=minz;
this->box[1].x=maxx;
this->box[1].y=maxy;
this->box[1].z=minz;
this->box[2].x=minx;
this->box[2].y=miny;
this->box[2].z=minz;
this->box[3].x=maxx;
this->box[3].y=miny;
this->box[3].z=minz;
this->box[4].x=minx;
this->box[4].y=maxy;
this->box[4].z=maxz;
this->box[5].x=maxx;
this->box[5].y=maxy;
this->box[5].z=maxz;
this->box[6].x=minx;
this->box[6].y=miny;
this->box[6].z=maxz;
this->box[7].x=maxx;
this->box[7].y=miny;
this->box[7].z=maxz;

};


Morpher::~Morpher(void)
{
    delete this->mtbl;
};




//=======================================================================
//wczytanie obiektu z pliku

Object::Object(FILE *f)
{

unsigned long type,flags,fatnum,vert,faces;
unsigned long posnum,rotnum,scalenum,morphnum,pivotnum;
int i,j;


//    fread(&type,2,1,f);	  //czytaj typ
//    fread(&flags,2,1,f);	  //flagi
    fread(&flags,4,1,f);
    fread(&fatnum,2,1,f);	//numer obiektu nadrzednego
    fread(&vert,2,1,f); 	//ilosc vertexow
    fread(&faces,2,1,f);	//ilosc face'ow
//    type&=0xffff;
//    flags&=0xffff;
    fatnum&=0xffff;
    vert&=0xffff;
    faces&=0xffff;
    this->flags=flags;
    this->facenum=faces;
    this->vertnum=vert;
    this->vertbl=new Vertex[vert];
    this->facetbl=new Face[faces];
//    this->fatherob=(Object *)(fatnum);
if(fatnum==0xffff)
  {
  this->fatherob=(Object *)(0xffffffff);
  } else
    {
    this->fatherob=(Object *)(fatnum);
    };


//czytaj vertexy
    for(i=0;i<vert;i++)
       {
       readvertex(&this->vertbl[i],f);
       };

//czytaj face'y
    for(i=0;i<faces;i++)
       {
       readface(this,&this->facetbl[i],f);
       };

//sciezka pozycji obiektu
    fread(&posnum,4,1,f);
    if(posnum>0)
    {
    this->postr=new Track3[posnum];
    this->postrnum=posnum;
    for(i=0;i<posnum;i++)
       {
       readtrack3(&postr[i],f);
       };
    } else
      {
      this->postrnum=0;
      this->postr=NULL;
      };
    this->actpos=0;

//sciezka obrotow
    fread(&rotnum,4,1,f);
    if(rotnum>0)
    {
    this->rottr=new TrackQ[rotnum];
    this->rottrnum=rotnum;
    for(i=0;i<rotnum;i++)
       {
       readtrackQ(&rottr[i],f);
       };
    } else
      {
      this->rottrnum=0;
      this->rottr=NULL;
      };
    this->actrot=0;

//sciezka skalowania
    fread(&scalenum,4,1,f);
    if(scalenum>0)
    {
    this->scaletr=new Track3[scalenum];
    this->scaletrnum=scalenum;
    for(i=0;i<scalenum;i++)
       {
       readtrack3(&scaletr[i],f);
       };
    } else
      {
      this->scaletrnum=0;
      this->scaletr=NULL;
      };
    this->actscale=0;


//sciezka pivotu
    fread(&pivotnum,4,1,f);
    if(pivotnum>0)
    {
    this->pivottr=new Track3[pivotnum];
    this->pivottrnum=pivotnum;
    for(i=0;i<pivotnum;i++)
       {
       readtrack3(&pivottr[i],f);
       };
    } else
      {
      this->pivottrnum=0;
      this->pivottr=NULL;
      };
    this->actpivot=0;


//sciezka morfingu
    fread(&morphnum,4,1,f);
    if(morphnum>0)
    {
    this->morphtr=new TrackM[morphnum];
    this->morphtrnum=morphnum;
    for(i=0;i<morphnum;i++)
       {
       readtrackM(&morphtr[i],f);
       };
    } else
      {
      this->morphtrnum=0;
      this->morphtr=NULL;
      };
    this->actmorph=0;


//przeliczenie normalsow w punktach
unsigned long ilosc;
float sx,sy,sz;
Vertex *v;

    for(i=0;i<vert;i++)
       {
       sx=sy=sz=0.0;		//inicjalizacja wartosci
       ilosc=0;
       v=&this->vertbl[i];	//adres tego wierzcholka
       for(j=0;j<faces;j++)
	  {		    //sumowanie wartosci
	  if((v==this->facetbl[j].p1)||
	    (v==this->facetbl[j].p2)||
	    (v==this->facetbl[j].p3))
	    {
	    ilosc++;			//dodaj kolejne wartosci
	    sx+=facetbl[j].normals.x;
	    sy+=facetbl[j].normals.y;
	    sz+=facetbl[j].normals.z;
	    };
	  };
       sx/=(float)(ilosc);		//usrednienie
       sy/=(float)(ilosc);
       sz/=(float)(ilosc);
       this->vertbl[i].norig.x=sx;	//zapisz
       this->vertbl[i].norig.y=sy;
       this->vertbl[i].norig.z=sz;
       normalize(&this->vertbl[i].norig,1.0);	//normalizuj
       };

//zamkniecie w boundboxie
float maxx,maxy,maxz,minx,miny,minz;
maxx=minx=this->vertbl[0].vorig.x;   //pierwszy na poczatek
maxy=miny=this->vertbl[0].vorig.y;
maxz=minz=this->vertbl[0].vorig.z;
for(i=1;i<this->vertnum;i++)
   {
   if(this->vertbl[i].vorig.x>maxx) maxx=this->vertbl[i].vorig.x;
   if(this->vertbl[i].vorig.x<minx) minx=this->vertbl[i].vorig.x;
   if(this->vertbl[i].vorig.y>maxy) maxy=this->vertbl[i].vorig.y;
   if(this->vertbl[i].vorig.y<miny) miny=this->vertbl[i].vorig.y;
   if(this->vertbl[i].vorig.z>maxz) maxz=this->vertbl[i].vorig.z;
   if(this->vertbl[i].vorig.z<minz) minz=this->vertbl[i].vorig.z;
   };
this->box[0].x=minx;	//wpisujemy box
this->box[0].y=maxy;
this->box[0].z=minz;
this->box[1].x=maxx;
this->box[1].y=maxy;
this->box[1].z=minz;
this->box[2].x=minx;
this->box[2].y=miny;
this->box[2].z=minz;
this->box[3].x=maxx;
this->box[3].y=miny;
this->box[3].z=minz;
this->box[4].x=minx;
this->box[4].y=maxy;
this->box[4].z=maxz;
this->box[5].x=maxx;
this->box[5].y=maxy;
this->box[5].z=maxz;
this->box[6].x=minx;
this->box[6].y=miny;
this->box[6].z=maxz;
this->box[7].x=maxx;
this->box[7].y=miny;
this->box[7].z=maxz;



//    this->fatherob=NULL;
};



//destruktor obiektu
Object::~Object(void)
{

       delete this->vertbl;
       delete this->facetbl;
       delete this->postr;
       delete this->scaletr;
       delete this->pivottr;
       delete this->rottr;
       delete this->morphtr;

};





//=======================================================================
//wczytanie kamery z pliku
Camera::Camera(FILE *f)
{
unsigned long type,fatnum,fatnum2;
unsigned long posnum,trgnum,rollnum,FOVnum;
float FOV;
int i,j;



   fread(&type,4,1,f);
   fread(&FOV,4,1,f);
   fread(&fatnum,2,1,f);
   fread(&fatnum2,2,1,f);
   fatnum&=0xffff;
   fatnum2&=0xffff;
   this->FOV=FOV;
//   this->fatherob=(Object *)(fatnum);
//   this->fatherob2=(Object *)(fatnum2);
if(fatnum==0xffff)
  {
  this->fatherob=(Object *)(0xffffffff);
  } else
    {
    this->fatherob=(Object *)(fatnum);
    };
if(fatnum2==0xffff)
  {
  this->fatherob2=(Object *)(0xffffffff);
  } else
    {
    this->fatherob2=(Object *)(fatnum2);
    };


//sciezka pozycji kamery
    fread(&posnum,4,1,f);
    if(posnum>0)
    {
    this->postr=new Track3[posnum];
    this->postrnum=posnum;
    for(i=0;i<posnum;i++)
       {
       readtrack3(&postr[i],f);
       };
    } else
      {
      this->postrnum=0;
      this->postr=NULL;
      };
    this->actpos=0;

//sciezka pozycji trg
    fread(&trgnum,4,1,f);
    if(trgnum>0)
    {
    this->trgtr=new Track3[trgnum];
    this->trgtrnum=trgnum;
    for(i=0;i<trgnum;i++)
       {
       readtrack3(&trgtr[i],f);
       };
    } else
      {
      this->trgtrnum=0;
      this->trgtr=NULL;
      };
    this->acttrg=0;

//sciezka roll'a
    fread(&rollnum,4,1,f);
    if(rollnum>0)
    {
    this->rolltr=new Track1[rollnum];
    this->rolltrnum=rollnum;
    for(i=0;i<rollnum;i++)
       {
       readtrack1(&rolltr[i],f);
       };
    } else
      {
      this->rolltrnum=0;
      this->rolltr=NULL;
      };
    this->actroll=0;

//sciezka FOV
    fread(&FOVnum,4,1,f);
    if(FOVnum>0)
    {
    this->FOVtr=new Track1[FOVnum];
    this->FOVtrnum=FOVnum;
    for(i=0;i<FOVnum;i++)
       {
       readtrack1(&FOVtr[i],f);
       };
    } else
      {
      this->FOVtrnum=0;
      this->FOVtr=NULL;
      };
    this->actFOV=0;



//   this->fatherob=NULL;
//   this->fatherob2=NULL;
   this->aspectratio=0.75;

};



//destruktor kamery
Camera::~Camera(void)
{

       delete this->postr;
       delete this->trgtr;
       delete this->rolltr;
       delete this->FOVtr;
};






//=======================================================================
//wczytanie sceny

Scene::Scene(const char *file,Texman *texman)
{
FILE *f;
unsigned char id[3];
unsigned long obnum,camnum,lightnum,morphcount;
float firstfr,lastfr;
unsigned long ambnum,texnum,facenum;
int i,j,k,p1,p2;
float f1,f2,f3,ff,fn;
void *ptr;
mptr morph1, morph2;
long v1,v2,v3,v,type;
Face *face;
char tname[13];
unsigned char c;
unsigned long **texes;
Object *o;

     f=fopen(file,"rb");
     fread(&id,1,3,f);
     if((id[0]=='V')&&(id[1]=='D')&&(id[2]=='S'))
       {
       fread(&obnum,4,1,f);
       fread(&camnum,4,1,f);
       fread(&lightnum,4,1,f);
       fread(&firstfr,4,1,f);
       fread(&lastfr,4,1,f);
       fread(&texnum,4,1,f);
       fread(&morphcount,4,1,f);
       this->obnum=obnum;
       this->camnum=camnum;
       this->lightnum=lightnum;
       this->morphnum=morphcount;
       this->firstfr=firstfr;
       this->lastfr=lastfr;
       this->activecam=0;	   //inicjalizacja pierwszej kamery
       this->texnum=texnum;

       fread(&this->ambient.r,4,1,f);	//r	wczytaj dane ambientu
       fread(&this->ambient.g,4,1,f);	//g
       fread(&this->ambient.b,4,1,f);	//b
       fread(&ambnum,4,1,f);
       if(ambnum>0)
	 {
	 this->ambient.trnum=ambnum;
	 this->ambient.tr=new Track3[ambnum];
	 for(i=0;i<ambnum;i++)
	    {
	    readtrack3(&ambient.tr[i],f);
	    };
	 } else
	   {
	   this->ambient.trnum=0;
	   this->ambient.tr=NULL;
	   };


       this->obtbl=NULL;
       this->camtbl=NULL;
       this->lighttbl=NULL;

       if(obnum>0)		//obiekty
	 {
	 this->obtbl=new optr[obnum];
	 for(i=0;i<obnum;i++)
	    {
	    this->obtbl[i]=new Object(f);
	    };
	 };

       if(lightnum>0)		//swiatla
	 {

	 };

       if(camnum>0)		//kamery
	 {
	 this->camtbl=new cptr[camnum];
	 for(i=0;i<camnum;i++)
	    {
	    this->camtbl[i]=new Camera(f);
	    };
	 };

       if(morphcount>0) 	//bufor morfingu
	 {
	 this->morphtbl=new mptr[morphcount];
	 for(i=0;i<morphcount;i++)
	    {
	    this->morphtbl[i]=new Morpher(f);
	    };
	 };


    //bufor textur
    if(texnum>0)
    {
    texes=new unsigned long *[texnum];
    for(i=0;i<texnum;i++)
       {		  //wczytujemy textury
       j=0;c='a';
       while(c!=0)
       {	   //nazwa
       fread(&c,1,1,f);
       tname[j]=c;
       j++;
       };
       j=texman->addtex((const char *)(&tname));  //laduj texture
       texes[i]=(unsigned long *)(texman->gettexaddy(j));	     //wez adres od razu
       };
    } else {texes=NULL;};

       };
   fclose(f);

     //tworzenie powiazan adresow potomkow i rodzicow
     for(i=0;i<obnum;i++)
	{
	 ptr=this->obtbl[i]->fatherob;
	 if((unsigned long)(ptr)!=0xffffffff)
	   {
	    ptr=this->obtbl[(unsigned long)(ptr)];
	    this->obtbl[i]->fatherob=(Object *)(ptr);
	   } else
	     {
	     this->obtbl[i]->fatherob=NULL;
	     };
	};
     for(i=0;i<camnum;i++)
	{
	 ptr=this->camtbl[i]->fatherob;
	 if((unsigned long)(ptr)!=0xffffffff)
	   {
	    ptr=this->obtbl[(unsigned long)(ptr)];
	    this->camtbl[i]->fatherob=(Object *)(ptr);
	   } else
	     {
	     this->camtbl[i]->fatherob=NULL;
	     };
	 ptr=this->camtbl[i]->fatherob2;
	 if((unsigned long)(ptr)!=0xffffffff)
	   {
	    ptr=this->obtbl[(unsigned long)(ptr)];
	    this->camtbl[i]->fatherob2=(Object *)(ptr);
	   } else
	     {
	     this->camtbl[i]->fatherob2=NULL;
	     };
	};

    //pzeliczanie delt w buforze morfingu
    for(i=0;i<obnum;i++)
       {
       if(this->obtbl[i]->morphtrnum>0)
	 {			       //przelicz dla danego obiektu
	 face=this->obtbl[i]->facetbl; //tablice danego obiektu
	 v=(long)(this->obtbl[i]->vertbl);  //adres pierwszego pktu
	 //liczenie normalsow dla kazdego wpisu
	 for(j=0;j<this->obtbl[i]->morphtrnum;j++)
	    {
	    p1=this->obtbl[i]->morphtr[j].number; //ilosc wpisow w morpherze
	    morph1=this->morphtbl[p1];		  //morpher w klatce
	    for(k=0;k<p1;k++)
	       {	      //trzeba wyzerowac odpowiednie pola
	       morph1->mtbl[k].norms.x=0.0;	 //od razu sumy normalsow
	       morph1->mtbl[k].norms.y=0.0;
	       morph1->mtbl[k].norms.z=0.0;
	       morph1->mtbl[k].dn.x=0.0;	 //od razu ilosc wystapien
	       };
	    for(k=0;k<this->obtbl[i]->facenum;k++)  //liczymy normalsy
	       {				    //w face'ach
	       v1=(long)(face[k].p1);
	       v2=(long)(face[k].p2);
	       v3=(long)(face[k].p3);
	       v1-=v;v2-=v;v3-=v;
	       v1/=sizeof(Vertex);	//3 numery vertexow
	       v2/=sizeof(Vertex);	//czyli indeksy w tablicy
	       v3/=sizeof(Vertex);	//pktow
	       //bez niszczenia danych normalsow w face'ach
	       f1=-((morph1->mtbl[v2].coords.y-morph1->mtbl[v1].coords.y)*(morph1->mtbl[v3].coords.z-morph1->mtbl[v1].coords.z)+
		  (morph1->mtbl[v3].coords.y-morph1->mtbl[v1].coords.y)*(morph1->mtbl[v2].coords.z-morph1->mtbl[v1].coords.z));
	       f2=(morph1->mtbl[v2].coords.x-morph1->mtbl[v1].coords.x)*(morph1->mtbl[v3].coords.z-morph1->mtbl[v1].coords.z)-
		  (morph1->mtbl[v3].coords.x-morph1->mtbl[v1].coords.x)*(morph1->mtbl[v2].coords.z-morph1->mtbl[v1].coords.z);
	       f3=-((morph1->mtbl[v2].coords.y-morph1->mtbl[v1].coords.y)*(morph1->mtbl[v3].coords.x-morph1->mtbl[v1].coords.x)-
		  (morph1->mtbl[v3].coords.y-morph1->mtbl[v1].coords.y)*(morph1->mtbl[v2].coords.x-morph1->mtbl[v1].coords.x));
	       //od razu mozna je dodac
	       morph1->mtbl[v1].norms.x+=f1;
	       morph1->mtbl[v1].norms.y+=f2;
	       morph1->mtbl[v1].norms.z+=f3;
	       morph1->mtbl[v2].norms.x+=f1;
	       morph1->mtbl[v2].norms.y+=f2;
	       morph1->mtbl[v2].norms.z+=f3;
	       morph1->mtbl[v3].norms.x+=f1;
	       morph1->mtbl[v3].norms.y+=f2;
	       morph1->mtbl[v3].norms.z+=f3;
	       //i policzyc wystapienia
	       morph1->mtbl[v1].dn.x+=1.0;
	       morph1->mtbl[v2].dn.x+=1.0;
	       morph1->mtbl[v3].dn.x+=1.0;
	       };
	    for(k=0;k<p1;k++)	//dzielimy
	       {
	       morph1->mtbl[k].norms.x/=morph1->mtbl[k].dn.x;
	       morph1->mtbl[k].norms.y/=morph1->mtbl[k].dn.x;
	       morph1->mtbl[k].norms.z/=morph1->mtbl[k].dn.x;
	       normalize(&morph1->mtbl[k].norms,1.0);  //i normalizujemy
	       };
	    };
	 //liczenie delt dla wszystkich wpisow
	 for(j=0;j<this->obtbl[i]->morphtrnum-1;j++)
	    {				    //dla wszystkich wpisow
	    f1=this->obtbl[i]->morphtr[j].frame;
	    f2=this->obtbl[i]->morphtr[j+1].frame;
	    ff=f2-f1;
	    p1=this->obtbl[i]->morphtr[j].number;	 //pozycje w buforze
	    p2=this->obtbl[i]->morphtr[j+1].number;
	    morph1=this->morphtbl[p1];		    //2 kolejne wpisy
	    morph2=this->morphtbl[p2];
	    for(k=0;k<morph1->mnum;k++)
	       {
	       //liczymy delty vertexow
	       fn=(morph2->mtbl[k].coords.x-morph1->mtbl[k].coords.x)/ff;
	       morph1->mtbl[k].dv.x=fn;
	       fn=(morph2->mtbl[k].coords.y-morph1->mtbl[k].coords.y)/ff;
	       morph1->mtbl[k].dv.y=fn;
	       fn=(morph2->mtbl[k].coords.z-morph1->mtbl[k].coords.z)/ff;
	       morph1->mtbl[k].dv.z=fn;
	       //liczymy delty normalsow
	       fn=(morph2->mtbl[k].norms.x-morph1->mtbl[k].norms.x)/ff;
	       morph1->mtbl[k].dn.x=fn;
	       fn=(morph2->mtbl[k].norms.y-morph1->mtbl[k].norms.y)/ff;
	       morph1->mtbl[k].dn.y=fn;
	       fn=(morph2->mtbl[k].norms.z-morph1->mtbl[k].norms.z)/ff;
	       morph1->mtbl[k].dn.z=fn;
	       };
	    for(k=0;k<8;k++)
	       { //delty boundboxow
	       fn=(morph2->box[k].x-morph1->box[k].x)/ff;
	       morph1->dbox[k].x=fn;
	       fn=(morph2->box[k].y-morph1->box[k].y)/ff;
	       morph1->dbox[k].y=fn;
	       fn=(morph2->box[k].z-morph1->box[k].z)/ff;
	       morph1->dbox[k].z=fn;
	       };
	    };
	 j=this->obtbl[i]->morphtrnum-1;  //ostatni wpis z deltami=0
	 p1=this->obtbl[i]->morphtr[j].number;
	 morph1=this->morphtbl[p1];
	 for(k=0;k<morph1->mnum;k++)
	    {
	    morph1->mtbl[k].dv.x=0.0;
	    morph1->mtbl[k].dv.x=0.0;
	    morph1->mtbl[k].dv.x=0.0;
	    morph1->mtbl[k].dn.x=0.0;
	    morph1->mtbl[k].dn.x=0.0;
	    morph1->mtbl[k].dn.x=0.0;
	    };
	 for(k=0;k<8;k++)
	    {
	    morph1->dbox[k].x=0.0;
	    morph1->dbox[k].y=0.0;
	    morph1->dbox[k].z=0.0;
	    };
	 };

       };


    //wpisywanie adresow textur do face'ow
    for(i=0;i<obnum;i++)
    {
    if((this->obtbl[i]->flags&0xffff)!=0)
       {
       for(j=0;j<this->obtbl[i]->facenum;j++)
	  {
	  face=&this->obtbl[i]->facetbl[j];
	  face->texaddr=texes[(unsigned long)(face->texaddr)];
	  };
       };
    };

    delete texes;



    //zliczanie face'ow
    facenum=0;
    for(i=0;i<obnum;i++)
       {
       facenum+=this->obtbl[i]->facenum;
       };
    //przydziel tablice dla face'ow do rysowania
    facenum*=2;
    this->drawtbl=new fptr[facenum];
    this->drawtbl2=new fptr[facenum];

    //kopiowanie bitow typu do face'ow
    for(i=0;i<obnum;i++)
       {
       o=this->obtbl[i];
       type=o->flags&0xffff;
       for(j=0;j<o->facenum;j++)
	  {
	  face=&o->facetbl[j];
	  face->flags=(face->flags&0xffff0000)|type;
	  };
       };



//debug info
/*     printf("zaladowano :\n");
     printf("obiektow : %d\n",this->obnum);
     printf("kamer    : %d\n",this->camnum);
     printf("swiatel  : %d\n",this->lightnum);
     printf("textur   : %d\n",this->texnum);
     printf("razem facow : %d\n",facenum/2);
     printf("pierwsza klatka  : %f\n",this->firstfr);
     printf("ostatnia klatka  : %f\n",this->lastfr);*/

};


//destruktor sceny
Scene::~Scene(void)
{
unsigned long i;


      for(i=0;i<this->obnum;i++)	//usun obiekty
	 {
	  delete this->obtbl[i];
	 };
      delete this->obtbl;
      for(i=0;i<this->lightnum;i++)	   //usun swiatla
	 {
	  delete this->lighttbl[i];
	 };
      delete this->lighttbl;
      for(i=0;i<this->camnum;i++)	 //usun kamery
	 {
	  delete this->camtbl[i];
	 };
      delete this->obtbl;
					//usun ambient
      delete this->ambient.tr;
      delete this->drawtbl;		//usuniecie tablic face'ow
      delete this->drawtbl2;

      for(i=0;i<this->morphnum;i++)	//usun bufor moprhingu
	 {
	  delete this->morphtbl[i];
	 };
      delete this->morphtbl;


//debug info
//	printf("usunieto scene\n");


};











//=========================================================================
#endif
