#include <reg51.h>
#include <stdio.h>

#define UPPER 0xD8
#define LOWER 0xEF

void Section_A(); // Generate a signal on pin P1.1 having frequency equal to 10 Hz with a duty cycle of 10%.
void Section_B(); // When a user presses a button at P1.2 then frequency changes to 20Hz with a 20% duty cycle.
void Section_C(); // When a user again presses the same button then frequency changes to 40Hz with a duty cycle of 40 %.
void Section_D(); // When a user again presses the same button then frequency changes to 80Hz with a duty cycle of 80 %.

// Delay Function
void Delay(int H_VALUE, int L_VALUE);

// Defining ports
sbit PIN_01_LED = P1 ^ 1; // By Default
sbit PIN_02_BTN = P1 ^ 2; // For Button

unsigned int btn_count = 0;
int l = 0;
void main(void)
{
    while (1)
    {
        if (PIN_02_BTN == 0) // Button is pressed
        {
            btn_count++;
        }

        //////////////////////
        if (btn_count == 0)
            Section_A();
        else if (btn_count == 1)
            Section_B();
        else if (btn_count == 2)
            Seciont_C();
        else if (btn_count == 3)
            Section_D();
        else
            ;
        //////////////////////

        if (btn_count >= 3) // Logic that Reset (Start from A again)
            btn_count = 0;
    }
}

void Section_A()
{
    PIN_01_LED = 1;
    Delay(UPPER, LOWER); // Generating Upper time Delay
    PIN_01_LED = 0;
    Delay(0x50, 0x37);
    Delay(0x50, 0x37);
}

void Section_B()
{
    PIN_01_LED = 1;
    Delay(UPPER, LOWER); // Generating Upper time Delay
    PIN_01_LED = 0;
    Delay(0x63, 0xBF);
}

void Section_C()
{
    PIN_01_LED = 1;
    Delay(UPPER, LOWER); // Generating Upper time Delay
    PIN_01_LED = 0;
    Delay(0xC5, 0x67);
}

void Section_D()
{
    PIN_01_LED = 1;
    Delay(UPPER, LOWER); // Generating Upper time Delay
    PIN_01_LED = 0;
    Delay(0xF6, 0x3B);
}

void Delay(int H_VALUE, int L_VALUE)
{
    TMOD = 0x01;
    TR0 = 1;
    TL0 = L_VALUE;
    TH0 = H_VALUE;
    while (TF0 == 0)
        ;
    TF0 = 0;
    TR0 = 0;
}
