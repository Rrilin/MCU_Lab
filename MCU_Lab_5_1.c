//主机程序
#include <reg51.h>
#include <stdio.h>

void UART_Init(){
   SCON = 0xC0;    // 1100 0000 方式3 波特率可变9位异步通信 REN=0禁止接收
}

void Timer1_Init(){ //波特率为2400
    TMOD = 0x20; // 0010 0000  方式2 8位自动重装
    TL1 = 0xF4;    // 设定定时初值
    TH1 = 0xF4;    // 设定定时器重装值
    TR1 = 1;
}

void main(void){
    unsigned char i;
    UART_Init();
    Timer1_Init();
    while (1){
        i = P1;    // 读取目标地址
        i = i&0x0F;    // 取P1低四位
        TB8 = 1;    // 地址信息TB8置1
        SBUF = i;    // 发送地址
        while(TI == 0); // 等待一帧信息发送完
        TI = 0; // 重设状态为0
        P2 = P1;
        i = P1; // 取P1
        TB8 = 0; // 数据信息置0
        SBUF = i; // 发送数据
        while(TI == 0);
        TI = 0;
   }
}



//从机程序
#include <reg51.h>
#include <stdio.h>

void UART_Init(){
   SCON = 0xF0;    // 1111 0000  方式3 所有从机SM2 = 1接收地址 REN=1允许接收
}

void Timer1_Init(){ //波特率为2400
    TMOD = 0x20; // 0010 0000  方式2 8位自动重装
    TL1 = 0xF4;    //设定定时初值
    TH1 = 0xF4;    //设定定时器重装值
    TR1 = 1;
}

void main(void){
    unsigned char i, j, k;
    UART_Init();
    Timer1_Init();
    while (1){
        i = P1&0x0F; //低四位本机地址
        while(RI == 0);
        RI = 0;
        j = SBUF; // 接收目标地址
        if(j == i) // 若目标地址与本机地址相同
        {
            SM2 = 0; // 接收数据信息
            while(RI == 0);
            RI = 0;
            k = SBUF; // 读取数据信息
            P2 = k; // 用LED显示数据
        }
        else{
            P2 = j | 0xF0;
        }
    }
}
