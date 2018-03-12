#include "ADC.h"
#include <math.h>

//Number of steps to move bits to correspond to 'setting'
#define READY_BIT 7
#define CHANNEL_BIT 5				
#define CONVERSION_BIT 4			
#define SAMPLE_RATE_BIT 2
#define PGA_BIT 0

double LSB = 1000.0;					//(micro Volts)	Value of Least Significant bit
char numBits;
char PGA = 1;							//(multiple) 	Power Gain Amplifier
char setting = 0x10010000;				//'setting' is the settings transfered to the ADC
int ADC_Adr = 208;							//ADC's I2C adress 208 as default
int latestValue;


ADs::ADs(){
  Wire.begin();
  setAdress(ADC_Adr);
  Wire.setClock(100000);
}
int ADs::getValue(char ch){
	char converted = ch<<CHANNEL_BIT;		//Convert 'ch' to correspond to 'setting'
	if(! setting & converted){				//Check if needs to change channel
		ADC_setChannel(converted);				//Change channel
	}
	return ADC_getValue();
}
void ADs::setGain(char gain){				//1,2,4,8 as input
	switch(gain){
		case 1:
			ADC_setGain(0x00<<PGA_BIT);
			break;
		case 2:
			ADC_setGain(0x01<<PGA_BIT);
			break;
		case 4:
			ADC_setGain(0x10<<PGA_BIT);
			break;
		case 8:
			ADC_setGain(0x11<<PGA_BIT);
			break;
	}
}
void ADs::setResolution(int Res){
	switch(Res){
		case 12:
			ADC_setResolution(0x00<<SAMPLE_RATE_BIT);
			LSB = 1000.0;		//Least significant bit = 1000 micro volts
      numBits = 12;
			break;
		case 14:
			ADC_setResolution(0x01<<SAMPLE_RATE_BIT);
			LSB = 250.0;		//Least significant bit = 250 micro volts
      numBits = 14;
			break;
		case 16:
			ADC_setResolution(0x10<<SAMPLE_RATE_BIT);
			LSB = 62.5;			//Least significant bit = 62.5 micro volts
      numBits = 16;
			break;
	}
}
void ADs::setConversionMode(char CM){
	ADC_setConversionMode(CM<<CONVERSION_BIT);
}
void ADs::setAdress(int adr){
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
int ADs::getAdress(){
	return ADC_Adr;
}
void ADs::changeSpeed(int spd){
	Wire.setClock(spd);
}
//
//Below are functions not accessable to the user.
//Theses are used to comminicate with the ADC
//
int ADCtoNumb(String str){ //Converts incomming message from ADC to a number
  int converted = 0;
  int exponent = 0;
  for(int i = str.length()-1; i >= 0; i--){
    if(str.substring(i,i+1).equals("1")){
      converted += pow(2,exponent);
    }
    exponent++;
  }
  return converted;
}
int ADC_getValue() {					//channel already changed
	Wire.requestFrom(ADC_Adr, numBits);
  String message = "";
  while (Wire.available()) { // slave may send less than requested
    message += Wire.read(); // receive a byte as character
  }
  int value = ADCtoNumb(message);
	return value * LSB / PGA;
}
void ADC_setChannel(char ch){			//'ch' already converted in 'getValue()'
	setting |= ch;
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
}



