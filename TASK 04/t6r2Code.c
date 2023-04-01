#include <reg51.h>
#include <stdio.h>

sbit pin = P1 ^ 0;
int x = 0;

void Start_timer0(void)
{
    TR1 = 1;
}

void timer1(void) interrupt 1
{
    x++;
    if (x == 4)
    {
        pin = ~pin;
        x = 0;
    }
    TH0 = 0x3C;
    TL0 = 0xAF;
}

void Init_timer0(void)
{
    TMOD = 0x01;
    TH0 = 0x3C;
    TL0 = 0xAF;
    IE = 0x88;
}

void main(void)
{
    Init_timer0();
    Start_timer0();
    while (1)
    {
    }
}