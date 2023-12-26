#### MSP430 Clock 
its hearth of synchronous digital systems and processors.

CPU's require clocks to run to ensure the orderly fetching and execution of instructions. 

one of the most obvious effects of clocks is the speed at which the cpu is processing data. if clock is slow, algo will take longer to complete. 

* LFXT1CLK – Low frequency mode of the XT1 oscillator, typically used with watch crystals
or clocks of 32.768kHz. 
* HFXT1 – High frequency mode of the XT1 oscillator, used with High Frequency crystals.
Not available in all MSP430 (not present in G2553 device)
* VLOCLK – Internal low frequency and low accuracy oscillator for low power
* DCOCLK – Internal Digitally Controlled Oscillator capable of generating a wide array of
frequencies.
* XT2CLK – Optional high-frequency oscillator that uses standard crystals, resonators or
external clocks in the 400kHz to 16MHz range or more.
* PxIN – If the pin is set to operate as GPIO Input, this pin indicates whether the voltage
at the pin is High(0) or Low(0) 



### Source
* https://embeddedtechnosolutions.com/wp-content/uploads/2016/11/MSP430-Tutorial.pdf // page 57
