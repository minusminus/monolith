#ifdef __cplusplus
  extern "C"{
#endif



extern void inittex(void *zbuf,void *buf,float *fdt);
#pragma aux inittex parm [esi] [edi] [edx] modify exact []


extern void textr(Face *f);
#pragma aux textr parm [esi] modify exact []




#ifdef __cplusplus
  };
#endif
