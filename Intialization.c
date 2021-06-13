#include "D:\Essentials\Keil\header\tm4c123gh6pm.h"
#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#define PI 3.14159
#define RED 0x02
void SystemInit() {}
//------LCD--------//
void delay_milli(int n);
void delay_micro(int n);
void LCD_init(void);
void LCD_Cmd(unsigned char command);
void LCD_Data(unsigned char data);
void SendNumbers(double v);
//------DEGREE CONVERSION-----//
long double degreesToRadians(long double degree);
int distance(long double lat1, long double long1, long double lat2, long double long2);


//-----LED---------//
void port_init(void)
{

    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0) {};
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x02;
    GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DEN_R |= 0x02;
    GPIO_PORTF_AMSEL_R &= ~0x02;
    GPIO_PORTF_AFSEL_R &= ~0X02;
    GPIO_PORTF_PCTL_R &= ~0x000000F0;
    GPIO_PORTF_DATA_R &= ~0x02;
}


void LED(int dist)
{
    if(dist<100)
        GPIO_PORTF_DATA_R &=~ 0x02;
  else
        GPIO_PORTF_DATA_R|=0x02;
}


