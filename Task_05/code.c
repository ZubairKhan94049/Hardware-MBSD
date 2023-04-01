#include<reg51.h>
#include<stdio.h>

sbit LED = P3^1;
sbit Button_00 = P3^2;
sbit Button_01 = P3^3;
unsigned int looping_controller = 0;

void t() interrupt 3 {
		looping_controller++;
	if(looping_controller == 5000) {
		IE = 0;
		LED = 1;
	}else {
		TH1 = 0xD1;
		TL1 = 0x1F;
	}
}

void Func_B() interrupt 0 {
	P1 = P1 + 1;
}

void Func_A() interrupt 2 {
	P2 = P2 + 1;
}

void strt_timer() {
		TR1 = 1;
}

void main() {
	P3 |= 0x0c;
	LED = 0;
	P1 = 0;
	P2 = 0; 
	IT0 = 1;
	IT1 = 1;
	IE = 0x8D; 
	TMOD = 0x10;	
	TH1 = 0xD1;
	TL1 = 0x1F;
	strt_timer();
	while(1);
}