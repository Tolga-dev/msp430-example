#include <msp430.h> 

// pxdir = used for setting a pin direction as input or output
// pxin = keeps the values of the input ports
// pxout = used for setting an output pin as 0 or 1
// pxren = used for enabling internal pull up/ pull down
// pxsel = used for selecting the purpose of the port/ pin

// pxdir = setting direction of pun either as input or output
    //output = 1
    // input = 0
    // example:
        // p1dir = 0x01 // p1.0 as output
        // p1dir = 0x02 // p1.1 as output -> 0b0000 0110

// pxin
    // contain input values
    // p2dir = 0x42 -> 2.1 and 2.6 output, others 0 to 7 is input
    // for specific input pin, 2.2, use and with p2in
        // p2in & 0.04
// pout
    // set output pins
    // p2dir = 0x42, p2.1 and p2.6.


void Init();

int main(void)
{



}
void Init()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
}

void BLinkingWIthPort()
{
        Init();

        P1DIR = 0x01; // set 1 as output
        P1OUT = 0x00; // set 0 closed
        P1REN = 0x00; // set 0 cleaning


        while(1) //Run the below code forever
        {
            if((P1IN & 0x10) == 0x10) // if input gets on 4 port, then open other wise make it down
                P1OUT = 0x01;
            else
                P1OUT = 0x00;

        }
}
void SingleBlink()
{
     Init();
    P1DIR |= 0x01;

    while(1)
    {
        P1OUT ^= 0x01;
    }
}
