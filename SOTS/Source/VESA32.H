#ifndef _vesa32_h_included_
#define _vesa32_h_included_

#ifdef __cplusplus
extern "C"{
#endif

#define VESA_BANKS     1
#define VESA_DOUBLE    2
#define VESA_RMODE     4
#define VESA_SET_LINE  8
#define VESA_DPIXEL    16

#pragma pack(1)
       typedef struct vesa_info_s{
         char signature[4];
         unsigned short int version;
         char *OEM_name;
         long flags;
         void *modes;
         unsigned short int memory;         // in 64kb blocks
         short oem_version;
         char *vendor_name;
         char *product_name;
         char *revision_string;
         char reserved[222];
         char trash[256];
       }vesa_info_s;
#pragma pack ()
long vesa_get_memory(vesa_info_s*);
#pragma aux vesa_get_memory parm [eax] value [eax] modify exact [eax];

extern long int vesa_bytespp;
extern long vesa_error;
extern long vesa_buffer_size;
extern unsigned char vesa_bpp;
extern unsigned long int vesa_screen_x;
extern unsigned long int vesa_screen_y;
extern void *vesa_screen_addy;
extern long *vesa_screen_buffer;
extern volatile long vesa_buffer_flag;

char* vesa_get_error_message();
#pragma aux vesa_get_error_message parm [] value [eax] modify exact [];

void vesa_set_buffer(long);
#pragma aux vesa_set_buffer parm [eax] modify exact [];

void vesa_show_buffer(long);
#pragma aux vesa_show_buffer parm [eax] modify exact [];

void vesa_free(void);
#pragma aux vesa_free parm [] modify exact [];

void vesa_show_screen(void);
#pragma aux vesa_show_screen parm [] modify exact [];

int vesa_mode_info(char*,int);
/*
 wejscie : adres 256-bajtowego bufora,numer trybu vesa
 wyjscie : eax = 0 - BLAD
                 1 - OK
*/
#pragma aux vesa_mode_info parm [eax] [ecx] modify exact [eax] value [eax];

int vesa_info(vesa_info_s*);
#pragma aux vesa_info parm [eax] modify exact [eax] value [eax]

int vesa_set_mode(int,int);
/*
 wejscie : numer trybu vesa, wlaczyc lfb ?
 wyjscie : eax = 0 - BLAD
                 1 - OK
*/
#pragma aux vesa_set_mode parm [ebx] [edx] modify exact [eax];

void vesa_dos_mode(void);
#pragma aux vesa_dos_mode parm [] modify exact [];

long vesa_get_mode(long,long,long);
#pragma aux vesa_get_mode parm [eax] [ebx] [ecx] value [eax] modify exact [eax];

#ifdef __cplusplus
};
#endif

#endif
