
#include <reg51.h>
#include <stdio.h>

sbit myPIN = P1^3;


int main(void){

    if(RST){
        myPIN = 0;
    }
    else{
        myPIN = 1;
    }


    return 0;
}


