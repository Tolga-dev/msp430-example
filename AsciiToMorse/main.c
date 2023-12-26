#include <msp430.h> 
#include <string.h>

#define TIMEUNIT 100000

typedef struct
{
    char *morse;
    char *ascii;
}morse_table_set;

morse_table_set table[] =
{
    { ".-", "A" },
    { "-...", "B" },
    { "-.-.", "C" },
    { "-..", "D" },
    { ".", "E" },
    { "..-.", "F" },
    { "--.", "G" },
    { "....", "H" },
    { "..", "I" },
    { ".---", "J" },
    { "-.-", "K" },
    { ".-..", "L" },
    { "--", "M" },
    { "-.", "N" },
    { "---", "O" },
    { ".--.", "P" },
    { "--.-", "Q" },
    { ".-.", "R" },
    { "...", "S" },
    { "-", "T" },
    { "..-", "U" },
    { "...-", "V" },
    { ".--", "W" },
    { "-..-", "X" },
    { "-.--", "y" },
    { "--..", "Z" }
};

char* toMorse(char Ascii)
{
   int i =0;
    for (i = 0; i <= 26; i++)
    {
        if (Ascii == *(table[i].ascii))
            return table[i].morse;
    }

}


int main(void)
{


	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALBC1_1MHZ;

	P1DIR = BIT0 | BIT6;
	P1OUT &= ~BIT0;
	P1OUT &= ~BIT6;

	char* str = "aaa aaa";
	int i,j;
	int lenght = strlen(str);


	while(1)
	{


	    for(i = 0; i < lenght; i++)
        {
            if (str[i] == ' ')
                __delay_cycles(7 * TIMEUNIT);
            else
            {
                char * result = toMorse(toupper(str[i]));


                for(j = 0; j < strlen(result); j++)
                {
                    if (result[j] == '.')
                    {
                        P1OUT ^= BIT0;
                        __delay_cycles(TIMEUNIT);
                        P1OUT ^= BIT0;
                        __delay_cycles(TIMEUNIT);
                    }
                    else
                    {
                        P1OUT ^= BIT6;
                        __delay_cycles(3 * TIMEUNIT);
                        P1OUT ^= BIT6;
                        __delay_cycles(TIMEUNIT);
                    }

                }
                __delay_cycles(3 * TIMEUNIT);
            }

	    }


	}


}
