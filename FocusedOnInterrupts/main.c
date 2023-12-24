// check interrupts.md

#include <msp430.h> 

#define SW BIT3



int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= GREEN;
    P1DIR &= ~SW;
    P1REN |= SW;
    P1OUT |= SW;

    P1IES &= ~SW;
    P1IE |= SW;

    __bis_SR_register(LPM4_bits + GIE); // status register -> enable power optimization

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1()
{
    P1OUT ^= GREEN;
    P1IFG &= ~SW;
}
