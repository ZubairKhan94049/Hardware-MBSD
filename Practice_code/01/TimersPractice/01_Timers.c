// This program will generate 2sec of delay 
// 1sec of up and 1 sec of down



#include <reg51.h>
#include <stdio.h>

#define ON 1
#define OFF 0

sbit LED = P1^0;

void Delay();

int main(){
   
    while(1){
        LED = ON;
        Delay();
        LED = OFF;
        Delay();
    }
    return 0;
}

void Delay(){
    TMOD = 0x01;
    TH0 =  0xF8;
    TL0 = 0x2F;
    TR0 = ON;
    while(TF0 == 0);
    TR0 = OFF;
    TF0 = OFF;
}
