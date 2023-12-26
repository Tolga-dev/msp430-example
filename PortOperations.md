### General Purpose I/O
GPIO stands for general purpose input and output and refers to the fact that the pins can support both output and input functionalities. 

the manufacturere has to multiplex the pins among the internal modules. This means that each pin has a number of functions that it can perform.

Each port is assigned several 8-bit registers that control the function of the pins and provides information on their current status. 
	* PxSEL PxSEL2, they select whether the pin operates in GPIO mode or is used for a specialized function as described in the pinout. 
	* PxDir
	* PxIN

#### Pull ups and Pull Downs
Saving board space and reducing the number of components is the goal of every engineer. GPIO need a pull-up or pull-down and integrating it in the dvice enables easy configuration and space saving. 

They can only be enabled when gpio is in input mode. in order to control this, a few special registers are used:
	* PxREN: each bit enables 1 or dsables 0 pull up or pull down resistors for the particular pin controlled by the bit.
	* PxOut: when the pin is in input mode and ren is enabled, this register selects whether the resistors is a pull up or pull down.

Pxren only controls whether the functionality is enabled. Pout in this mode is the one that controles 
whether the resistor is pull- up and down. A word of caution is in place. 

#### Power Up defaults
before any code is executed, registers controlling the msp430 are cleared to defaults. This includes PxSel set to 0, along with pxdir.

	* PxSel2 PxSel		PinFunction
	*  0       0              I/O is selected      
	*  0       1	          Primary peripheral module function is selected
	*  1       0              Reserved. See device specific data sheet
	*  1       1              Secondary peripheral module function is selected

* Register	 0	 		1
* PxSEL	 	Input/Output	 Peripheral Module
* PxIN 		Input is '0' 	Input is '1'
* PxOUT 	Output is '0' 	Output is '1'
* PxDIR 	Pin is Input 	Pin is Output


#### Interrupt capability
some gpios have the capability to generate an interrupt and inform the cpu when a transtion has occured. 
	* pxie, each bit enables or disables the interrupt for that particular pin
	* pxies, selects whether a pin will generate an interrupt on the rising 0 or falling 1
	* pxifgm interrupt flag register indicate
	
	
### Memort Mapping
to access a byte from memory of a computer, there is always an adress. to fetch any data or instruction form memory, CPU makes use of address of that data or instruction.

CPU considers ports as memory registers. Each port is a byte in the memory, and pin of the port represents a bit of that register. 

The registers assigned to the port are called peripheral registers, This is called memory mappnig of i/o. 
	* they can be
		* read
		* written
		* modified

How do we decide that whether a port is to used as i/o?
	* with register
		* pxin
		* pxout
		* pxdir

Setting p1dir to one, configures the pins of port1 as output and clearing the p1die, register to zero, it makes it as input.

example
	* p2dir = 0b10110001 means 0,4, 5, 7 are output.
	

#### Accessing individual bits (masking)
* byte is generall used as the smallest entity in mc. 
	* example masking
		 ```c 
			if( ( P1IN & BIT3 ) == 0 ) // Reading the BIT3 of port 1, checking if it is logic low
			{
			 	P2OUT = P2OUT | BIT3; // Setting up BIT3 of P2. i.e. writing the individual bit
			 	// this can also be written as P2OUT |= BIT3
			}
			else
			{
			 	P2OUT &= ~BIT3; // Clearing the BIT3 of P2, if BIT3 of P1 is high.
			}
 		```

* We generally use int or char. they are used for declaration of the counter variable. Their size are 1 and 2 byte respectively. Int8_t abd uint+_t are used to declare signed and unsigned 8 bit integers. 




### sources
* https://www.idc-online.com/technical_references/pdfs/electronic_engineering/I_O_port_operation.pdf
* https://maxembedded.wordpress.com/2013/12/26/io-port-operations-in-msp430/
* https://embeddedtechnosolutions.com/wp-content/uploads/2016/11/MSP430-Tutorial.pdf // page 40
