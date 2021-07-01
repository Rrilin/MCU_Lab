#include <reg51.h>

void Delaylms(unsigned int xms) {
    unsigned char i, j;
    while(xms){
        i = 2;
        j = 239;
        do{
            while(--j);
        } while(--i);
        xms--;
    }
}
//hgfedcba
int hello[5]={0x89,    //    H
            0x86,    //    E
            0xc7,    //    L
            0xc7,    //    L
            0xc0,    //    O
};

int cod[6] = {
            0xDF, //1101 1111
            0xEF, //1110 1111
            0xF7, //1111 0111
            0xFB, //1111 1011
            0xFD, //1111 1101
            0xFE}; //1111 1110

void main(){
    int i;
    while(1){
        for(i=0; i<30; i++){
            P2 = cod[i%6];
            P0 = hello[i%5];
            Delaylms(200);
            P0 = 0xFF;
        }
    }
}
