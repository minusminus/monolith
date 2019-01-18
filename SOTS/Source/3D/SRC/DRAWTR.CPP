//rysuje trojakt
void drawtriangle(Face *f,void *buf)
{
float fl,fl2;
Vertex *v1,*v2,*v3,*t;
int y1,y2,y3,yt;
float d12,d23,d13,dz12,dz13,dz23;
float z1,z2,z3;
int l;

f->flags&=FPUNVIS;
//liczenie delt
v1=f->p1;
v2=f->p2;
v3=f->p3;

v1->y2d=floor(v1->y2d);
v2->y2d=floor(v2->y2d);
v3->y2d=floor(v3->y2d);

_asm{
pushad
mov esi,[v1]
fld dword ptr[esi+52]
fistp dword ptr[y1]
mov esi,[v2]
fld dword ptr[esi+52]
fistp dword ptr[y2]
mov esi,[v3]
fld dword ptr[esi+52]
fistp dword ptr[y3]
popad
};



//sortowanie wierzcholkow
if(y1>y2)
  {
  t=v1;
  v1=v2;
  v2=t;
  yt=y2;
  y2=y1;
  y1=yt;
  };
if(y1>y3)
  {
  t=v1;
  v1=v3;
  v3=t;
  yt=y3;
  y3=y1;
  y1=yt;
  };
if(y2>y3)
  {
  t=v3;
  v3=v2;
  v2=t;
  yt=y2;
  y2=y3;
  y3=yt;
  };




//linia 1-3
//fl=(v3->y2d-v1->y2d);
l=(v3->y2d-v1->y2d);
if(l>0)
{
z1=(256.0*65536.0)/v1->v3d.z;
z2=(256.0*65536.0)/v2->v3d.z;
z3=(256.0*65536.0)/v3->v3d.z;
//fl=1.0/fl;
fl=fastdivtbl[l];
d13=(v3->x2d-v1->x2d)*fl;
f->d13=(int)(d13*65536.0);
dz13=(z3-z1)*fl;
f->dz13=(int)(dz13);


//linia 1-2
//fl=(v2->y2d-v1->y2d);
l=(v2->y2d-v1->y2d);
if(l>0)
{
//fl=1.0/fl;
fl=fastdivtbl[l];
d12=(v2->x2d-v1->x2d)*fl;
f->d12=(int)(d12*65536.0);
dz12=(z2-z1)*fl;
f->dz12=(int)(dz12);
f->flags|=FP12;
} else {d12=dz12=0;};


//linia 2-3
//fl=(v3->y2d-v2->y2d);
l=(v3->y2d-v2->y2d);
if(l>0)
{
//fl=1.0/fl;
fl=fastdivtbl[l];
d23=(v3->x2d-v2->x2d)*fl;
f->d23=(int)(d23*65536.0);
dz23=(z3-z2)*fl;
f->dz23=(int)(dz23);
f->flags|=FP23;
} else {d23=dz23=0;};


//stale Z

/*fl=(v3->x2d-v1->x2d)*(v2->y2d-v1->y2d)-(v2->x2d-v1->x2d)*(v3->y2d-v1->y2d);
fl2=(z3-z1)*(v2->y2d-v1->y2d)-(z2-z1)*(v3->y2d-v1->y2d);
if(fl!=0)
  fl2=fl2/fl;
f->dzx=(int)(fl2);*/


if(d12!=0)
{
fl2=(dz13-dz12)/(d13-d12);
} else
{
fl2=(dz13-dz23)/(d13-d23);
};
f->dzx=(int)(fl2);



} else {d13=dz13=0;};



//flat(f);	  //rysuj trojkat
inittex(zbufor,bufor,fastdivtbl);
//inittex(zbufor,screen,fastdivtbl);
textr(f);
//check(f,v1,v2,v3);

//keycheck();

};
