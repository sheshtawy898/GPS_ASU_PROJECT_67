#include "stdint.h"
#include "C:/Users/Zezo/Desktop/KeilExamples/tm4c123gh6pm.h"
void SystemInit(){}
//         LCD commands         //
#define clear_display     0x01  
#define moveCursorRight   0x06  
#define cursorBlink       0x0F  
#define Function_set_8bit 0x38  
#define Function_8_bit    0x32  
#define Set5x7FontSize    0x20  
#define FirstRow          0x80  
#define SecondRow         0xC0 
#define RS 0x20 // PORTA BIT5 mask
#define RW 0x40 // PORTA BIT6 mask 
#define EN 0x80 // PORTA BIT7 mask 
/* Milli seconds delay function */
void delay_ms(int n)  
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3180;j++)
 {}
}
/* Micro seconds delay function */
void delay_us(int n) 
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}
 }
void LCD_Cmd(unsigned char command) 
{		GPIO_PORTA_DATA_R &=0x1F; //&=~(0xE0)   CLEAR DATA 0001 1111
    GPIO_PORTB_DATA_R = command ;
		delay_ms(1);
		GPIO_PORTA_DATA_R = EN ;   
    delay_ms(1);              // E ON
    GPIO_PORTA_DATA_R &=0x1F; // E OFF
    if (command < 4)
        delay_ms(2);        
    else
        delay_us(40);        
}
void LCD_init(void)  
{
 SYSCTL_RCGCGPIO_R |=0X03;            // Enable Clock to GPIOB & GPIOA
 while((SYSCTL_PRGPIO_R&0x03)==0);
 GPIO_PORTB_DIR_R  |=0xFF;            // PB0-PB7
 GPIO_PORTB_DEN_R  |=0xFF;            // PB0-PB7
 GPIO_PORTB_AFSEL_R  &=0x00;          // Disable alternative function 
 GPIO_PORTB_AMSEL_R  &=0x00;          // Disable analog for  PB0-PB7
 GPIO_PORTA_DIR_R  |=0xE0;            // PA5-PB7 
 GPIO_PORTA_DEN_R  |=0xE0;            // PB5-PB7	
 GPIO_PORTA_AFSEL_R  &= ~(0xE0);      // Disable alternative function
 GPIO_PORTA_AMSEL_R  &=~(0xE0);	      // Disable analog for  PA5-PA7
 delay_ms(20);
 LCD_Cmd(Set5x7FontSize);             //0x20 select 5x7 font size and 2 rows of LCD 
 delay_ms(50);
 LCD_Cmd(Function_set_8bit);          //0x38 Select 8-bit Mode of LCD
 delay_ms(50);
 LCD_Cmd(clear_display);              //0x01 clear whatever is written on display
 delay_ms(50);
 LCD_Cmd(cursorBlink);                //0x01 Enable Display and cursor blinking 
 delay_ms(50);
 LCD_Cmd(moveCursorRight);            //0x06 shift cursor right 
 delay_ms(50);
}
void LCD_Write_Char(unsigned char data) 
{
	GPIO_PORTA_DATA_R =RS;
  GPIO_PORTB_DATA_R =data;
	GPIO_PORTA_DATA_R = EN | RS;  //(EN) //set pulse -->E
	delay_ms(0);
	GPIO_PORTA_DATA_R &=~(0xE0);  //set down the pulse  
	delay_ms(0);
}

void LCD_String (char *str)
{ int i;
	for(i=0;str[i]!='\0';i++)  
	{
		LCD_Write_Char(str[i]); 
		delay_ms(1);
	}
}
