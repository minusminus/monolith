#ifdef __cplusplus
  extern "C"{
#endif


/*
odejmuje wartosc od kolorow w buforze
0 - brak zmiany [najjasniejszy - normalny]
255 - ciemno
*/
extern void FADEIN(void *src,unsigned long val,unsigned long len);
#pragma aux FADEIN parm [esi] [ebx] [ecx] modify exact []

/*
dodaje wartosc do koloru
0 - brak zmian [normalny]
255 - bialo
*/
extern void FADEOUT(void *dest,unsigned long val,unsigned long len);
#pragma aux FADEOUT parm [esi] [ebx] [ecx] modify exact []


/*
wrzuca bufor src transparentnie do dest
*/
extern void TRANSPUT(void *src,void *dest,unsigned long len);
#pragma aux TRANSPUT parm [esi] [edi] [ecx] modify exact []




#ifdef __cplusplus
  };
#endif
