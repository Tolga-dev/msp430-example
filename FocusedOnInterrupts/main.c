#include <msp430.h>
// check interrupt.md

#define RED BIT6
#define GREEN BIT0
#define SW BIT0

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer




}


void TimerLoopBlinkOnRed(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer

    P1DIR |= RED;                       // Set RED pin -> Output
    P1OUT &=~ RED;                      // Turn OFF RED

    TACCR0 = 5000;                      // Set Timer Timeout Value
    TACCTL0 |= CCIE;                    // Enable Overflow Interrupt
    TACTL |= MC_1 + TASSEL_1 + TACLR ;  // Set Mode -> Up Count, Clock -> ACLK, Clear Timer


    __bis_SR_register(LPM3_bits + GIE); // Goto LPM3 (Only ACLK active), Enable CPU Interrupt
}

#pragma vector = TIMER0_A0_VECTOR       // CCR0 Interrupt Vector
__interrupt void CCR0_ISR(void)
{
    P1OUT ^= RED;                       // Toggle RED
}



void PortVector()
{
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

