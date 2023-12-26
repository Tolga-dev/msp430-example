### MSP430 Timer

16 bit timers, Timer A and Timer B.

Timer Clock = 1MHz (SMCLK=1MHz), 1000 ticks will equal to 1ms

MSP430 Timer Registers
* TAR – Timer Counter Register: Holds the current count for Timer_A.

* TACCRx – Timer Capture/Compare Register: In Compare mode, it holds compare value to be compared against TAR. In Capture mode, it holds the current value of TAR when a capture is performed. Maximum value it can store is 0xFFFF since its a 16 bit register.

* TACTL – Control Register: Used to configure Timer_A. This register is divided as follows:

Bit[0] – TAIFG – Timer_A Interrupt Flag. 0 = No interrupt pending, 1 = Interrupt pending.
Bit[1] – TAIE – Timer_A Interrupt Enable. 0 = Interrupt Disabled, 1 = Interrupt Enabled.
Bit[2] – TACLR – Timer_A clear. Setting this bit resets TAR, clock divider, and the count direction. It is automatically reset and is always read as zero.
Bits[5:4] – MCx – Mode Control bits. Used to select between 4 different modes as given:
[00] = MC_0 – Stop mode: Timer is halted.
[01] = MC_1 – Up mode: Timer counts up to TACCR0.
[10] = MC_2 – Continuous mode: Timer counts up to 0xFFFF.
[11] = MC_3 – Up/down mode: Timer counts up to TACCR0 then down to 0x0000.
Bit[7:6] – IDx – Input divider. Selects input clock divider.
[00] = ID_0 – /1
[01] = ID_1 – /2
[10] = ID_2 – /4
[11] = ID_3 – /8
Bits[9:8] TASSELx – Timer_A clock source select.
[00] = TASSEL_0 – TACLK
[01] = TASSEL_1 – ACLK
[10] = TASSEL_2 – SMCLK
[11] = TASSEL_3 – INCLK (check datasheet)
Other Bits – Reserved
* TACCTLx – Capture/Compare Control Register: Used to configure capture/compare options. I will only cover the parts of this register which are applicable to this tutorial. We will see it in detail in other tutorials(for Capture mode & PWM).

Bit[0] – CCIFG – Capture/compare interrupt flag: 0 = interrupt pending, 1 = Interrupt pending.
Bit[4] – CCIE – Capture/compare interrupt enable: This bit enables the interrupt request of the corresponding CCIFG flag. 0 = Interrupt disabled = 1 Interrupt enabled.
Bit[8] – CAP – Capture mode: Used to select between Compare and Capture mode. We will this bit in its default setting i.e. = 0. 0 = Compare mode, 1 = Capture mode.

* TAIV – Interrupt Vector Register: Used to identify the flag which requested an interrupt. This is a read only register and only uses 3 bits [3:1] called TAIVx. The values for TAIVx which corresponds to various sources is as given below:

0x00 = No Interrupt Pending.
0x02 = Capture/Compare 1 – TACCR1 CCIFG.
0x04 = Capture/Compare 2 – TACCR2 CCIFG.
0x0A = Timer(TAR) Overflow – TAIFG.
Other – Reserved.



#### sources
* http://www.ocfreaks.com/msp430-timer-programming-tutorial/
