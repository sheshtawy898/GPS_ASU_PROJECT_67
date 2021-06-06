#include "stdint.h"
#include "C:/Users/Zezo/Desktop/KeilExamples/tm4c123gh6pm.h"
void SystemInit(){};
void LCD_Cmd(unsigned char cmnd);                
//         LCD commands         //
#define clear_display     0x01  
#define moveCursorRight   0x06  
#define cursorBlink       0x0F  
#define Function_set_8bit 0x38  
#define Function_8_bit    0x32  
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
 LCD_Cmd(0x30);     
 delay_ms(20);
	LCD_Cmd(0x30);    
 delay_ms(20);
	LCD_Cmd(0x30);    
 delay_ms(20);
 LCD_Cmd(0x38);     //Function_set_8bit
 delay_ms(50);
 LCD_Cmd(0x06);     //moveCursorRight
 delay_ms(50);
 LCD_Cmd(0x01);     //clear_display
 delay_ms(50);
 LCD_Cmd(0x0F);     //cursorBlink 
 delay_ms(50);
 
}

 void LCD_Cmd(unsigned char command) 
{   GPIO_PORTA_DATA_R &=~(0xE0) ;      
    GPIO_PORTB_DATA_R = command ;
    delay_ms(1);
    GPIO_PORTA_DATA_R |= EN ;  
    delay_ms(1);              // Pulse on
    GPIO_PORTA_DATA_R = 0;    // Pulse off                                    
    if (command < 4)
		delay_ms(2);              // command 1 and 2 needs up to 1.64ms 
		else
		delay_us(40);                                          
} 

void LCD_Write_Char(unsigned char data) 
{
    GPIO_PORTA_DATA_R |=RS;
		GPIO_PORTB_DATA_R =data;
    GPIO_PORTA_DATA_R = EN | RS;  //Can be modified later
    delay_ms(0);
    GPIO_PORTA_DATA_R &= ~(0xE0);   //set down the pulse   //can be modified 
    delay_ms(40);                                                            
}

void LCD_String (char *str)  // Send string to LCD function
{ int i;
    for(i=0;str[i]!='\0';i++)  
    {
        LCD_Write_Char(str[i]);  
        delay_ms(1);
    }
}

