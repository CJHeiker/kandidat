// https://www.elfa.se/Web/Downloads/he/et/MCP3426_7_8_eng_datasheet.pdf
#ifndef _ADC_H
#define _ADC_H

class ADC			//Analog to Digital Converter
{
public:
	ADC();

	int getValue(char ch);
	void setGain(char gain);				//(x1, x2, x4, x8)
	void setResolution(int Res)				//(12, 14, 16) bit
	void setConversionMode(bit b)			//1 = continous, 0 = One-shot
	void setAdress(char adr)				//150,152,154,156 possible. Sets adress of the I2C

private:
	double LSB;		//Least Significant Bit
	char PGA;		//Power Gain Amplifier
	char setting;	//
	int ADC_Adr;	//

	int ADC_getValue();                  	//returns value of set channel
	void ADC_setChannel(char ch);         	//sets channel to read to 'ch' (1..4)
	int ADC_readValue();                	//prompts ADC to read, returns 14bit value
	void ADC_setGain(char gain);       		//prompts ADC to chand gain to 'gain' (00..11)
	void ADC_OC(bit b)                  	//prompts ADC to continous or One-shot mode
	void ADC_setResolution(char Res)      	//prompts ADC tp set sample Rate (00..10) (12,14,16  bit)
}
#endif