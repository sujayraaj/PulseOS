#include"utility.h"
#include"textmode.h"

unsigned int page_fault(struct regs* r){
uint32_t faultaddr;
__asm__ __volatile__("mov %%cr2, %0" : "=r" (faultaddr));
int exist  = !(r->err_code & 0x1); // Page not present
int rw = r->err_code & 0x2;           // Write operation?
int us = r->err_code & 0x4;           // Processor was in user-mode?
int reserved = r->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
int id = r->err_code & 0x10;          // Caused by an instruction fetch?
terminal_writestring("\nPage Fault Exception at ");
terminal_putint(faultaddr);
for(;;){}
}
