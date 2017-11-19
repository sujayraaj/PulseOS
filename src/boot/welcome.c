#include "textmode.h"


void welcome(void){
uint8_t col = color(COLOR_BLACK,COLOR_LIGHT_RED);
terminal_color = col;

terminal_writestring("                             Welcome To ");
col = color(COLOR_BLACK,COLOR_BLUE);
terminal_color = col;
terminal_writestring("PulseOS");
col = color(COLOR_BLACK,COLOR_LIGHT_BLUE);
terminal_color=col;
terminal_writestring(" !\n\n");
terminal_writestring("          __________      .__                  ________    _________\n");
terminal_writestring("          \\______   \\__ __|  |   ______ ____   \\_____  \\  /   _____/\n");
terminal_writestring("           |     ___/  |  \\  |  /  ___// __ \\   /   |   \\ \\_____  \\ \n");
terminal_writestring("           |    |   |  |  /  |__\\___ \\\\  ___/  /    |    \\/        \\\n");
terminal_writestring("           |____|   |____/|____/____  >\\___  > \\_______  /_______  /\n");
terminal_writestring("                                    \\/     \\/          \\/        \\/ v0.1\n");
col = color(COLOR_BLACK,COLOR_LIGHT_GREEN);
terminal_color=col;
terminal_writestring("\n\t\t\t\tSujay Raj  (C)2014\n\t\t\t\tIndian School of Mines, Dhanbad\n\t\t\t\tsujayraaj@gmail.com"); 

}
