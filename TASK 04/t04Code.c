#include <reg51.h>
#include <stdio.h>

// interrupt 0 = > External Hardware interupts
// interrupt 1 = > Timer zero (0) interrupt

sbit PIN_LED = P2 ^ 0; // Output PIN => attached with Oscilloscope to Observe the output
sbit PIN_BTN = P3 ^ 2; // Input PIN  => Button has been connected with 8051 through this pin

// Just to Display State by pressing button
sbit state_A = P1 ^ 1;
sbit state_B = P1 ^ 2;
sbit state_C = P1 ^ 3;

int btn_counter = 0; // To Control the program/state
int i = 0;           // To Control debouncing => Creating Dealy

void LED_init()
// This is just to show initial state
// If absent State A LED will be off even though program may be in state A
{
    state_A = 1;
    state_B = 0;
    state_C = 0;
}
void Start_tm(void)
{
    TR0 = 1; // starting timer 0
}

void Init_tm(void)
{
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x17;
    IE = 0x83; // Enabling EX_I and T_I (EA = 1, EX0 = 1)
}

void tm_intr(void) interrupt 1
{
    if (btn_counter == 0)
    {
        if (PIN_LED == 0)
        {
            TH0 = 0xFC;
            TL0 = 0x17;
            PIN_LED = !PIN_LED; // PIN_LED = 1;
        }
        else
        {
            TH0 = 0xF4;
            TL0 = 0x47;
            PIN_LED = 0;
        }
    }
    else if (btn_counter == 1)
    {
        TH0 = 0xFC;
        TL0 = 0x17;
        PIN_LED = ~PIN_LED;
    }
    else if (btn_counter == 2)
    {
        if (PIN_LED == 0)
        {
            TH0 = 0xFD;
            TL0 = 0x11;
            PIN_LED = !PIN_LED; // PIN_LED = 1;
        }
        else
        {
            TH0 = 0xFF;
            TL0 = 0x05;
            PIN_LED = 0;
        }
    }
}

void ext_intr(void) interrupt 0
{
    for (i = 0; i < 10000; i++)
        ; // To Control Debouncing
    switch (btn_counter % 3)
    {
    case 0:
        btn_counter = 1;
        break;
    case 1:
        btn_counter = 2;
        break;
    case 2:
        btn_counter = 0;
        break;
    }
    // Controlling BTNs
    switch (btn_counter % 3)
    {
    case 0:
        state_A = 1;
        state_B = 0;
        state_C = 0;
        break;
    case 1:
        state_A = 0;
        state_B = 1;
        state_C = 0;
        break;
    case 2:
        state_A = 0;
        state_B = 0;
        state_C = 1;
        break;
    }
}

void main(void)
{
    P1 = 0;
    LED_init();
    PIN_BTN = 1;
    Start_tm();
    Init_tm();
    while (1)
        ;
}