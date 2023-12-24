#include <msp430.h> 


int main(void)
{


}





void LedFadedEffectWithTimer()
{
    P1DIR |= BIT6;
    P1OUT &= ~(BIT6);
    P1SEL |= BIT6;

    TACCR0 = 10000;
    TACCR1 = 0;
    TACCTL1 |= OUTMOD_7;
    TACTL |= TASSEL_2 + MC_1;

    int pwm = 0, l = 100;

    while(1)
    {
        __delay_cycles(5000);
        pwm += l;

        if(pwm == 10000) l = -100;
        if(pwm == 0) l = 100;

        TACCR1 = pwm;

    }

}
void LedFadedEffectWithoutTimer()
{
    int i,j,k,l; //Declare the needed variables
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    P1DIR|=BIT0; //Set P1.0 as output
    j=10;k=1000;l=8; //Initialise the variables
    while(1) //Run the code forever
    {
        P1OUT|=BIT0; //Turn on the LED
        for(i=0;i<j;i++); //Let the LED be on for j number of cycles
        P1OUT&=~BIT0; //Turn off the LED
        for(i=j;i<k;i++); //Let the LED be off for k-j number of cycles
        j+=l; //Change j
        if(j>990){l*=-1;} //If the LED is reaching maximum brightness, start decreaing j
        if(j<10){l*=-1;} //If the LED is reaching minimum brightness, start increasing j
    }

}
