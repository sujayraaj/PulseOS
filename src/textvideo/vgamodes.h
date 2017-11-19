#ifndef _VGAMODES__H_
#define _VGAMODES__H_

#include<stddef.h>
#include<stdint.h>
#include "io.h"

#define sgn(x) ((x<0)?-1:((x>0)?1:0)) 
inline int abs(int x)
{
if(x>=0)
return x;
else
return -x;
}

#define VGA_AC_INDEX            0x3C0
#define VGA_AC_WRITE            0x3C0
#define VGA_AC_READ             0x3C1
#define VGA_MISC_WRITE          0x3C2
#define VGA_SEQ_INDEX           0x3C4
#define VGA_SEQ_DATA            0x3C5
#define VGA_DAC_READ_INDEX	0x3C7
#define VGA_DAC_WRITE_INDEX     0x3C8
#define VGA_DAC_DATA            0x3C9
#define VGA_MISC_READ           0x3CC
#define VGA_GC_INDEX            0x3CE
#define VGA_GC_DATA             0x3CF

/*                      COLOR emulation         MONO emulation */
#define VGA_CRTC_INDEX          0x3D4           /* 0x3B4 */
#define VGA_CRTC_DATA           0x3D5           /* 0x3B5 */
#define VGA_INSTAT_READ         0x3DA

#define VGA_NUM_SEQ_REGS        5
#define VGA_NUM_CRTC_REGS	25
#define VGA_NUM_GC_REGS         9
#define VGA_NUM_AC_REGS         21
#define VGA_NUM_REGS            (1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
                                VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)
static unsigned g_wd, g_ht;


uint8_t* vga_buffer;

inline void put_pixel(uint8_t x,uint8_t y,uint8_t col)
{
int off = (y<<8)+(y<<6)+x;
*(vga_buffer+off)=col;
}
void write_regs(unsigned char *regs);
void line(int x1, int y1, int x2, int y2, uint8_t color);
void rect(int left,int top, int right, int bottom, uint8_t color);
void rect_fill(int left,int top, int right, int bottom, uint8_t color);
void set_palette(uint8_t *palette);
static void demo_graphics(void);
#endif
