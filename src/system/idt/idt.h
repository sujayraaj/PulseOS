#ifndef IDT_H_
#define IDT_H_

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        
    unsigned char always0;     
    unsigned char flags;       
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();

extern void idt_load();

#endif
