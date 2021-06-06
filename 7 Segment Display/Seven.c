#include "stdint.h"
#include "D:/Essentials/Keil/header/tm4c123gh6pm.h"
void SystemInit(){}
void init(){
	SYSCTL_RCGCGPIO_R |=0X01; //port a
	while((SYSCTL_PRGPIO_R&0x01)==0); //clock for port a
	GPIO_PORTA_DIR_R=0xF0; //PA4-PA7
	GPIO_PORTA_DEN_R=0xF0; //PA4-PA7 DIGITAL
	GPIO_PORTA_AFSEL_R &= ~0xF0; //disable alternative
	GPIO_PORTA_AMSEL_R &= ~0xF0; //disable analog
	GPIO_PORTA_PCTL_R  &= ~0xFFFF0000;
}
/*void reminder(unsigned int num,unsigned int a ,unsigned int b,unsigned int c){
	c=num%10; //units
	num=(num-c)/10; //tens
	b=num%10;
	num=(num-b)/10; 
	a=num/10; //hundreds
}*/
void seg(number){
	switch(number) {
		case 0: GPIO_PORTA_DATA_R =0x00;
		case 1: GPIO_PORTA_DATA_R =0x10; //0001 0000
		case 2: GPIO_PORTA_DATA_R =0x20;
		case 3: GPIO_PORTA_DATA_R =0x30;
		case 4: GPIO_PORTA_DATA_R =0x40;
		case 5: GPIO_PORTA_DATA_R =0x50;
		case 6: GPIO_PORTA_DATA_R =0x60;
		case 7: GPIO_PORTA_DATA_R =0x70;
		case 8: GPIO_PORTA_DATA_R =0x80;
		case 9: GPIO_PORTA_DATA_R =0x90;
		
	}
}
int main(){
	unsigned int units=0;
	unsigned int tens=0;
	unsigned int hundreds=0;
	unsigned int num=195;
	init();
	//reminder(187 /* input number (dummy data)*/,hundreds,tens,units);
	units=num%10;  //dummy data/ ; //units
	num=(num-units)/10; //tens
	tens=num%10;
	num=(num-tens)/10; 
	hundreds=num; //hundreds
	seg(units);
	seg(tens);
	seg(hundreds);

}


