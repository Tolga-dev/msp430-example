### MSP430 Interrupts

it means reaction to something in i/o (human)

usually asynchronous to processor activies

interupts handler or interrupt service routine(isr) invoked to take care of condition causing interrupt
	* change val of internal vars like counting
	* read a data val like sensor
	* write a data value like actuator

interrupts can be enable and disabled
	* globally
	* individually on a per-peripheral basis
	* non-maskable interrupt - nmi

they commonly used for 
	* urgent tasks w/higher priority than main code
	* infrequent tasks to save polling overhead
	* waking the cpu from sleep 
	* call to an operating system

event driven programming
	
cpu must know where to fetch the next instruction following an interrupt, the address of an isr is defined in an interrupt vector.

The MSP430 uses vectored interrupts where each ISR has its own vector stored in a vector table located at the end of program memory.

ISR;
	* should be short and fast
	* should affects rest of the system as litte as possible

#### P1 and P2 interrupts

* only transitions cause interrupts
* p1ifg & p2ifg (port1 and port2 interrupt edge select reg)
	* bit 0: pxifg is set on low to high transtion
	* bit 1: pxifg is set on high to low transtion
* P1IES & P2IES (port1 and port2 interrupt flag registers)
	* bit 0: no interrupt pending
	* bit 1: interrupt pending

* P1IE & P2IE (port1 and port2 enable reg)
	* bit 0: interrupt disabled
	* bit 1: interrupt enabled

#### Timer interrupt

#### Pulse Width Modulation (PWM)
* pulse width modulation is used to control analog circuits with a processor's digital outputs
* a technique of digitally encoding analog signal levels
	* the duty cycle of a square wave is modulated to encode a specific analog signal level
	* it is digital, at any given instant of time
* the ovltage or current source is supplied to the analog load by means of a repeating series of on and off pulses

#### Processor clock speeds
	* often, the most important factor for reducing power consumption is slowing the clock down
		* faster clock = higher performance, more power
		* slower clock = lower performance, less power
		* we can reduce clock time with assembly code or c code
	* another method to reduce power consumption is to turn off some of the system clocks
		* active mode, am: cpu, all clocks, and enableed modules are active(~300 uA)
		* LPM0: cpu and mclk are disabled, smclk and aclk remain active
		* LPM3: cpu, mclk, smclk and dco are disable; only aclk remains active
		* LPM4: cpu and all clocks disabled, ram is retained
	* a device is said to be sleeping when in low-power mode, waking refers to returning to active mode	
	
#### Principles of Low-Power Apps
	* maximize the time in lpm3 mode
	* use interrupts to wake the processor
	* switch on peripherals only when needed
	* use low power integrated peripherals; timer a and timer b
	* calculated branches instead of flag polling
	* fast table look-ups instead of calculations
	* aboid frequent subroutine and function calls
	* longer software routines should use single-cycle cpu registers
	* setting low power mode puts the microcontroller "to sleep" so usually, interrupts would need to enabled as well.
	* enter lpm3 and enable interrupts using, 
		__bis_SR_register(LPM3_bits + GIE);

		
#### Timers
	* essential to almost any embedded applications
		* generate fixed-period events
		* periodic wakeup
		* count edges
	* five types of msp430 timer modules.
		* basic timer
		* rtc
			*two model, counter and calendar
			* bt and rtc share interrupt vectors
		* watchdog timer
		* Timer A
			* the most versatile one
		* Timer B

##### Applications
	* basic timer / rtc
		* rtc-specific functionality
		* lcd functions
		* interrupt intervals up to two seconds
	* wdt / wdt+
		* can reset device automatically
		* interrupt intervals up to one second
	* timer a/b 
		* widest interrupt interval rane
		* Timer_A/B for PWM, capture, and more-complex counting situations
	* Use the Basic Timer and Watchdog Interval timer for simple interval situations
		
#### Timer 
* Timer A and Timer B. Timer B is slightly different than Timer A and also has few more features.
	* Timer A support 4 different clock sources; aclk, smclk, and 2 external sources, taclk or inclk
* Timer has 4 mode
	* stop mode
		* halted
	* up mode
		* timer reatedly counters from 0 to value
		
	* continuous 
		* timer repeatedly counter from 0 to 0xffff
	* up/down 
		* from 0 to val in taccr0 and back down to zero
##### Registers
* Tar
	* timer counter register: holds current count for timer a
* Taccrx
	* timer capture/compare register: holds a val to compare against tar
* tactl
	* control
* tacctl
	* capture and control
* taiv
	* interrupt vector register

* http://www.ocfreaks.com/msp430-timer-programming-tutorial/
* https://www.ti.com/lit/ml/slap113/slap113.pdf
* https://software-dl.ti.com/trainingTTO/trainingTTO_public_sw/MSP430_LaunchPad_Workshop/v4/Chapters/MSP430m07_LPM.pdf
* https://courses.cs.washington.edu/courses/cse466/11au/calendar/04-Interrupts-posted.pdf
