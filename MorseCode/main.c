#include <msp430.h> 
#include <stdio.h>


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	printf("sex");

	while(1)
	{
	}

	return 0;
}
