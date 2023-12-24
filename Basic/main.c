#include <msp430.h> 
#include <stdio.h>

#define DELAY 2000
#define LONG_DELAY 2000


int main(void) {


    return 0;
}


void TogglingLedWithTimerMode()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

       P1DIR |= BIT0;

       TACTL |= TASSEL_2+MC_2+TAIE;

      __low_power_mode_0();

}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TMR0()
{
    if(TAIV==TA0IV_TAIFG)   //Check if Timer overflow caused the interrupt
                            //This would be required in projects where multiple interrupts have
                            //the same interrupt vector. Here it is only optional.
        {
            P1OUT^=BIT0; //Toggle the LED
            TACTL&=~(TAIFG); //Reset the interrupt flag
        }
}



void UsingPISR()
{


    WDTCTL = WDTPW | WDTHOLD;

    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1OUT |= BIT3;

    P1IE|=BIT3;
    P1IE |= BIT3;

    __enable_interrupt();

    P1DIR|=BIT0; //Set P1.0 as output
    P1OUT&=~BIT0; //Initially turn off the LED


    __low_power_mode_0(); //Go to low power mode 0

}

#pragma vector=PORT1_VECTOR
__interrupt void P1_Function()
{
    int i; //Declare counter variable
    P1OUT^=BIT0; //Toggle the LED
    i=0; //Start a counter variable
    while(i<500) //Wait till the switch is not pressed continusouly for 500 loop cycles
    {
        if((P1IN&BIT3))
            i++;  //If the switch is not pressed, increment the counter variable
        else
            i=0; //If the switch is pressed, reset the counter variable
    }
    P1IFG&=~BIT3; // Reset interrupt flag

}


void ButtonWithDebouncing()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
       P1DIR&=~BIT3; //Set P1.3 as input
       P1REN|=BIT3; //Enable pullup/pulldown resistors for P1.3
       P1OUT|=BIT3; //Set P1.3 to have pull up resistors

       P1DIR|=BIT0; //Set P1.0 as output
       P1OUT&=~BIT0; //Initially turn off the LED

       while(1)
       {
           if((P1IN&BIT3)==0) //If the switch is pressed
           {

            P1OUT^=BIT0; //Toggle the LED
             __delay_cycles(LONG_DELAY ); //Wait for switch to be unpressed
           }

       }
}

void Button()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

       P1DIR &= ~BIT3; //Set P1.3 as input
       P1REN |= BIT3; //Enable pullup/pulldown resistors for P1.3
       P1OUT |= BIT3; //Set P1.3 to have pull up resistors

       P1DIR |=BIT0; //Set P1.0 as output

       while(1) //Run the below code forever
       {
           if((P1IN&BIT3)==(BIT3)) //If P1.3 is logical HIGH
               P1OUT&=~BIT0; //Turn off the LED
           else
               P1OUT|=BIT0; //Else, turn on the LED
       }
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




