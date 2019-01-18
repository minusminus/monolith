#ifndef bsort_H
 #define bsort_H

//=========================================================================
#define PI 3.14159265359

//including sorting procedure
extern "C"{
extern void BSORT(fptr *tbl1,fptr *tbl2,unsigned long fnum);
#pragma aux BSORT parm [esi] [edi] [ecx] modify exact []
};



//=========================================================================
#endif
