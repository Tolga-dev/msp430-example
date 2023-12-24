#include <msp430.h> 


#define BUZZER  BIT1

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;                       // Stop watchdog timer
    P2DIR |= BUZZER;                                // Set Buzzer pin as Output

    P1DIR |= BIT0;
    P1DIR &= ~BIT3;

    P1REN |= BIT3;
    P1OUT |= BIT3;


    while(1)
    {
        if(P1IN & BIT3) // not pressed
        {
            P1OUT &= ~BIT0;
            P2SEL |= BUZZER;
        }
        else
        {
            P1OUT |= BIT0;
            P2SEL &= ~BUZZER;
        }

    }


}
