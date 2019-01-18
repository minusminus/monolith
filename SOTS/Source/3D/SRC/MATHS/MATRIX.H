#ifndef MATRIX_H
#define MATRIX_H

//=========================================================================

//including vector class
#include "vector.h"


//defining matrix class
class Matrix
{
public:
      float m[3][3];

      friend void fidentmatrix(Matrix *mat);
      friend void transmat(Matrix *mat);
};

//prototypes for matrix class
Matrix operator *(Matrix mat1,Matrix mat2);
Vector operator *(Vector v,Matrix mat);



//including code for matrix class
#include "matrix.cpp"


//=========================================================================
#endif
