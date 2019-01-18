#ifdef __cplusplus
  extern "C"{
#endif


union valun
{
long l;
float f;
};


extern void memcopy(void *src,void *dest,unsigned long num);
#pragma aux memcopy parm [esi] [edi] [ecx] modify exact []


extern void memfill(void *dest,valun v,unsigned long num);
#pragma aux memfill parm [edi] [eax] [ecx] modify exact []




#ifdef __cplusplus
  };
#endif
