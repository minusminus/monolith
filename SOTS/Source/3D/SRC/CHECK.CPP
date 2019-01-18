//sprawdzenie sceny
void check(Face *f,Vertex *p1,Vertex *p2,Vertex *p3)
{
int dz12,dz23,dz13,dzx;

/*
dz12=f->dz12;
dz23=f->dz23;
dz13=f->dz13;
dzx=f->dzx;
printf("wsp 1: %5.5f %5.5f,2: %5.5f %5.5f,3: %5.5f %5.5f\n",p1->x2d,p1->y2d,p2->x2d,p2->y2d,p3->x2d,p3->y2d);
printf("z   1: %5.5f,2: %5.5f,3: %5.5f\n",p1->v3d.z,p2->v3d.z,p3->v3d.z);
printf("1/z 1: %5.5f,2: %5.5f,3: %5.5f\n",65536.0/p1->v3d.z,65536.0/p2->v3d.z,65536.0/p3->v3d.z);
printf("dz  12: %8x,23: %8x,13: %8x,x: %8x \n",dz12,dz23,dz13,dzx);
printf("-----------------------------------------------------------\n");
*/


if(p1->x2d<-0.4) numx++;
if(p1->x2d>319.4) numx++;
if(p1->y2d<-0.4) numy++;
if(p1->y2d>199.4) numy++;
if(p2->x2d<-0.4) numx++;
if(p2->x2d>319.4) numx++;
if(p2->y2d<-0.4) numy++;
if(p2->y2d>199.4) numy++;
if(p3->x2d<-0.4) numx++;
if(p3->x2d>319.4) numx++;
if(p3->y2d<-0.4) numy++;
if(p3->y2d>199.4) numy++;



};


void keycheck(void)
{

while(!kbhit());
int k=getch();
//if(k==27) koniec=1;
if(k==27) { setmode(0x03);
	    exit(0);
	    };

};