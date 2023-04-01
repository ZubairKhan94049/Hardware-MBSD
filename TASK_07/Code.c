
#include <reg51.h>

sbit RD_n = P3 ^ 0; // read pin of ADC connected to pin 3.0
sbit WR_n = P3 ^ 1; // write pin of ADC connected to pin 3.1
sbit INTR = P3 ^ 2; // interpt pin of ADC connected to pin 3.2
sbit RS = P3 ^ 6;   // RS pin of LCD
sbit En = P3 ^ 7;   // enable pin of LC
sbit SPK = P3 ^ 4;  // speaker
sfr ldata = 0xA0;

unsigned char temperature;

// declaraing functions
void delay(unsigned int);    // Function of creating Delays
void writecmd(int);          // Function that sends commands to LCD
void writedata(char);        // Function that writes data to LCD
void convert(unsigned char); // Function that converts the Integer value to char and display it on LCD
void SetTimer(int, int);     // Function that set the TH0 and TL0 values
void Init(void);             // Function that initializes the timer values
void StartTimer(void);       // Fnction that starts Timer 0
void StopTimer(void);        // Function to Stop Timer 0
void Ext0(void);             // Function that is called after the ADC is done with conversion
void lcdinit(void);          // function to give commands to lcd
// defining the functions

void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 125; j++)
            ;
}

void writecmd(int z)
{
    RS = 0;    // This is command
    ldata = z; // Data transfer
    En = 1;    // => E = 1
    delay(150);
    En = 0; // => E = 0
    delay(150);
}

void writedata(char t)
{
    RS = 1;    // This is data
    ldata = t; // Data transfer
    En = 1;    // => E = 1
    delay(150);
    En = 0; // => E = 0
    delay(150);
}

void timer0() interrupt 1
{
    if (SPK) // if the Speaker is ON
    {
        SPK = 0;              // Turn it OFF
        SetTimer(0xFB, 0x1D); // Set Delay to 1.25msec
    }
    else // if the Speaker is OFF
    {
        SPK = 1;              // Turn it ON
        SetTimer(0xF1, 0x59); // Set the delay to 3.75msec
    }
}

void SetTimer(int xx, int yy)
{
    TH0 = xx; // Set the value of TH0 to xx
    TL0 = yy; // Set the value of TL0 to yy
}

void Init()
{
    TMOD = 0x1;           // Timer 0 is Mode 1
    EA = 1;               // Enable Global interrupt
    ET0 = 1;              // Enable timer overflow interrupt for timer 0
    SetTimer(0xF1, 0x59); // Set the values of TH0 and TL0 for a delay of 3.75ms
}

void StartTimer()
{
    TR0 = 1; // Start Timer 0;
}

void StopTimer()
{
    TR0 = 0; // Stop Timer 0
}

void Ext0()
{
    RD_n = 0;                                 // Set the RD pin of ADC from HIGH to LOW    //The ADC sends the converted value to P1
    temperature = P1;                         // Store the value at P1 in temperature
    convert(temperature);                     // Display temperature on LCD
    if (temperature < 10 || temperature > 25) // If the is less than 10 or it is greater than 25
    {
        SPK = 1;      // Turn the speaker ON
        StartTimer(); // Start the Timer
    }
    else // if the temperature is in-between 10 and 25
    {
        if (TR0 == 1) // if the Timer 0 is satarted
        {
            StopTimer();          // stop the timer
            SetTimer(0xF1, 0x59); // Set a delay of 3.75ms
        }
        SPK = 0; // Turn the Speaker OFF
    }
}
void convert(unsigned char value)
{
    writecmd(0xc6);                        // command to set the cursor to 6th position of 2nd line on 16*2 lcd
    writedata(((value / 100) + 48));       // Convert the hundredth place int to char and display on LCD
    writedata((((value / 10) % 10) + 48)); // Convert the tenth place int to char and display on LCD
    writedata(((value % 10) + 48));        // Convert the unit place int to char and display on LCD
    writedata(0xDF);                       // Hex value for displaying the Degree sign
    writedata('C');                        // Write C to LCD
}

void lcdinit(void)
{
    writecmd(0x38); // 2 lines and 5X7 matrix
    writecmd(0x01); // Clear Display Screen
    writecmd(0x06); // Increment Cursor (Shift cursor right)
    writecmd(0x0C); // Display On, Cursor Off
    writecmd(0x82); //
}

// main program

void main()
{
    SPK = 0;   // Turn the Speaker OFF
    P1 = 0xFF; // Set P1 as an input Port
    INTR = 1;  // Set P3.2 as an input pin
    lcdinit();
    writedata('T');
    writedata('e');
    writedata('m');
    writedata('p');
    writedata('e');
    writedata('r');
    writedata('a');
    writedata('t');
    writedata('u');
    writedata('r');
    writedata('e');
    writedata(':');

    Init();
    while (1)
    {
        RD_n = 1; // Set the RD pin to High
        WR_n = 0; // WR = Low
        WR_n = 1; // Low-->High
        while (INTR == 1)
            ;   // Wait for the ADC to Convert the given voltage
        Ext0(); // Call the Ext0 function
    }
}
