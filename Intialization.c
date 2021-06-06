#include "stdint.h"
#include "C:/Keil/UV4/tm4c123gh6pm.h"
void SystemInit(){}
void Inti()
{
	//enable the clock for port A, port B,port F
  SYSCTL_RCGCGPIO_R |= 0x23 ;
	while((SYSCTL_PRGPIO_R & 0X23)==0) ;
	//initialization port A as digital outputs for the control of the LCD 
	GPIO_PORTA_LOCK_R = 0x4C4F434B ;
	GPIO_PORTA_CR_R = 0xE0 ;
	GPIO_PORTA_PCTL_R = 0 ;
        GPIO_PORTA_PUR_R = 0x00 ;
	GPIO_PORTA_DIR_R  |=0xE0;            // PA5-PA7  outputs
        GPIO_PORTA_DEN_R  |=0xE0;            // PA5-PA7 Digital	
        GPIO_PORTA_AFSEL_R  &= ~(0xE0);      // Disable alternative function
        GPIO_PORTA_AMSEL_R  &=~(0xE0);	      // Disable analog for  PA5-PA7
	//initialization port B as digital outputs for the data of the LCD
	GPIO_PORTB_LOCK_R = 0x4C4F434B ;
	GPIO_PORTB_CR_R = 0xFF ;
	GPIO_PORTB_PCTL_R = 0 ;
        GPIO_PORTB_PUR_R = 0x00 ;               
       	GPIO_PORTB_DIR_R  |=0xFF;            // PB0-PB7 outputs
        GPIO_PORTB_DEN_R  |=0xFF;            // PB0-PB7 digital
        GPIO_PORTB_AFSEL_R  &=0x00;          // Disable alternative function 
        GPIO_PORTB_AMSEL_R  &=0x00;          // Disable analog for  PB0-PB7
	//initialization port F as p0,p4 digital inputs and p1,p2,p3 as digital outputs
	//used to enable the built-in led to green and red 
	GPIO_PORTF_LOCK_R =0x4C4F434B;
	GPIO_PORTF_CR_R =0x1F; //PINS used in PORT_F
	GPIO_PORTF_PCTL_R = 0 ;
	GPIO_PORTF_PUR_R =0x11;
	GPIO_PORTF_DIR_R =0x0E; //LEDs Output
	GPIO_PORTF_DEN_R =0x1F; 
	GPIO_PORTF_AFSEL_R =0;
	GPIO_PORTF_AMSEL_R =0;
}	
