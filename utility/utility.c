#include"utility.h"

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
unsigned char *beg=dest;
for(int i=0;i<count;i++)
{
*dest = val;
dest++;
}

return (unsigned char*)beg;
}

