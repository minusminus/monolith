#ifndef PROCOB_CPP
 #define PROCOB_CPP
//=========================================================================


//========================================================================
//vertices processing



void processvertices(Vertex *vtbl,Object *o,unsigned long vnum,Camera *cam)
{
int i;
float f;

//obracanie pktow
for(i=0;i<vnum;i++)
   {
    vtbl[i].v3d=vtbl[i].vorig*o->eyemat;
    vtbl[i].v3d=vtbl[i].v3d+o->transl;
    vtbl[i].flags=0;
   };


//obracanie normalsow


//liczenie flag widocznosci w 3d
for(i=0;i<vnum;i++)
   {
   //liczenie flag dla z
   if(vtbl[i].v3d.z<=10.0) vtbl[i].flags|=VIS1;  //minimalny z
   if(vtbl[i].v3d.z>=10000.0) vtbl[i].flags|=VIS3;  //max z

/*
   //liczenie dla bocznych scian piramidy widzenia
   //sciana 2
   f=vtbl[i].v3d.x*cam->focus-vtbl[i].v3d.z*cam->cvalx;
   if(f>=0.0) vtbl[i].flags|=VIS2;
   //sciana 4
   f=vtbl[i].v3d.x*cam->focus-vtbl[i].v3d.z*(-cam->cvalx);
   if(f<=0.0) vtbl[i].flags|=VIS4;
   //sciana 5
//   f=-(vtbl[i].v3d.y*cam->focus-vtbl[i].v3d.z*(-cam->cvaly));
   f=vtbl[i].v3d.z*(-cam->cvaly)-vtbl[i].v3d.y*cam->focus;
   if(f<=0.0) vtbl[i].flags|=VIS5;
   //sciana 6
//   f=-(vtbl[i].v3d.y*cam->focus-vtbl[i].v3d.z*cam->cvaly);
   f=vtbl[i].v3d.z*cam->cvaly-vtbl[i].v3d.y*cam->focus;
   if(f>=0.0) vtbl[i].flags|=VIS6;
*/
   };


};





//========================================================================
//faces processing
unsigned long processfaces(Vector *cvec,Face *ftbl,unsigned long fnum,
			  Face **drawtbl,unsigned long off)
{
unsigned long pos2,pos;
int i;
float fl;
Face *f;
long l;

//wycinanie face'ow tylem
pos=off;
for(i=0;i<fnum;i++)
   {
    f=&ftbl[i];

//    fl=-((f->p2->v3d.y-f->p1->v3d.y)*(f->p3->v3d.x-f->p1->v3d.x)-
//	 (f->p3->v3d.y-f->p1->v3d.y)*(f->p2->v3d.x-f->p1->v3d.x));

fl = f->p3->v3d.x*((f->p1->v3d.z*f->p2->v3d.y)-(f->p1->v3d.y*f->p2->v3d.z))+
     f->p3->v3d.y*((f->p1->v3d.x*f->p2->v3d.z)-(f->p1->v3d.z*f->p2->v3d.x))+
     f->p3->v3d.z*((f->p1->v3d.y*f->p2->v3d.x)-(f->p1->v3d.x*f->p2->v3d.y));

//fl=cvec->x*f->normals.x+cvec->y*f->normals.y+cvec->z*f->normals.z;
//fl=f->normals.z;

    if(fl>0.0)
      {
      drawtbl[pos]=f;
      pos++;
      };

   };
pos2=pos-off;	//ilosc face'ow wlozonych do tablicy


//wyciecie face'ow spoza pola widzenia kamery
pos=off;
for(i=off;i<pos2+off;i++)
    {
    f=drawtbl[i];
    l=(f->p1->flags)&(f->p2->flags)&(f->p3->flags);
    if((l&0x7f)==0)
      {
      f->zsum=f->p1->v3d.z+f->p2->v3d.z+f->p3->v3d.z;
      drawtbl[pos]=drawtbl[i];	//jak widac to przepisz aktualny
      pos++;			//sprawdz nastepny
      };
    };

return pos;
};



//========================================================================
//boxes processing
void processbox(Camera *cam,Object *o)
{
Vector nbox[8]; //po przeksztalceniu
long flags[8];	//falgi widocznosci
long i,l;
float f;

for(i=0;i<8;i++)
   {
   nbox[i]=o->box[i]*o->eyemat;
   nbox[i]=nbox[i]+o->transl;
   flags[i]=0;
   };

//liczenie flag widocznosci w 3d
for(i=0;i<8;i++)
   {
   //liczenie flag dla z
   if(nbox[i].z<=10.0) flags[i]|=VIS1;	//minimalny z
   if(nbox[i].z>=10000.0) flags[i]|=VIS3;  //max z

   //liczenie dla bocznych scian piramidy widzenia
/*
troche dziwne rzeczy wychodza ze znakami - przeciwne niz w clippingu -
chyba ze jest blad w oznaczeniu scian
le dziala
*/
   //sciana 2
   f=nbox[i].x*cam->focus-nbox[i].z*cam->cvalx;
   if(f>0.0) flags[i]|=VIS2;
   //sciana 4
   f=nbox[i].x*cam->focus-nbox[i].z*(-cam->cvalx);
   if(f<0.0) flags[i]|=VIS4;
   //sciana 5
   f=-(nbox[i].z*(-cam->cvaly)-nbox[i].y*cam->focus);
   if(f<0.0) flags[i]|=VIS5;
   //sciana 6
   f=-(nbox[i].z*cam->cvaly-nbox[i].y*cam->focus);
   if(f>0.0) flags[i]|=VIS6;


   };

l=flags[0];
for(i=1;i<8;i++)
   {
   l&=flags[i];
   };
i=o->flags;

if(l!=0) i|=OUNVISBOX; else i&=(OUNVISBOX^0xffffffff);

o->flags=i;
};


long numo;
//========================================================================
//object processing

unsigned long processobject(Object *o,Face **drawtbl,unsigned long off,
			    Camera *cam )
{
unsigned long pos=off;		//pozycja w tablicy face'ow
int i;
Vector camob;	//kamera przeksztalcona do ukladu obiektu
Vector v1;
Matrix mat,mat2;

//sprawdz boundbox
processbox(cam,o);


if(((o->flags&OUNVIS)==0)&&((o->flags&OUNVISBOX)==0)) //czy obiekt jest widoczny
{
numo++;
//przeksztalcenie pktow
processvertices(o->vertbl,o,o->vertnum,cam);


//wyciecie punktow z tylu kamery

//wycinanie face'ow tylem
mat=o->obmat;
mat2=cam->mat;
transmat(&mat);
transmat(&mat2);
v1=o->pos*mat;
/*v1.x=-v1.x;
v1.y=-v1.y;
v1.z=-v1.z;*/

camob=cam->trg*mat2*mat;
camob=camob+o->pos;
pos=processfaces(&camob,o->facetbl,o->facenum,drawtbl,pos);
};


return pos;	//zwroc numer aktualnej wolnej pozycji
};




//=========================================================================
#endif
