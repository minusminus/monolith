#ifdef __cplusplus
  extern "C"{
#endif



extern void initflat(void *zbuf,void *buf);
#pragma aux initflat parm [esi] [edi] modify exact []


extern void flat(Face *f);
#pragma aux flat parm [esi] modify exact []




#ifdef __cplusplus
  };
#endif
