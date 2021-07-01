#include <reg51.h>
#include <stdio.h>

void main(void)
{
   int x, y;
   SCON = 0x52;
   TMOD = 0x20;
   TH1 = 0xf3;
   TR1 = 1;
   printf("input:");
   scanf("%d %d", &x, &y);
   printf("\n%d+%d=%d", x, y, x+y);
   printf("\n%xH+%xH=%XH", x, y, x+y);
   while(1);
}
