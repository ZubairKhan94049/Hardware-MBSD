#include <reg51.h>
#include <stdio.h>

sbit pin = P3 ^ 0;

void Start_timer0(void)
{
    TR0 = 1;
}

void timer0(void) interrupt 1
{
    TH0 = 0xD8;
    TL0 = 0xEF;
}

void Init_timer0(void)
{
    TMOD = 0x01;
    TH0 = 0xD8;
    TL0 = 0xEF;
    IE = 0x82;
}

void main(void)
{
    Init_timer0();
    Start_timer0();
    while (1)
    {
        while (TF0 == 0)
        {
            pin = ~pin;
        }
    }
}