#include <msp430.h>				
#include <stdio.h>





void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    Pointer2();

    while(1);
    return 0;

}


void Pointer2()
{
    int a[5] = {1,2,3,4,5};
         int *pA;

         pA = a;
         pA += 3;

         *pA = 0;
}

void Pointers()
{
    int a = 3;
    int *pA;

    pA = &a;
    *pA = 7;


}

void Parameters()
{

    int d = 0;
    int a = 1;
    float b = -255.25;
    char c = 'c';
    d = d + 1;
    while(1);
}

int Function(int s , int s2)
{
    int s4 = s + s2;
    return s;
}

void BitWiseOperations()
{
    unsigned char a = 0x02;
    unsigned char b = 0xFF;
    unsigned char c,d,e,f;

    c = a | b;
    d = a & b;
    e = a ^ b;
    d = ~a;
}

void LoopIfElse()
{
    int a = 5;
        int b = 6;
        if(a > b)
        {
            a  = b;
        }
        else
        {
            b = a;
        }

        switch(a)
        {
        case 1:
            break;
        case 5:
            a = 9;
            break;
        case 6:
            a = 10;
            break;
        default:
            break;

        }
        int i;
        for(i = 0; i < a; i++ )
        {
            b++;
        }

        while(a < 100)
        {
            a++;
        }

        while(1);
}
