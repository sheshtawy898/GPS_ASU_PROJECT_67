#include "stdint.h"
#include <math.h>
#include "D:/Essentials/Keil/header/tm4c123gh6pm.h"
void SystemInit(){}
void init(){
	SYSCTL_RCGCGPIO_R |=0X0B; //port a&b&d
	while((SYSCTL_PRGPIO_R&0x0B)==0){}; //clock for port a&b&d
	//           PORT A INIT            //
 	GPIO_PORTA_DIR_R=0xF0; //PA4-PA7
	GPIO_PORTA_DEN_R=0xF0; //PA4-PA7 DIGITAL
	GPIO_PORTA_AFSEL_R &= ~0xF0; //disable alternative
	GPIO_PORTA_AMSEL_R &= ~0xF0; //disable analog
	GPIO_PORTA_PCTL_R  &= ~0xFFFF0000;
	//           PORT B INIT            //
	GPIO_PORTB_DIR_R=0xF0; //PB4-PB7
	GPIO_PORTB_DEN_R=0xF0; //PB4-PB7 DIGITAL
	GPIO_PORTB_AFSEL_R &= ~0xF0; //disable alternative
	GPIO_PORTB_AMSEL_R &= ~0xF0; //disable analog
	GPIO_PORTB_PCTL_R  &= ~0xFFFF0000;
	//           PORT D INIT            //
	GPIO_PORTD_LOCK_R=0x4C4F434B;
	GPIO_PORTD_CR_R=0xF0;
	GPIO_PORTD_DIR_R=0xF0; //PD4-PD7
	GPIO_PORTD_DEN_R=0xF0; //PD4-PD7 DIGITAL
	GPIO_PORTD_AFSEL_R &= ~0xF0; //disable alternative
	GPIO_PORTD_AMSEL_R &= ~0xF0; //disable analog
	GPIO_PORTD_PCTL_R  &= ~0xFFFF0000;
}
unsigned char hundreds,tens,units;
void decoderData(unsigned char h,unsigned char t,unsigned char u){
	GPIO_PORTA_DATA_R=0x00; // clear data in portA
	GPIO_PORTB_DATA_R=0x00; // clear data in portB
	GPIO_PORTD_DATA_R=0x00; // clear data in portD
	//               READ ME FOR IMPLMETATION
	GPIO_PORTA_DATA_R |= (h<<4); //  first seven segement (hundreds) at port A
	GPIO_PORTB_DATA_R |= (t<<4);     //  second seven segement (tens) at port B
	GPIO_PORTD_DATA_R |= (u<<4);    //  third seven segement (units) at port D
}
void parseNumber(unsigned int distance){
	units=distance%10; //units
	distance=(distance-units)/10; //tens
	tens=distance%10;
	distance=(distance-tens)/10; 
	hundreds=distance; //hundreds
	decoderData(hundreds,tens,units); // save the data
}
                                                // another way to display code
/*void displayDigit( unsigned int digit){ // another way to display code
	switch(digit) {
		case 0: GPIO_PORTA_DATA_R =0x00;
		case 1: GPIO_PORTA_DATA_R =0x10; 
		case 2: GPIO_PORTA_DATA_R =0x20;
		case 3: GPIO_PORTA_DATA_R =0x30;
		case 4: GPIO_PORTA_DATA_R =0x40;
		case 5: GPIO_PORTA_DATA_R =0x50;
		case 6: GPIO_PORTA_DATA_R =0x60;
		case 7: GPIO_PORTA_DATA_R =0x70;
		case 8: GPIO_PORTA_DATA_R =0x80;
		case 9: GPIO_PORTA_DATA_R =0x90;
	}
}*/
int main(){
	init();
	parseNumber(567);
}