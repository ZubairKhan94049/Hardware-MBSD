#include <reg51.h>

#include <stdio.h>

sbit input_pin = P3 ^ 4;

void start_timer(void)
{
    TR0 = 1;
}

void init_timer(void)
{
    TMOD = 0x06;
    TH0 = 0;
    input_pin = 1;
}

void main(void)
{
    init_timer();
    start_timer();
    while (1)
    {
        P1 = TL0;
    }
}