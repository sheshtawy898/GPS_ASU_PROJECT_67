#include "stdint.h"
#include "C:/Users/Dell/Desktop/GPS Project/tm4c123gh6pm.h"
#define RED 0x02
#define GREEN 0x08

void SystemInit(){}
void Initialize(){
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R)==0);
	GPIO_PORTF_LOCK_R =0x4C4F434B;
	GPIO_PORTF_CR_R =0x1F; //PINS used in PORT_F
	GPIO_PORTF_AFSEL_R =0;
	GPIO_PORTF_AMSEL_R =0;
	GPIO_PORTF_DIR_R =0x0E; //LEDs Output
	GPIO_PORTF_DEN_R =0x1F;
	GPIO_PORTF_PUR_R =0x11;
}
void LED(float distance) {
	if( distance >=100){
		GPIO_PORTF_DATA_R = GREEN;
	}
	else{
		GPIO_PORTF_DATA_R = RED;
	}
}

int main(){

	float x;
	Initialize();
while(1){
	if((GPIO_PORTF_DATA_R&0x11)==0x01){ x=0;}         //eqv. to start tracking case (Press SW_1)
	else if((GPIO_PORTF_DATA_R&0x11)==0x00){ x=100;}  //eqv. to reach destination case (Press SW_2)
	led(x);
}

}
