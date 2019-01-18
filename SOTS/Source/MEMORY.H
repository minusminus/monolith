#ifdef __cplusplus
  extern "C"{
#endif


union valun
{
long l;
float f;
};


extern void MEMCOPY(void *src,void *dest,unsigned long num);
#pragma aux MEMCOPY parm [esi] [edi] [ecx] modify exact []


extern void MEMFILL(void *dest,union valun v,unsigned long num);
#pragma aux MEMFILL parm [edi] [eax] [ecx] modify exact []




#ifdef __cplusplus
  };
#endif
