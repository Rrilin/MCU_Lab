#include <reg51.h>
#include <intrins.h>
unsigned int count = 0;

void Delayms(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;
	while(xms)
	{
			_nop_();
			_nop_();
			_nop_();
			i = 11;
			j = 190;
			do
			{
				while (--j);
			} while (--i);
			xms--;
	}
}

int cod[6]={
			0xdf, // 1101 1111
			0xef, // 1110 1111
			0xf7, // 1111 0111
			0xfb, // 1111 1011
			0xfd, // 1111 1101
			0xfe  // 1111 1110
};
						
void Int0Init()
{
	IT0 = 1; 
	EX0 = 1; 
	EA = 1; 
}
						
void Int0() interrupt 0
{
	Delayms(200);
	if(count == 6){
		count = 0;
	}
	P2 = cod[count];
	count++;
}
						
void main()
{
	Int0Init();
	P0 = 0x80;
	while(1);
}
