//=========================================================================
//ustawia rozmiar bufora do renderingu
//we:
//scx,scy - rozmar ekranu w pikselach
//bfx,bfy - rozmiar bufora w pixelach
//px,py - przesuniecie ekranu w buforze [dodawane do przesuniecia
//	  perspektywy] wzgledem srodka ekranu
//rozmiar ekranu musi byc <= rozmiar bufora
//przesuniecia musza by odpowiednio dobrane do rozmiaru bufora
void Scene::setresolution(float scx,float scy,
			  float bfx,float bfy,
			  float px, float py)
{
this->scrX=scx;
this->scrY=scy;
this->bufx=bfx;
this->bufy=bfy;
this->perspx=px;
this->perspy=py;
};

//=========================================================================
//wybiera odpowiednia kamere
void setcamera(Scene *sc)
{
unsigned long cn;

//     cn=sc->activecam;
     if(sc->activecam>=sc->camnum)
       {
       cn=0;
       } else
	 {
	 cn=sc->activecam;
	 };
     sc->cam=sc->camtbl[cn];

};




//=========================================================================
//tworzy macierz wlasna dla obiektu
void makeobmat(Object *o)
{
float x2,y2,z2,wx,wy,wz,xx,xy,xz,yy,yz,zz;

  x2=o->rot.x+o->rot.x; 		//liczenie obrotu z kwateriona
  y2=o->rot.y+o->rot.y;
  z2=o->rot.z+o->rot.z;
  wx=o->rot.w*x2; wy=o->rot.w*y2; wz=o->rot.w*z2;
  xx=o->rot.x*x2; xy=o->rot.x*y2; xz=o->rot.x*z2;
  yy=o->rot.y*y2; yz=o->rot.y*z2; zz=o->rot.z*z2;
  o->obmat.m[0][0]=1.0-(yy+zz); 		  //tworzenie macierzy
  o->obmat.m[1][0]=(xy-wz);			    //obrotu
  o->obmat.m[2][0]=xz+wy;
  o->obmat.m[0][1]=xy+wz;
  o->obmat.m[1][1]=(1.0-(xx+zz));
  o->obmat.m[2][1]=yz-wx;
  o->obmat.m[0][2]=xz-wy;
  o->obmat.m[1][2]=(yz+wx);
  o->obmat.m[2][2]=1.0-(xx+yy);

  if(o->scaletrnum>0)			//skalowanie jesli jest
  {
    o->obmat.m[0][0]*=o->scale.x;
    o->obmat.m[0][1]*=o->scale.x;
    o->obmat.m[0][2]*=o->scale.x;
    o->obmat.m[1][0]*=o->scale.y;
    o->obmat.m[1][1]*=o->scale.y;
    o->obmat.m[1][2]*=o->scale.y;
    o->obmat.m[2][0]*=o->scale.z;
    o->obmat.m[2][1]*=o->scale.z;
    o->obmat.m[2][2]*=o->scale.z;
  };
};








//=========================================================================
//tworzy macierz wlasna dla obiektu
void makeobeyemat(Object *o,Camera *cam)
{
// policz macierz i wektor obiektu
 if(o->fatherob==NULL)
 {
//   o->backeyemat=cam->mat*o->obmat;
   o->eyemat=o->obmat*cam->mat;
   o->transl=o->pos*cam->mat;
   o->transl=o->transl+cam->campos;
 } else
   {
//    o->backeyemat=o->fatherob->eyemat*o->obmat;
    o->eyemat=o->obmat*o->fatherob->eyemat;
    o->transl=o->pos*o->fatherob->obmat;
    o->transl=o->transl+o->fatherob->transl;
   };

};







