#include <msp430.h> 
#include <stdio.h>

void main() {



    WDTCTL = WDTPW + WDTHOLD;




    P1DIR  = 0x01; // Set P1.0 as output and P1.1 as intput



    while(1)
    {
        if(P1IN) // If push button is pressed *[2]
        {
          P1OUT = 0x01;
        }
        else
        {
            P1OUT = 0x00;
        }

        if(P3IN) // If push button is pressed *[2]
        {
          P1OUT = 0x01;
        }
        else
        {
            P1OUT = 0x00;
        }

    }

}
