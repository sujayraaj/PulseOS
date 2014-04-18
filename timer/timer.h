
#include "io.h"
#include "irq.h"
#include "textmode.h"

void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       
    outb(0x43, 0x36);             
    outb(0x40, divisor & 0xFF);   
    outb(0x40, divisor >> 8);     
}

uint32_t timer_ticks = 0;
uint32_t timer_seconds = 0;

void timer_handler(struct regs *r)
{
    timer_ticks++;
    if (timer_ticks % 18 == 0)
    {
	++timer_seconds;
    }


}


void timer_install()
{
    irq_install_handler(0, timer_handler);
}
