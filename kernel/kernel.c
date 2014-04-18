#include "textmode.h"
#include "vgamodes.h"
#include "io.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "timer.h"
#include "multiboot.h"

extern unsigned char g_320x200x256[];
extern unsigned char g_80x25_text[];
extern uint8_t defaultVgaPalette[];
extern void welcome(void);

void kernel_main(unsigned int magic,multiboot_info_t* mbt)
{
gdt_install();
idt_install();
isr_install();
irq_install();
timer_install();
keyboard_install();
 __asm__ __volatile__ ("sti"); 
unsigned int a[10];
uint32_t count=0,col,it=0;
memory_map_t* mmap = mbt->mmap_addr;
terminal_initialize();
welcome();
col = color(COLOR_BLACK,COLOR_LIGHT_BLUE);
terminal_color=col;
terminal_writestring("\nPlease wait while the memory of the system is being mapped ..");
terminal_putchar('\n');
while(mmap < mbt->mmap_addr + mbt->mmap_length) {
	count++;
	terminal_writestring("\nBlock: ");
	terminal_putint(count);
	terminal_writestring("\nSize ");
	terminal_putint(mmap->size);
	terminal_writestring("\nAddress (High/Low) ");
	terminal_putint(mmap->base_addr_high);
	terminal_putchar(' ');
	terminal_putint(mmap->base_addr_low);
	terminal_writestring("\nLength (High/Low) ");
	terminal_putint(mmap->length_high);
	terminal_putchar(' ');
	terminal_putint(mmap->length_low);
	terminal_writestring("\nType ");
	terminal_putint(mmap->type);
	terminal_putchar('\n');
	if(mmap->type==1){
	 a[it]= (unsigned int) mmap;
	it++;
	}
	mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
	wait_for_key('a');

	}
terminal_writestring("DONE");
wait_for_key('x');
}
