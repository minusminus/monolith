//keys preprocessing


void preprocesskeys(Scene *sc)
{
Object *o;
int i,j;
float d1,d2;

for(j=0;j<sc->obnum;j++)
{
o=sc->obtbl[j];
//przygotwanie quaterionow do interpolacji
for(i=0;i<o->rottrnum-1;i++)
   {
   float diff=o->rottr[i+1].angle-o->rottr[i].angle;
   if(fabs(diff)<(2.0*M_PI))
     {
     o->rottr[i].extraspin=0;
     } else
       {
       o->rottr[i].extraspin=(int)(diff/(2.0*M_PI));
       };
     };

for(i=0;i<o->rottrnum-1;i++)
   {
   d1=qt_dotunit(&o->rottr[i].q,&o->rottr[i+1].q);
   if(d1<0.0)
     {
     o->rottr[i+1].q.x=-o->rottr[i+1].q.x;
     o->rottr[i+1].q.y=-o->rottr[i+1].q.y;
     o->rottr[i+1].q.z=-o->rottr[i+1].q.z;
     o->rottr[i+1].q.w=-o->rottr[i+1].q.w;
     };
   };

for(i=0;i<o->rottrnum;i++)
   {
   if(o->rottr[i].q.w<-1.0) o->rottr[i].q.w=-1.0;
   if(o->rottr[i].q.w>1.0) o->rottr[i].q.w=1.0;
   };


};



};