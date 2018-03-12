// https://www.elfa.se/Web/Downloads/he/et/MCP3426_7_8_eng_datasheet.pdf
#ifndef ADC_H
#define ADC_H

#include "Arduino.h"
#include "IOconfig.h"
#include <Wire.h>

class ADs
{			//Analog to Digital Converter

  public:
	  ADs();

  	int getValue(char ch);
  	void setGain(char gain);				//(x1, x2, x4, x8)
  	void setResolution(int Res);				//(12, 14, 16) bit
  	void setConversionMode(char CM);			//1 = continous, 0 = One-shot
  	void setAdress(int adr);				//150,152,154,156 possible. Sets adress of the I2C
    int getAdress();
    void changeSpeed(int spd);

  private:
  	double LSB;		//Least Significant Bit
    char numBits;
  	char PGA;		//Power Gain Amplifier
  	char setting;	//
  	int ADC_Adr;	//
    int latestValue;
  
  	int toNumb(String str);
  	int ADC_getValue();                  	//returns value of set channel
  	void ADC_setChannel(char ch);         	//sets channel to read to 'ch' (1..4)
  	int ADC_readValue();                	//prompts ADC to read, returns 14bit value
  	void ADC_setGain(char gain);       		//prompts ADC to chand gain to 'gain' (00..11)
  	void ADC_OC(char b);                  	//prompts ADC to continous or One-shot mode
  	void ADC_setResolution(char Res);      	//prompts ADC tp set sample Rate (00..10) (12,14,16  bit)
    void readValue();
    void ADC_receiveHandler();
    void ADC_setConversionMode(char CM);
    
};
#endif
