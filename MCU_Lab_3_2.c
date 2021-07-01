#include <reg51.h>
unsigned char T0count = 0;
unsigned char orgn = 0;
sbit ch_0 = P2 ^ 0;
sbit ch_1 = P2 ^ 1;
sbit ch_2 = P2 ^ 2;
sbit ch_3 = P2 ^ 3;

void Timer0_Init(){
    TMOD = 0x01;
    TH0 = (65536 - 512) / 256;
    TL0 = (65536 - 112) % 256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void Timer0_Routin() interrupt 1{
    T0count++;
    TH0 = (65536 - 512) / 256;
    TL0 = (65536 - 512) % 256;
}

void main(void){
    P1 = 0x00;
    Timer0_Init();
    while (1){
        if(orgn != T0count){
            if (T0count % 6 == 0){
                ch_0 = ~ch_0;
            }
            if (T0count % 10 == 0){
                ch_1 = ~ch_1;
            }
            if (T0count % 15 == 0){
                ch_2 = ~ch_2;
            }
            if (T0count % 90 == 0){
                T0count = 0;
            }
            orgn = T0count;
        }
    }
}


