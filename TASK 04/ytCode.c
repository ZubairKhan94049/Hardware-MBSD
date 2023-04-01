/*
We will blink a LED1 connected to p0.0 at 50ms and in the mean time we would also read the sw connected to p3.2 and display on led2 connected to p0.1
Important thing to understand here is , in the main program the swithc is continuous read and displayed on the LED2 the timer keeps ticking on its own and generates interrupt every 50ms to toggle the LED2 connected to p0.0 is toggled


interrupt 0 = > External Hardware interupts
interrupt 1 = > Timer zero (0) interrupt
*/

#include <reg51.h>
sbit LED1 = P0 ^ 0;
sbit LED2 = P0 ^ 1;
sbit SW = P3 ^ 2;

void timer0_isr() interrupt 1
{
    TH0 = 0x4B;
    TL0 = 0xFD;
    LED1 = !LED1;
}

void main()
{
    TMOD = 0x01;
    TH0 = 0x4B;
    TL0 = 0xFD;
    TR0 = 1;
    SW = 1;
    IE = 0x82;
    while (1)
    {
        LED2 = SW;
    }
}