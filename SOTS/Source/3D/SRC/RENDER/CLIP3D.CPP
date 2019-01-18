

//kopiowanie vertexa
void cpyvertex(Vertex *src,Vertex *dest)
{
dest->v3d.x=src->v3d.x;
dest->v3d.y=src->v3d.y;
dest->v3d.z=src->v3d.z;
dest->tex.tx=src->tex.tx;
dest->tex.ty=src->tex.ty;
dest->flags=src->flags;

};

//kopiowanie trojkata
void cpyface(Face *src,Face *dest)
{
dest->texaddr=src->texaddr;
dest->flags=src->flags;

};



//=========================================================================
//clipping 3d
//obcina pkty face'a wynik powinien byc w tablicy vvt2 - bo nie ma
//obcinania do sciany przedniej
//wartoscia jest ilosc pktow po obcieciu
long clip3d(Face *f,Camera *cam,Vertex *vvt1,Vertex *vvt2)
{
Vertex *vt1, *vt2, *t;
long i,i1;
float m,Mi,Mi1;
float mt[10];
long l,num;
float zmin;

zmin=cam->zmin;
vt1=&vvt1[0]; vt2=&vvt2[0];
//wstawienie pktow poczatkowych do tablicy
cpyvertex(f->p1,&vt1[0]);
cpyvertex(f->p2,&vt1[1]);
cpyvertex(f->p3,&vt1[2]);
num=3;


//obcinanie do sciany 1 [rzutni]
l=0;
for(i=0;i<num;i++)    //do przedostatniego
   {
   i1=(i+1)%(num);    //zeby mozna bylo zrobic obciecie ostatni->pierwszy
   if((vt1[i].v3d.z>zmin)||(vt1[i1].v3d.z>zmin)) //ktorys punkt widac
     if((vt1[i].v3d.z>zmin)&&(vt1[i1].v3d.z>zmin))  //oba widac
       {
       cpyvertex(&vt1[i],&vt2[l]);
       l++;
       } else	//trzeba obciac
	 {
	 if((vt1[i].v3d.z>zmin)&&(vt1[i1].v3d.z<=zmin))
	   {
	   cpyvertex(&vt1[i],&vt2[l]);
	   l++;
	   };
	   m=(zmin-vt1[i].v3d.z)/(vt1[i1].v3d.z-vt1[i].v3d.z);
	   vt2[l].v3d.x=vt1[i].v3d.x+(vt1[i1].v3d.x-vt1[i].v3d.x)*m;
	   vt2[l].v3d.y=vt1[i].v3d.y+(vt1[i1].v3d.y-vt1[i].v3d.y)*m;
	   vt2[l].v3d.z=zmin;
	   //tu interpolacja potrzebnych skladowych w punkcie
	   vt2[l].tex.tx=vt1[i].tex.tx+(vt1[i1].tex.tx-vt1[i].tex.tx)*m;
	   vt2[l].tex.ty=vt1[i].tex.ty+(vt1[i1].tex.ty-vt1[i].tex.ty)*m;

	   l++; 			 //i nastepny pkt
	 };
   };
num=l;		//ilosc pktow po obcieciu
t=vt2;		//zamiana adresow
vt2=vt1;	//dla przejrzystosci algorytmu
vt1=t;




//clipping dla sciany 2
l=0;
for(i=0;i<num;i++)    //liczenie wspolczynnikow
   {
   mt[i]=vt1[i].v3d.x*cam->focus-vt1[i].v3d.z*cam->cvalx;
   };

for(i=0;i<num;i++)		//obcinanie
   {
   i1=(i+1)%(num);
   if((mt[i]<0.0)||(mt[i1]<0.0))	//czy ktorys widoczny
     if((mt[i]<0.0)&&(mt[i1]<0.0))	//oba widoczne
       {
       cpyvertex(&vt1[i],&vt2[l]);
       l++;
       } else	//trzeba obciac
	 {
	 if((mt[i]<0.0)&&(mt[i1]>=0.0))
	   {
	   cpyvertex(&vt1[i],&vt2[l]);
	   l++;
	   };
	 m=mt[i]/(mt[i]-mt[i1]);
	 vt2[l].v3d.x=vt1[i].v3d.x+(vt1[i1].v3d.x-vt1[i].v3d.x)*m;
	 vt2[l].v3d.y=vt1[i].v3d.y+(vt1[i1].v3d.y-vt1[i].v3d.y)*m;
	 vt2[l].v3d.z=vt1[i].v3d.z+(vt1[i1].v3d.z-vt1[i].v3d.z)*m;
	 //tu interpolacja niezbednych wartosci
	 vt2[l].tex.tx=vt1[i].tex.tx+(vt1[i1].tex.tx-vt1[i].tex.tx)*m;
	 vt2[l].tex.ty=vt1[i].tex.ty+(vt1[i1].tex.ty-vt1[i].tex.ty)*m;

	 l++;		   //nast pkt
	 };
   };
num=l;		//ilosc pktow po obcieciu
t=vt2;		//zamiana adresow
vt2=vt1;	//dla przejrzystosci algorytmu
vt1=t;


//clipping dla sciany 4
l=0;
for(i=0;i<num;i++)    //liczenie wspolczynnikow
   {
   mt[i]=vt1[i].v3d.x*cam->focus-vt1[i].v3d.z*(-cam->cvalx);
   };

for(i=0;i<num;i++)		//obcinanie
   {
   i1=(i+1)%(num);
   if((mt[i]>0.0)||(mt[i1]>0.0))	//czy ktorys widoczny
     if((mt[i]>0.0)&&(mt[i1]>0.0))	//oba widoczne
       {
       cpyvertex(&vt1[i],&vt2[l]);
       l++;
       } else	//trzeba obciac
	 {
	 if((mt[i]>0.0)&&(mt[i1]<=0.0))
	   {
	   cpyvertex(&vt1[i],&vt2[l]);
	   l++;
	   };
	 m=mt[i]/(mt[i]-mt[i1]);
	 vt2[l].v3d.x=vt1[i].v3d.x+(vt1[i1].v3d.x-vt1[i].v3d.x)*m;
	 vt2[l].v3d.y=vt1[i].v3d.y+(vt1[i1].v3d.y-vt1[i].v3d.y)*m;
	 vt2[l].v3d.z=vt1[i].v3d.z+(vt1[i1].v3d.z-vt1[i].v3d.z)*m;
	 //tu interpolacja niezbednych wartosci
	 vt2[l].tex.tx=vt1[i].tex.tx+(vt1[i1].tex.tx-vt1[i].tex.tx)*m;
	 vt2[l].tex.ty=vt1[i].tex.ty+(vt1[i1].tex.ty-vt1[i].tex.ty)*m;

	 l++;		   //nast pkt
	 };
   };
num=l;		//ilosc pktow po obcieciu
t=vt2;		//zamiana adresow
vt2=vt1;	//dla przejrzystosci algorytmu
vt1=t;


//clipping dla sciany 5
l=0;
for(i=0;i<num;i++)    //liczenie wspolczynnikow
   {
   mt[i]=-(vt1[i].v3d.z*(-cam->cvaly)-vt1[i].v3d.y*cam->focus);
   };

for(i=0;i<num;i++)		//obcinanie
   {
   i1=(i+1)%(num);
   if((mt[i]>0.0)||(mt[i1]>0.0))	//czy ktorys widoczny
     if((mt[i]>0.0)&&(mt[i1]>0.0))	//oba widoczne
       {
       cpyvertex(&vt1[i],&vt2[l]);
       l++;
       } else	//trzeba obciac
	 {
	 if((mt[i]>0.0)&&(mt[i1]<=0.0))
	   {
	   cpyvertex(&vt1[i],&vt2[l]);
	   l++;
	   };
	 m=mt[i]/(mt[i]-mt[i1]);
	 vt2[l].v3d.x=vt1[i].v3d.x+(vt1[i1].v3d.x-vt1[i].v3d.x)*m;
	 vt2[l].v3d.y=vt1[i].v3d.y+(vt1[i1].v3d.y-vt1[i].v3d.y)*m;
	 vt2[l].v3d.z=vt1[i].v3d.z+(vt1[i1].v3d.z-vt1[i].v3d.z)*m;
	 //tu interpolacja niezbednych wartosci
	 vt2[l].tex.tx=vt1[i].tex.tx+(vt1[i1].tex.tx-vt1[i].tex.tx)*m;
	 vt2[l].tex.ty=vt1[i].tex.ty+(vt1[i1].tex.ty-vt1[i].tex.ty)*m;

	 l++;		   //nast pkt
	 };
   };
num=l;		//ilosc pktow po obcieciu
t=vt2;		//zamiana adresow
vt2=vt1;	//dla przejrzystosci algorytmu
vt1=t;


//clipping dla sciany 6
l=0;
for(i=0;i<num;i++)    //liczenie wspolczynnikow
   {
   mt[i]=-(vt1[i].v3d.z*cam->cvaly-vt1[i].v3d.y*cam->focus);
   };

for(i=0;i<num;i++)		//obcinanie
   {
   i1=(i+1)%(num);
   if((mt[i]<0.0)||(mt[i1]<0.0))	//czy ktorys widoczny
     if((mt[i]<0.0)&&(mt[i1]<0.0))	//oba widoczne
       {
       cpyvertex(&vt1[i],&vt2[l]);
       l++;
       } else	//trzeba obciac
	 {
	 if((mt[i]<0.0)&&(mt[i1]>=0.0))
	   {
	   cpyvertex(&vt1[i],&vt2[l]);
	   l++;
	   };
	 m=mt[i]/(mt[i]-mt[i1]);
	 vt2[l].v3d.x=vt1[i].v3d.x+(vt1[i1].v3d.x-vt1[i].v3d.x)*m;
	 vt2[l].v3d.y=vt1[i].v3d.y+(vt1[i1].v3d.y-vt1[i].v3d.y)*m;
	 vt2[l].v3d.z=vt1[i].v3d.z+(vt1[i1].v3d.z-vt1[i].v3d.z)*m;
	 //tu interpolacja niezbednych wartosci
	 vt2[l].tex.tx=vt1[i].tex.tx+(vt1[i1].tex.tx-vt1[i].tex.tx)*m;
	 vt2[l].tex.ty=vt1[i].tex.ty+(vt1[i1].tex.ty-vt1[i].tex.ty)*m;

	 l++;		   //nast pkt
	 };
   };
num=l;		//ilosc pktow po obcieciu
t=vt2;		//zamiana adresow
vt2=vt1;	//dla przejrzystosci algorytmu
vt1=t;


return num;	//zwraca liczbe pktow po obcieciu
};