//========================================================================
//liczy macierz kamery
void makecammat(Camera *cam,long ScreenX,long ScreenY)
{
Vector pos,tar,n;
float ax,ay,az;
float sinx,cosx,siny,cosy,sinz,cosz;
Object *o;
float focus,tanfov,tanfov2;
float scaleX,scaleY,_1_scaleX,_1_scaleY;


cam->aspectratio=(float)(ScreenY)/(float)(ScreenX);

// policz wektory kamery
 pos=cam->pos;
 for(o=cam->fatherob;o;o=o->fatherob)
 {
   n=pos*(o->obmat);
   n=n+o->pos;
//   pos.x=n.x;pos.y=n.y;pos.z=n.z;
   pos=n;
 };

 tar=cam->trg;
 for(o=cam->fatherob2;o;o=o->fatherob)
 {
   n=tar*(o->obmat);
   n=n+o->pos;
//   tar.x=n.x;tar.y=n.y;tar.z=n.z;
   tar=n;
 };


// policz macierz kamery
// tar.x-=pos.x;tar.y-=pos.y;tar.z-=pos.z;
 tar=tar-pos;
 cam->trg=tar;
 focus=sqrt((tar.x*tar.x)+(tar.y*tar.y)+(tar.z*tar.z));
 tanfov=tan((cam->FOV/2.0));

scaleX=(ScreenX/2.0)/(1.0*tanfov);
scaleY=(ScreenY/2.0)/(cam->aspectratio*1.0*tanfov);

// _1_scaleX=1.0/scaleX;
// _1_scaleY=1.0/scaleY;

 cam->scaleX=scaleX;
 cam->scaleY=scaleY;
/* cam->focus=10.0;
 cam->cvalx=10.0*tanfov;
 cam->cvaly=cam->aspectratio*10.0*tanfov;*/
 cam->focus=cam->zmin;
 cam->cvalx=cam->zmin*tanfov;
 cam->cvaly=cam->aspectratio*cam->zmin*tanfov;

 ax=-atan2(tar.x,tar.z);
 ay=asin(tar.y/focus);
 az=-cam->roll;

 sinx=sin(ax); cosx=cos(ax); siny=sin(ay);
 cosy=cos(ay); sinz=sin(az); cosz=cos(az);

 cam->mat.m[0][0]=sinx*siny*sinz+cosx*cosz;
 cam->mat.m[1][0]=cosy*sinz;
 cam->mat.m[2][0]=sinx*cosz-cosx*siny*sinz;
 cam->mat.m[0][1]=-(sinx*siny*cosz-cosx*sinz);
 cam->mat.m[1][1]=-(cosy*cosz);
 cam->mat.m[2][1]=-(-cosx*siny*cosz-sinx*sinz);
 cam->mat.m[0][2]=(-sinx*cosy);
 cam->mat.m[1][2]=(siny);
 cam->mat.m[2][2]=(cosx*cosy);

 cam->campos=cam->pos;
 cam->campos.x*=-1.0;
 cam->campos.y*=-1.0;
 cam->campos.z*=-1.0;
 cam->campos=cam->campos*cam->mat;
/* cam->trg.x*=-1.0;
 cam->trg.y*=-1.0;
 cam->trg.z*=-1.0;
 cam->trg=cam->trg*cam->mat;
 cam->pos.x*=-1.0;
 cam->pos.y*=-1.0;
 cam->pos.z*=-1.0;
 cam->pos=cam->pos*cam->mat;*/

};



//========================================================================
//perspektywa dla danego punktu
void vertpersp(Vertex *v,float korx,float kory,float scx,float scy)
{
float m;
float x,y;

    m=1.0/(v->v3d.z);
    x=((scx*v->v3d.x)*m)+korx;
    y=((scy*v->v3d.y)*m)+kory;
    if(x<0.0) x=0.0;
    if(x>319.0) x=319.0;
    if(y<0.0) y=0.0;
    if(y>199.0) y=199.0;
    v->x2d=x;
    v->y2d=floor(y);

/*
    m=256.0/(v->v3d.z+1000.0);
    v->x2d=(m*v->v3d.x)+korx;
    v->y2d=(m*v->v3d.y)+kory;
*/
    v->flags|=VPERSP;

};


//========================================================================
//liczy perspektywe dla punktow trojkata
void perspective(Face *tr,float korx,float kory,float scx,float scy)
{
unsigned long flags;

   if((tr->p1->flags&VPERSP)==0)
     vertpersp(tr->p1,korx,kory,scx,scy);
   if((tr->p2->flags&VPERSP)==0)
     vertpersp(tr->p2,korx,kory,scx,scy);
   if((tr->p3->flags&VPERSP)==0)
     vertpersp(tr->p3,korx,kory,scx,scy);

};

