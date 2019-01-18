#ifndef MATRIX_CPP
 #define MATRIX_CPP
//=========================================================================


Matrix operator *(Matrix mat1,Matrix mat2)
{
Matrix m;

    m.m[0][0]=mat1.m[0][0]*mat2.m[0][0]+
		  mat1.m[0][1]*mat2.m[1][0]+
		  mat1.m[0][2]*mat2.m[2][0];
    m.m[0][1]=mat1.m[0][0]*mat2.m[0][1]+
		  mat1.m[0][1]*mat2.m[1][1]+
		  mat1.m[0][2]*mat2.m[2][1];
    m.m[0][2]=mat1.m[0][0]*mat2.m[0][2]+
		  mat1.m[0][1]*mat2.m[1][2]+
		  mat1.m[0][2]*mat2.m[2][2];
    m.m[1][0]=mat1.m[1][0]*mat2.m[0][0]+
		  mat1.m[1][1]*mat2.m[1][0]+
		  mat1.m[1][2]*mat2.m[2][0];
    m.m[1][1]=mat1.m[1][0]*mat2.m[0][1]+
		  mat1.m[1][1]*mat2.m[1][1]+
		  mat1.m[1][2]*mat2.m[2][1];
    m.m[1][2]=mat1.m[1][0]*mat2.m[0][2]+
		  mat1.m[1][1]*mat2.m[1][2]+
		  mat1.m[1][2]*mat2.m[2][2];
    m.m[2][0]=mat1.m[2][0]*mat2.m[0][0]+
		  mat1.m[2][1]*mat2.m[1][0]+
		  mat1.m[2][2]*mat2.m[2][0];
    m.m[2][1]=mat1.m[2][0]*mat2.m[0][1]+
		  mat1.m[2][1]*mat2.m[1][1]+
		  mat1.m[2][2]*mat2.m[2][1];
    m.m[2][2]=mat1.m[2][0]*mat2.m[0][2]+
		  mat1.m[2][1]*mat2.m[1][2]+
		  mat1.m[2][2]*mat2.m[2][2];

return m;
};


Vector operator *(Vector v,Matrix mat)
{
Vector vv;

       vv.x=mat.m[0][0]*v.x+mat.m[1][0]*v.y+mat.m[2][0]*v.z;
       vv.y=mat.m[0][1]*v.x+mat.m[1][1]*v.y+mat.m[2][1]*v.z;
       vv.z=mat.m[0][2]*v.x+mat.m[1][2]*v.y+mat.m[2][2]*v.z;

return vv;
};



//friend
void fidentmatrix(Matrix* mat)
{

mat->m[0][0]=mat->m[1][1]=mat->m[2][2]=1.0;
mat->m[0][1]=mat->m[0][2]=mat->m[1][0]=mat->m[1][2]=mat->m[2][0]=mat->m[2][1]=0;

};

void transmat(Matrix *mat)
{
int i;
float t;

t=mat->m[0][1];
mat->m[0][1]=mat->m[1][0];
mat->m[1][0]=t;
t=mat->m[0][2];
mat->m[0][2]=mat->m[2][0];
mat->m[2][0]=t;
t=mat->m[1][2];
mat->m[1][2]=mat->m[2][1];
mat->m[2][1]=t;

};



//=========================================================================
#endif
