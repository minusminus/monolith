//=========================================================================
//dla quaterionow
void qt_copy (quat *a, quat *out)
{
  out->w = a->w;out->x = a->x;out->y = a->y;out->z = a->z;
}


//=========================================================================
float qt_dotunit (quat *a, quat *b)
{
  return (a->w*b->w + a->x*b->x + a->y*b->y + a->z*b->z);
}


//=========================================================================
void qt_slerpl (quat *a, quat *b, float t, quat *out)
{
  quat temp;
  float  k1, k2;
  float  angle, anglespin;
  float  sina, cosa,flip;


cosa=qt_dotunit(a,b);
if(cosa<-1.0) { cosa=-1.0; } else
	      { if(cosa>1.0) cosa=1.0; };

angle=acos(cosa);
sina=sin(angle);
if(sina<EPSILON)
{
qt_copy(a,out);
} else
  {
  sina = 1.0/sina;
  k1 = sin((1.0-t)*angle)*sina;
  k2 = sin(t*angle)*sina;
  temp.x=a->x*k1+b->x*k2;
  temp.y=a->y*k1+b->y*k2;
  temp.z=a->z*k1+b->z*k2;
  temp.w=a->w*k1+b->w*k2;
  qt_copy(&temp,out);
  };

};

//=========================================================================
void qt_slerplextraspin (quat *a, quat *b, float t, quat *out,int extraspin)
{
  quat temp;
  float  k1, k2;
  float  angle, anglespin;
  float  sina, cosa,flip,phase;


cosa=qt_dotunit(a,b);
if(cosa<-1.0) { cosa=-1.0; } else
	      { if(cosa>1.0) cosa=1.0; };

angle=acos(cosa);
sina=sin(angle);
if(sina<EPSILON)
{
qt_copy(a,out);
} else
  {
  phase=M_PI*extraspin*t;
  sina = 1.0/sina;
  k1 = sin((1.0-t)*angle-phase)*sina;
  k2 = sin(t*angle+phase)*sina;
  temp.x=a->x*k1+b->x*k2;
  temp.y=a->y*k1+b->y*k2;
  temp.z=a->z*k1+b->z*k2;
  temp.w=a->w*k1+b->w*k2;
  qt_copy(&temp,out);
  };

};



