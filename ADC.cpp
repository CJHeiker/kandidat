#include "ADC.h"
#include "IOconfig.h"
#include <Wire.h>

//Number of steps to move bits to correspond to 'setting'
#define READY_BIT 7
#define CHANNEL_BIT 5				
#define CONVERSION_BIT 4			
#define SAMPLE_RATE_BIT 2
#define PGA_BIT 0

double LSB = 1000.0;					//(micro Volts)	Value of Least Significant bit
char PGA = 1;							//(multiple) 	Power Gain Amplifier
char setting = 0x10010000;				//'setting' is the settings transfered to the ADC
int ADC_Adr = 208;							//ADC's I2C adress 208 as default


void ADC::initiate(){
	Wire.begin();
	Wire.onReceive(ADC_receiveHandler);
	setAdress(ADC_Adr);
	Wire.setClock(100000);
}
int ADC::getValue(char ch){
	char converted = ch<<CHANNEL_BIT;		//Convert 'ch' to correspond to 'setting'
	if(! setting & converted){				//Check if needs to change channel
		setChannel(converted);				//Change channel
	}
	return ADC_getValue();
}
void ADC::setGain(char gain){				//1,2,4,8 as input
	switch(ch){
		case 1:
			ADC_setGain(0x00<<PGA_BIT);
			break;
		case 2:
			ADC_setGain(0x01<<PGA_BIT)
			break;
		case 4:
			ADC_setGain(0x10<<PGA_BIT);
			break;
		case 8:
			ADC_setGain(0x11<<PGA_BIT);
			break;
	}
}
void ADC::setResolution(int Res){
	switch(SR){
		case 12:
			ADC_setSampleRate(0x00<<SAMPLE_RATE_BIT);
			LSB = 1000.0;		//Least significant bit = 1000 micro volts
			break;
		case 14:
			ADC_setSampleRate(0x01<<SAMPLE_RATE_BIT);
			LSB = 250.0;		//Least significant bit = 250 micro volts
			break;
		case 16:
			ADC_setSampleRate(0x10<<SAMPLE_RATE_BIT);
			LSB = 62.5;			//Least significant bit = 62.5 micro volts
			break;
	}
}
void ADC::setConversionMode(bit b){
	char CM = (char)b;
	ADC_setConversionMode(CM<<CONVERSION_BIT);
}
void ADC::setAdress(int adr){
	switch(adr){
		case 150:
			ADC_Adr = adr;
			digitalWrite(IO_ADR0, 0);
			digitalWrite(IO_ADR1, 0);
			break;
		case 152:
			ADC_Adr = adr;
			digitalWrite(IO_ADR0, 0);
			digitalWrite(IO_ADR1, 1);
			break;
		case 154:
			ADC_Adr = adr;
			digitalWrite(IO_ADR0, 1);
			digitalWrite(IO_ADR1, 0);
			break;
		case 156:
			ADC_Adr = adr;
			digitalWrite(IO_ADR0, 1);
			digitalWrite(IO_ADR1, 1);
			break;
	}
}
int ADC::getAdress(){
	return ADC_Adr;
}
void ADC::changeSpeed(int spd){
	Wire.setClock(spd);
}
//
//Below are functions not accessable for the user.
//Theses are used to comminicate with the ADC
//

int ADC_getValue() {					//channel already changed
	int value = readValue();
	return value * LSB / PGA;
}
void ADC_setChannel(char ch){			//'ch' already converted in 'getValue()'
	setting |= ch
}
void ADC_setGain(char gain){			//'gain' already converted in 'setGain()'
	char temp = 0x1111111 & gain;
	setting |= temp;
}
void ADC_setResolution(char Res){		//'SR' already converted in 'setSampleRate()'
	char temp = 0x1111111 & Res;
	setting |= temp;
}
void ADC_setConversionMode(char CM){	//'CM' already converted in 'setConversionMode()'
	setting |= CM;
}
void ADC_updateSettings(){
	Wire.beginTransmission(ADC_Adr);
	Wire.write(setting);
	Wire.endTransmission();
	0x101
	0x100
	0x100
}
void readValue(){}
void ADC_receiveHandler(int numBytes){
	
}