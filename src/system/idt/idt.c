#include "idt.h"
#include "utility.h"


void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;
	idt[num].always0 = 0;
	idt[num].sel = sel;
	idt[num].flags = flags;

}

void idt_install()
{

	int sizeidt = sizeof(struct idt_entry);
    idtp.limit =(unsigned short) (sizeidt * 256) - 1;
    idtp.base = (unsigned long)&idt;

    memset((unsigned char*)&idt, 0, sizeidt* 256);
	
	
    idt_load();
}

