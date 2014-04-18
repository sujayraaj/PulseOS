#include"keyboard.h"
#include"irq.h"
#include"io.h"
void keyboard_handler(struct regs *r)
{
        r=0; r++;
    unsigned char scancode;

    scancode = inb(0x60);
    if (scancode & 0x80)
    {
    }
 else
    {
    }
}

void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}

int wait_for_key(char a)
{
unsigned char   scancode =0;

while(kbdus[scancode]!= a)
{
scancode =  inb(0x60);
}
return 1;
}

