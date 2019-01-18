//testowe rysowanie punktow


void points(Face *tr,unsigned char *buf)
{
Vertex *p1, *p2, *p3;
long y,x;

p1=tr->p1;
p2=tr->p2;
p3=tr->p3;


if(((p1->v3d.z)>0.0)&&
   ((p1->x2d)>0.0)&&((p1->x2d)<320.0)&&
   ((p1->y2d)>0.0)&&((p1->y2d)<200.0))
   {
   x=(long)(p1->x2d);
   y=(long)(p1->y2d);
   buf[y*320+x]=15;
   numpoints++;
   };
/*
if((p2->v3d.z>0)&&
   (p2->x2d>0)&&(p2->x2d<320)&&
   (p2->y2d>0)&&(p2->y2d<200))
   {
   x=(long)(p2->x2d);
   y=(long)(p2->y2d);
   buf[y*320+x]=15;
   numpoints++;
   };
if((p3->v3d.z>0)&&
   (p3->x2d>0)&&(p3->x2d<320)&&
   (p3->y2d>0)&&(p3->y2d<200))
   {
   x=(long)(p3->x2d);
   y=(long)(p3->y2d);
   buf[y*320+x]=15;
   numpoints++;
   };
*/
};