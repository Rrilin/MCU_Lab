#include <reg51.h>
#define uchar unsigned char
uchar code dispcode[3] = {0xdf, 0xef, 0xf7};
uchar code codevalue[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90}; // 0~9
uchar temp; // 存储ADC0808转换过程中的临时数值
uchar dispbuf[4]; // 存储十进制值
sbit ST = P3^0; // ALE和START共用
sbit OE = P3^1; // 输出允许信号
sbit EOC = P3^2; // 转换结束信号
sbit CLK = P3^7; // Timer0定时10us
sbit CLK1 = P3^5;
uchar count; // LED位控制
uchar getdata; // 转换后的数值

void delay(uchar m){
   while(m--){}
}

void Timer0_Init(){ //  10us
    TMOD = 0x12; // 方式2
    TH0 = 246;
    TL0 = 246; //  (65536 - 10) % 256 = 100;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void Timer0_Int(void) interrupt 1 using 0 { // 周期20us 50kHz
    CLK = ~CLK;
}

void Timer1_Init(){ //  20ms
    TMOD = 0x12; // 方式1
    TH1 = (65536 - 20000) / 256;
    TL1 = (65536 - 20000) % 256;
    EA = 1;
    ET1 = 1;
    TR1 = 1;
}

void Timer1_Int(void) interrupt 3 using 0 { }// 动态刷新显示数码管
    CLK1 = ~CLK1;
    TH1 = (65536 - 20000) / 256;
    TL1 = (65536 - 20000) % 256;
    for(count=0; count<3; count++){ // 位信号
        P2 = dispcode[count];
        P1 = 0xff;
        P1 = codevalue[dispbuf[count]];
        delay(255);
        P1 = 0xff;
        delay(255);
    }
}

void main(){
    Timer0_Init();
    Timer1_Init();
    ST = 0;
    while(1){
        ST = 1; // START信号下降沿，启动转换
        delay(45);
        ST = 0;
        delay(45);
        while(EOC == 0){;} // 等待转换结束8个CLK时钟
        OE = 0; // 将转换结果输出
        getdata = P0;
        OE = 1; // 关闭三态门
        temp = getdata;
        /* 进制转换 */
        dispbuf[2] = getdata/100;
        temp = temp - dispbuf[2]*100;
        dispbuf[1] = temp/10;
        temp = temp - dispbuf[1]*10;
        dispbuf[0] = temp;
        delay(255);
    }
}
