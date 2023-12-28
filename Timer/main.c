#include <msp430.h>

#define IN BIT4  // Button connected to P1.3
#define LED BIT6     // Green LED connected to P1.6
#define LED2 BIT0     // Green LED connected to P1.6
#define BUZZER  BIT7

unsigned long buttonPressedTime = 0;
int morsePos = 0;  // Morse code buffer position
int dotTime = 250; // Time in milliseconds for a dot
int dashTime = 500; // Time in milliseconds for a dash
int resetTime = 1000; // Time in milliseconds to reset
int OFCount = 0;
volatile int indexCounter = 0;
int check = 0;



const char *morseAlphabet[] = {
        ".-",   // A
        "-...", // B
        "-.-.", // C
        "-..",  // D
        ".",    // E
        "..-.", // F
        "--.",  // G
        "....", // H
        "..",   // I
        ".---", // J
        "-.-",  // K
        ".-..", // L
        "--",   // M
        "-.",   // N
        "---",  // O
        ".--.", // P
        "--.-", // Q
        ".-.",  // R
        "...",  // S
        "-",    // T
        "..-",  // U
        "...-", // V
        ".--",  // W
        "-..-", // X
        "-.--", // Y
        "--.."  // Z
};

void buzzerOn() {
    P1OUT |= BUZZER;
}

void buzzerOff() {
    P1OUT &= ~BUZZER;
}


int findMorseIndex(char *morse) {
    volatile int index = -1; // Default index if not found
    volatile int i = 0;
    for (i = 0; i < sizeof(morseAlphabet) / sizeof(morseAlphabet[0]); i++) {
        if (strcmp(morseAlphabet[i], morse) == 0) {
            index = i; // Set the index if the Morse code is found
            break;
        }
    }

    return index;
}


void delayForOn(unsigned int n)
{
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        __delay_cycles(1000); // 1ms delay at 1MHz clock speed
        if ((P1IN & IN ) != 0) break;
    }
}
void delayForOff(unsigned int n)
{
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        __delay_cycles(1000); // 1ms delay at 1MHz clock speed
        if((P1IN & IN ) == 0)
            break;
    }
}

void main(void)
{
    volatile int indexCounter = 0;
    char adder;
    volatile char morseCode[6]; // Morse code buffer to store dots and dashes

    WDTCTL = WDTPW | WDTHOLD; // Watchdog Timer'ı durdur

    P1DIR |= BIT0;  // P1.0'i bir çıkış olarak ayarla (Kırmızı LED için)
    P1DIR |= BIT6;  // P1.6'yı bir çıkış olarak ayarla (Yeşil LED için)


    P1DIR &= ~IN; // P1.3'ü bir giriş olarak ayarla (Düğme için)
    P1REN |= IN ;  // P1.3 için pull-up/pull-down direncini etkinleştir

    P1DIR |= BUZZER;
    P1OUT &= ~BUZZER; // Buzzer'ı başlangıçta kapalı tut


    while (1)
    {
        if ((P1IN & IN ) == 0)
        {
            // Düğme basılıysa
            P1OUT |= BIT0; // Yeşil LED'i aç
            buzzerOn();

            adder = '.';

            delayForOn(250); // 0.25 saniye gecikme

            if ((P1IN & IN ) == 0)
            {
                // Düğme hala basılıysa (0.25 saniye boyunca basıldı)
                P1OUT &= ~BIT0; // Yeşil LED'i kapat
                P1OUT |= BIT6; // Kırmızı LED'i aç
                adder = '-';
                while((P1IN & IN ) == 0);
            }
            buzzerOff();

            morseCode[indexCounter] = adder;
            indexCounter++;

        }
        else if(morseCode[0] != '\0')
        {

            // Düğme basılı değilse
            P1OUT &= ~BIT0; // Kırmızı LED'i kapat
            P1OUT &= ~BIT6; // Yeşil LED'i kapat


            delayForOff(1000);    // 1 saniye bekle

            if ((P1IN & IN ) != 0)
            {

                morseCode[indexCounter] = '\0';

                if(findMorseIndex(morseCode) != -1)
                {
                    P1OUT |= BIT0; // Kırmızı LED'i aç
                    delayForOff(1000);
                    P1OUT &= ~BIT0; // Yeşil LED'i kapat

                }
                else
                {

                     P1OUT |= BIT6; // Kırmızı LED'i aç
                     delayForOff(1000);
                     P1OUT &= ~BIT6; // Yeşil LED'i kapat
                }

                indexCounter = 0;

                memset(morseCode, '\0', sizeof(morseCode));

            }

        }
    }
}

