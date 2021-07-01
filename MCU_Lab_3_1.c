#include <reg51.h>
unsigned int T0count = 0;

void Timer0_Init()		//62.5us@11.0592MHz
{
	TMOD = 0x02;
	TL0 = 0xc6;
	TH0 = 0xc6;
	EA = 1; //开总中断开关
	ET0 = 1;
	TR0 = 1;
}

void Timer0_Routine() interrupt 1
{
	if(T0count == 4)	//1:8K  2:4K  3:2K  4:1K
	{
		P2_0 =! P2_0;
		T0count++;
	}
    else{
        T0count++;
    }
}

void main()
{
	Timer0_Init();
    while(1);
}
