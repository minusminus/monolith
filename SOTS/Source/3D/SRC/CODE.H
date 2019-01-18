#ifndef CODE_H
 #define CODE_H

//=========================================================================
#define PI 3.14159265359

//including code for loader
#include "./loader/loader.cpp"

//including code for interpolations
#include "./maths/interp.cpp"

//including code for keyframer
#include "./render/keyfr.cpp"

//including code for object processor
#include "./render/procob.cpp"

//including code for 3d clipper
#include "./render/clip3d.cpp"

//including sorting procedure
extern "C"{
extern void BSORT(fptr *tbl1,fptr *tbl2,unsigned long fnum);
#pragma aux BSORT parm [esi] [edi] [ecx] modify exact []
};



//=========================================================================
#endif
