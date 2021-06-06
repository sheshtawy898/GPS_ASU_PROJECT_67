#include "stdint.h"
#include "C:/Keil/UV4/tm4c123gh6pm.h"
void SystemInit(){}
void intialization()
{
	//enable the clock for all ports
  SYSCTL_RCGCGPIO_R |= 0x23 ;
	while((SYSCTL_PRGPIO_R & 0XFF)==0) ;
	//initialization port A as digital outputs with  
	GPIO_PORTA_LOCK_R = 0x4C4F434B ;
	GPIO_PORTA_CR_R = 0xFF ;
	GPIO_PORTA_PCTL_R = 0x11 ;
	GPIO_PORTA_AFSEL_R = 0x03  ;
  GPIO_PORTA_PUR_R = 0x00 ;
	GPIO_PORTA_DEN_R = 0xFF ;
	GPIO_PORTA_AMSEL_R &= ~ 0xFF ;
	GPIO_PORTA_DIR_R = 0xFF ;
	GPIO_PORTB_LOCK_R = 0x4C4F434B ;
	GPIO_PORTB_CR_R = 0xFF ;
	GPIO_PORTB_PCTL_R = 0 ;
  GPIO_PORTB_PUR_R = 0x00 ;
	GPIO_PORTB_DEN_R = 0xFF ;
	GPIO_PORTB_AMSEL_R &= ~ 0xFF ;
	GPIO_PORTB_AFSEL_R &= ~ 0xFF  ;
	GPIO_PORTB_DIR_R = 0xFF ;
	GPIO_PORTF_LOCK_R = 0x4C4F434B ;
	GPIO_PORTF_CR_R = 0x1E ;
	GPIO_PORTF_PCTL_R &= ~ 0xFFFFF ;
  GPIO_PORTF_PUR_R = 0x11 ;
	GPIO_PORTF_DEN_R = 0x1F ;
	GPIO_PORTF_AMSEL_R &= ~ 0x1F ;
	GPIO_PORTF_AFSEL_R &= ~ 0x1F  ;
	GPIO_PORTF_DIR_R = 0x0E ;
}	