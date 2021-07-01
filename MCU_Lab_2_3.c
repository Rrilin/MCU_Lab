#include <reg51.h>
#include <intrins.h>

void Delayms(unsigned int xms){		//@11.0592MHz
	unsigned char i, j;
	while(xms){
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

int hello[5]={
            0x89,    //    H
            0x86,    //    E
            0xc7,    //    L
            0xc7,    //    L
            0xc0};    //    O

int cod[6]={
            0xdf, // 1101 1111
            0xef, // 1110 1111
            0xf7, // 1111 0111
            0xfb, // 1111 1011
            0xfd, // 1111 1101
            0xfe};  // 1111 1110
						
void Int0Init(){
	IT0 = 1; 
	EX0 = 1; 
	EA = 1; 
}

unsigned int i = 1;
						
void Int0() interrupt 0{
	Delayms(200);
	if(i == 30){
		i = 0;
	}
	P2 = cod[i%6];
	P0 = hello[i%5];
	i++;
}	
												
void main(){
	Int0Init();
	P0 = 0x89;
	while(1);
}
