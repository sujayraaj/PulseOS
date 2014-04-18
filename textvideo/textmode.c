#include"textmode.h"

uint8_t color(enum vga_color bg,enum vga_color fg)
{
return fg | bg<<4;
}

uint16_t vga_entry(char c, uint8_t col)
{
return (uint16_t)c | (uint16_t)col<<8;
}

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}


void terminal_initialize()
{
		terminal_row=0;
		terminal_column=0;
	        terminal_color = color(COLOR_BLACK, COLOR_WHITE);
	        terminal_buffer = (uint16_t*) 0xB8000;
		for ( size_t y = 0; y < VGA_HEIGHT; y++ )
        	{
                	for ( size_t x = 0; x < VGA_WIDTH; x++ )
                	{
                        	const size_t index = y * VGA_WIDTH + x;
                       		terminal_buffer[index] = vga_entry(' ', terminal_color);
                	}
        	}
}

void terminal_setcolor(uint8_t color)
{
        terminal_color = color;
}



void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}


void terminal_putchar(char c)
{	
	if(c=='\n')
	{
	terminal_column=0;
	++terminal_row;
	}
	else if(c=='\t')
	{
	terminal_column= (terminal_column+8) %VGA_WIDTH;
	}
	else if(c=='\b')
	{
	if(terminal_column!=0)
	{
	--terminal_column;
	terminal_putentryat(' ',terminal_color,terminal_column,terminal_row);
	}
	}
	else
	{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	}
	if ( ++terminal_column == VGA_WIDTH || terminal_row == VGA_HEIGHT)
	{	
		if(terminal_column == VGA_WIDTH)
		terminal_column = 0;
		if ( terminal_row == VGA_HEIGHT )
		{
		size_t y,x;
		for (  y = 0; y < VGA_HEIGHT-1; y++ )
                {
                        for (  x = 0; x < VGA_WIDTH; x++ )
                        {
                                const size_t index = y * VGA_WIDTH + x;
                                terminal_buffer[index] = terminal_buffer[index+VGA_WIDTH];
                        }
                }
		for(x=0;x<VGA_WIDTH;x++)
		{
                const size_t index = y * VGA_WIDTH + x;
                                terminal_buffer[index] = vga_entry(' ', terminal_color);
			terminal_row = VGA_HEIGHT-1;
		}
		}
	}
}
 




void clrscr()
{
 for ( size_t y = 0; y < VGA_HEIGHT; y++ )
                {
                        for ( size_t x = 0; x < VGA_WIDTH; x++ )
                        {
                                const size_t index = y * VGA_WIDTH + x;
                                terminal_buffer[index] = vga_entry(' ', terminal_color);
                        }
                }
terminal_row=0;
terminal_column=0;
}

void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}


void terminal_putint(uint32_t i)
{
if(i==0)
terminal_putchar('0');
else{
char c[10];
uint16_t count=0;
while(i!=0)
{
uint16_t j= i%10;
c[count] = (char)48 + (char)j;
i=i/10;
count++;	
}
char ch;
for(i=0;i<count/2;i++)
{
ch=c[i];
c[i]=c[count-1-i];
c[count-1-i]=ch;
}
        for ( i = 0; i < count; i++ )
                terminal_putchar(c[i]);
}
}

