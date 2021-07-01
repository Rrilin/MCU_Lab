// Date: 2021.04.06
// Exp4
// Purpose: frequency detector
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar i, bt;
uint counter, num;
uchar dark = 0xff;
uchar pos[6] = {0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
uchar dot = 0x7f;
uchar letter[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void Delayms(unsigned int xms){        //@11.0592MHz
    unsigned char i, j;
    while(xms){
            _nop_();
            _nop_();
            _nop_();
            i = 11;
            j = 190;
            do{
                while (--j);
            } while (--i);
            xms--;
    }
}

void show(uint num){
    bt = 2;
    i = 5;
    while(1){
        P1 = dark;
        P0 = pos[i];
        if(i == bt){
            P1 = letter[num % 10] & dot;
        }else{
            P1 = letter[num % 10];
        }
        num /= 10;
        if(i == 0 || num == 0) break;
        else i--;
    }
}

void Timer0_Init(){ // 1s
    TMOD = 0x01;
    TH0 = 0xdb;
    TL0 = 0xe9;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void Timer0_Routine() interrupt 1{
    TH0 = 0xdb;
    TL0 = 0xe9;
    show(counter * 100);
    counter = 0;
    Delayms(20);
}

void Int0Init(){
    IT0 = 1;
    EX0 = 1;
    EA = 1;
}

void Int0() interrupt 0{
    counter++;
}

void main(){
    counter = 0;
    Timer0_Init();
    Int0Init();
    while(1);
}

