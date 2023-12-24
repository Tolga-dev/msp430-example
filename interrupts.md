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

Summary
* 

* https://courses.cs.washington.edu/courses/cse466/11au/calendar/04-Interrupts-posted.pdf
