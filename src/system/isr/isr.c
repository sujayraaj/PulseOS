#include "isr.h"
#include "idt.h"
#include "textmode.h"


unsigned char *exception_messages[] =
{
(unsigned char *)	"Division By Zero",
(unsigned char *) 	"Debug",
(unsigned char *) 	"Non Maskable Interrupt",
(unsigned char *) 	"Breakpoint Exception",
(unsigned char *) 	"Into Detected Overflow Exception",
(unsigned char *) 	"Out of Bounds Exception",
(unsigned char *) 	"Invalid Opcode Exception",
(unsigned char *) 	"No Coprocessor Exception",
(unsigned char *) 	"Double Fault Exception",
(unsigned char *) 	"Coprocessor Segment Overrun Exception",
(unsigned char *) 	"Bad TSS Exception",
(unsigned char *) 	"Segment Not Present Exception",
(unsigned char *) 	"Stack Fault Exception",
(unsigned char *) 	"General Protection Fault Exception",
(unsigned char *) 	"Page Fault Exception",
(unsigned char *) 	"Unknown Interrupt Exception",
(unsigned char *) 	"Coprocessor Fault Exception",
(unsigned char *) 	"Alignment Check Exception (486+)",
(unsigned char *) 	"Machine Check Exception (Pentium/586+)",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved",
(unsigned char *) 	"Reserved"
};



void isr_install()
{

idt_set_gate(0,(unsigned)isr0,0x08,0x8E);
idt_set_gate(1,(unsigned)isr1,0x08,0x8E);
idt_set_gate(2,(unsigned)isr2,0x08,0x8E);
idt_set_gate(3,(unsigned)isr3,0x08,0x8E);
idt_set_gate(4,(unsigned)isr4,0x08,0x8E);
idt_set_gate(5,(unsigned)isr5,0x08,0x8E);
idt_set_gate(6,(unsigned)isr6,0x08,0x8E);
idt_set_gate(7,(unsigned)isr7,0x08,0x8E);
idt_set_gate(8,(unsigned)isr8,0x08,0x8E);
idt_set_gate(9,(unsigned)isr9,0x08,0x8E);
idt_set_gate(10,(unsigned)isr10,0x08,0x8E);
idt_set_gate(11,(unsigned)isr11,0x08,0x8E);
idt_set_gate(12,(unsigned)isr12,0x08,0x8E);
idt_set_gate(13,(unsigned)isr13,0x08,0x8E);
//idt_set_gate(14,(unsigned)isr14,0x08,0x8E);
idt_set_gate(15,(unsigned)isr15,0x08,0x8E);
idt_set_gate(16,(unsigned)isr16,0x08,0x8E);
idt_set_gate(17,(unsigned)isr17,0x08,0x8E);
idt_set_gate(18,(unsigned)isr18,0x08,0x8E);
idt_set_gate(19,(unsigned)isr19,0x08,0x8E);
idt_set_gate(20,(unsigned)isr20,0x08,0x8E);
idt_set_gate(21,(unsigned)isr21,0x08,0x8E);
idt_set_gate(22,(unsigned)isr22,0x08,0x8E);
idt_set_gate(23,(unsigned)isr23,0x08,0x8E);
idt_set_gate(24,(unsigned)isr24,0x08,0x8E);
idt_set_gate(25,(unsigned)isr25,0x08,0x8E);
idt_set_gate(26,(unsigned)isr26,0x08,0x8E);
idt_set_gate(27,(unsigned)isr27,0x08,0x8E);
idt_set_gate(28,(unsigned)isr28,0x08,0x8E);
idt_set_gate(29,(unsigned)isr29,0x08,0x8E);
idt_set_gate(30,(unsigned)isr30,0x08,0x8E);
idt_set_gate(31,(unsigned)isr31,0x08,0x8E);

}



void fault_handler(struct regs *r)
{
    /* Is this a fault whose number is from 0 to 31? */
    if (r->int_no < 32)
    {
        /* Display the description for the Exception that occurred.
        *  In this tutorial, we will simply halt the system using an
        *  infinite loop */
        terminal_writestring((const char*)exception_messages[r->int_no]);
        terminal_writestring(" Exception. System Halted!\n");
        for (;;);
    }
}
