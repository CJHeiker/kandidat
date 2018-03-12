#ifndef _IOConfig_
#define _IOConfig_

	//IO_ADR0 and IO_ADR1 controls the I2C-adress of the ADC. 
	//These should be connected to pins 9 and 10 (Adr0, Adr1) of the ADC
	#define IO_ADR0 10
	#define IO_ADR1 11
	
	//SDA and SCL are the pins used for I2C communication. Pins 20 and 21 are default
	//but can be changed. These variables are NOT used but are noted here so the are 
	//not used for as other outputs
	#define SDA 20
	#define SCL 21
#endif
