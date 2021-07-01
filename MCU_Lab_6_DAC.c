#include <absacc.h> // 定义绝对地址访问
#include <reg51.h>
#define uchar unsigned char
#define DAC0832 XBYTE[0x7FFF] // 输入寄存器地址 最高位为0 接片选CS
// 由于将DAC0832看作外部数据存储器，且仅有一片，故定其片外数据存储器地址线为最高位

uchar code sindata[64] =
   {0x80, 0x8c, 0x98, 0xa5, 0xb0, 0xbc, 0xc7, 0xd1,
    0xda, 0xe2, 0xea, 0xf0, 0xf6, 0xfa, 0xfd, 0xff,
    0xff, 0xff, 0xfd, 0xfa, 0xf6, 0xf0, 0xea, 0xe3,
    0xda, 0xd1, 0xc7, 0xbc, 0xb1, 0xa5, 0x99, 0x8c,
    0x80, 0x73, 0x67, 0x5b, 0x4f, 0x43, 0x39, 0x2e,
    0x25, 0x1d, 0x15, 0xf, 0x9, 0x5, 0x2 ,0x0, 0x0,
    0x0, 0x2, 0x5, 0x9, 0xe, 0x15, 0x1c, 0x25, 0x2e,
    0x38, 0x43, 0x4e, 0x5a, 0x66, 0x73};
    
uchar phase[8] = {0, 16, 0, 48, 16, 48, 0, 32};
int phase_num;
int sin_num = 1;
uchar T0count = 0; // 控制sin数组移动时间间隔，从而控制频率
uchar fixnum;

void Timer0_Init(){ // 定时器0中断控制频率 10ms/64
    TMOD = 0x02;
    TH0 = 0x70;
    TL0 = 0x70; //  (65536 - 156) % 256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void Timer0_Int() interrupt 1{
    sin_num++;
    T0count++;
}

void main(){
    Timer0_Init();
    phase_num = 0;
    sin_num = 0;
    while(1){
        if(phase_num >= 8){ // 4 种相位循环
            phase_num = 0;
        }
        if(sin_num == 640){ //  每 10 个周期切换相位
            T0count = phase[phase_num];
            phase_num++;
            sin_num = 1;
        }
        DAC0832 = sindata[T0count % 64];
    }
}
