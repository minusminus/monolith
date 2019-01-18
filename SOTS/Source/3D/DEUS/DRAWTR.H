#ifdef __cplusplus
  extern "C"{
#endif



extern void INITTRENG(float *fdt);
#pragma aux INITTRENG parm [esi] modify exact []

extern void INITTRRENDER(void *zbuf,void *buf,long scrX);
#pragma aux INITTRRENDER parm [esi] [edi] [edx] modify exact []


extern void DRAWTR(Face *f);
#pragma aux DRAWTR parm [esi] modify exact []




#ifdef __cplusplus
  };
#endif