//perspektywa dla tablicy pktow
void perspective2(Vertex *tv,long vnum,float korx,float kory,
		  float scx,float scy)
{
long i;

for(i=0;i<vnum;i++)
   vertpersp(&tv[i],korx,kory,scx,scy);

};


//========================================================================
//renderuje scene
void render(Scene *sc,unsigned long *buf,unsigned long *zbuf,float frm)
{
unsigned long i,j;
Object *o;
Face *f;
Face f2;
long vcnum;
Vertex vvt1[10];
Vertex vvt2[10];
long numf;
float px,py;	//dla perspektywy

//inicjalizacja procedur
INITTRRENDER(zbuf,buf,(long)(sc->bufx));



//************************************************************************
//LICZENIE MACIERZY

//ustawia odpowiednia kamere
setcamera(sc);


//interpolacja sciezek
setframe(sc,frm);	 //tymczasowo zerowa klatka

//liczy macierze wszystkich obiektow [wlasne macierze]
for(i=0;i<sc->obnum;i++)
   {
    o=sc->obtbl[i];
    makeobmat(o);
   };



//liczy macierz kamery
//makecammat(sc->cam,160,100);
//makecammat(sc->cam,320,200);
makecammat(sc->cam,sc->scrX,sc->scrY);
//transmat(&sc->cam->mat);


//liczy macierze w hierarchii dla obiektow
for(i=0;i<sc->obnum;i++)
   {
    o=sc->obtbl[i];
    makeobeyemat(o,sc->cam);
   };



//************************************************************************
//TRANSFORMACJE I OBCINANIE NIEWIDOCZNYCH TROJKATOW

//przeksztalcenie obiektow i wrzucenie trojkatow widocznych do tablicy
numo=0;
sc->facestodraw=0;
for(i=0;i<sc->obnum;i++)
   {
    o=sc->obtbl[i];
    sc->facestodraw=processobject(o,sc->drawtbl,sc->facestodraw,sc->cam);
   };
//printf("klatka %f, w buforze : %d\n",frm,sc->facestodraw);



//************************************************************************
//RYSOWANIE WIDOCZNYCH TROJKATOW
if(sc->facestodraw>0)
{
sc->cam->zmin=sc->zmin;

//przesuniecie dla perspektywy
px=(sc->bufx/2)+sc->perspx;
py=(sc->bufy/2)+sc->perspy;


//sortowanie face'ow
BSORT(sc->drawtbl,sc->drawtbl2,sc->facestodraw);


//numf=numx=numy=numz=0.0;
//rysowanie trojkatow II
for(i=0;i<sc->facestodraw;i++)
   {
   f=sc->drawtbl[i];
   //obcinanie face'ow w 3d
   vcnum=clip3d(f,sc->cam,&vvt1[0],&vvt2[0]);

   if(vcnum>=3)
   {
   numf++;
   //przeksztalcenie perspektywiczne do 2d
//   perspective2(&vvt2[0],vcnum,160.0,100.0,sc->cam->scaleX,sc->cam->scaleY);
   perspective2(&vvt2[0],vcnum,px,py,sc->cam->scaleX,sc->cam->scaleY);

   //rysowanie
   cpyface(f,&f2);
   f2.p1=&vvt2[0];
   for(j=1;j<vcnum-1;j++)
      {
      f2.p2=&vvt2[j];
      f2.p3=&vvt2[j+1];
//	check(&f2,&numx,&numy,&numz);
//	points(&f2,buf);
//	printf("%d,%d\n",i,j);
//	printf("vvvvvvvvvvvvvvvvvvv\n\n");
//if(fdbg>(int)(numf)) drawtriangle(&f2,buf);
//	drawtriangle(&f2,buf);

//rysowanie face'a
DRAWTR(&f2);		 //TRENG v2.0

      };
//   printf("%d\n",i);
//   keycheck();
   };
   };
//printf("frame : %f,x : %d,y : %d,z : %d,faces : %d\n",frm,numx,numy,numz,numf);
//keycheck();
//fdbg++;
};
//************************************************************************



};
