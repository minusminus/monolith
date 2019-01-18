#ifndef VECTOR_CPP
 #define VECTOR_CPP
//=========================================================================


void normalize(Vector *v,float n)
{
float l;

    l=n/sqrt(v->x*v->x+v->y*v->y+v->z*v->z);
    v->x*=l;
    v->y*=l;
    v->z*=l;
};



Vector operator +(Vector v1,Vector v2)
{
Vector v;

       v.x=v1.x+v2.x;
       v.y=v1.y+v2.y;
       v.z=v1.z+v2.z;

return v;
};

Vector operator -(Vector v1,Vector v2)
{
Vector v;

       v.x=v1.x-v2.x;
       v.y=v1.y-v2.y;
       v.z=v1.z-v2.z;

return v;
};



//=========================================================================
#endif