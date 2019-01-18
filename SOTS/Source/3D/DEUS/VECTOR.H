#ifndef VECTOR_H
 #define VECTOR_H

//=========================================================================

//defining vector class
class Vector
{
public:
      float x,y,z;

      friend void normalize(Vector *v,float n);
};

//dla wspolrzednych textury
class TexVec
{
public:
      float tx,ty;
};

//prototypes for vector class
Vector operator +(Vector v1,Vector v2);
Vector operator -(Vector v1,Vector v2);



//including code for vector class
//#include "vector.cpp"

//=========================================================================
#endif
