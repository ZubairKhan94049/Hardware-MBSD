#include <reg51.h>
#include <stdio.h>

sbit LED = P1 ^ 1;
sbit BTN = P1 ^ 2;
int main()
{
    while (1)
    {
        if (BTN == 0)
            LED = 1;
        else
            LED = 0;
    }
    return 0;
}