#ifndef IRQ_H_
#define IRQ_H_
#include"utility.h"


void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void irq_remap(void);
void irq_install();
void irq_handler(struct regs *r);

#endif
