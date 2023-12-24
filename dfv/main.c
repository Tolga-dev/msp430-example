#include <msp430.h> 
#include <stdio.h>

#define DELAY 2000

void main() {


}


void ChangingFrequencyOfMultipleBlinking()
{
    volatile int i,j;
        WDTCTL = WDTPW | WDTHOLD;

        P1DIR |= BIT0 | BIT6;

        while(1)
        {
            for(j=0; j < 10000; j+=250)
            {
                P1OUT ^= BIT0 | BIT6;
                for(i=j;i>0;i--); //Wait for j number of cycles
            }
            for(j=10000;j>0;j-=250) //j goes from 10000 to 0 in steps of 250
            {
                P1OUT^=BIT0|BIT6; //Toggle the LEDs
                for(i=j;i>0;i--); //Wait for j number of cycles

            }

        }

}

void ChangingFrequencyOfBlinking()
{
    volatile int i,j; //Force the compiler to not optimize the variables i and j
       WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

       P1DIR|=BIT0; //Set P1.0 as output

       while(1)
       {

           for(j=0;j<10000;j+=250) //j goes from 0 to 10000 in steps of 250
               {
               P1OUT^=BIT0; //Toggle the LED
               for(i=j;i>0;i--); //Wait for j number of cycles

           }

       }
}
void MultiBlinkLed()
{
    volatile int i; //Force the compliler to not optimize the variable 'i'

        WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
        P1DIR|= BIT0|BIT6; //Set P1.0 and P1.6 as output pin

        while(1) //Keep toggling the LEDs forever
        {
            P1OUT|=BIT0; //Turn on red LED
            P1OUT&=~BIT6; //Turn off green LED

            for(i=DELAY;i>0;i--); //Delay

            P1OUT|=BIT6; //Turn on green LED
            P1OUT&=~BIT0; //Turn off red LED

            for(i=DELAY;i>0;i--); //Delay
        }
}
void SingleBlinkLed() // toggling on and off with p1.0
{


    volatile int i; // forcing complier do not optimize the v i
    WDTCTL = WDTPW | WDTHOLD;// stop watch dog timer
    P1DIR |=BIT0; // set p1.0 as output


    while(1)
    {
        P1OUT ^= BIT0; // from high to low or from low to high
        for (i = 0; i < DELAY; ++i){}


    }
}





