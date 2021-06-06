#include "stdint.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "C:\Keil\EE319Kware\inc\tm4c123gh6pm.h"
#define RED 0x02
#define GREEN 0x08
#define PI 3.14159
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

double lat1 =0 , lon1=0 , lat2=0 , lon2=0 ;
double DISTANCE=0;
double dist_2p;
double a;
double c;
double dLat;
double dLon;
int x;

void SystemInit(){};
	
void LCD_Cmd(unsigned char cmnd);                

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

	void Init(void)  
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

   // CONVERTING TO RADIANS //
 double degreesToRadians (double degrees)
{ 
  return degrees * PI / 180;
}

   // GETTING DISTANCE BETWEEN TWO COORDINATES //
 double distanceCoordinates (double lat1, double lon1, double lat2, double lon2)
{
  double earthRadiusKm = 6371;

   dLat = degreesToRadians (lat2 - lat1);
   dLon = degreesToRadians (lon2 - lon1);

  lat1 = degreesToRadians (lat1);
  lat2 = degreesToRadians (lat2);

   a = sin (dLat / 2) * sin (dLat / 2) +
    sin (dLon / 2) * sin (dLon / 2) * cos (lat1) *
    cos (lat2);
   c = 2 * atan2 (sqrt (a), sqrt (1 - a));
  return earthRadiusKm * c*1000;
}

        // LED FUNCTION //
void LED(uint32_t distance) { 
	char print[100];
	if( distance >=100){ 
		GPIO_PORTF_DATA_R = GREEN;
		delay_ms(500);
		sprintf(print, "  Distance:%d", distance);
		LCD_String(print);
	}
	else{
		GPIO_PORTF_DATA_R = RED;
		delay_ms(500);
		sprintf(print, "  Distance:%d", distance);
		LCD_String(print);
	}
}

int main(){ 
			lat2=30.049785453996144;
			lon2=31.385213143122954;
			dist_2p= distanceCoordinates(lat1, lon1 ,lat2, lon2);

	 //while loop to exit when the distance exceeds 100 meters
		while (DISTANCE < 100){
			lat1=lat2;
			lon1=lon2;
			lat2=30.049715814599192;
			lon2=31.3845695190232;

			dist_2p= distanceCoordinates(lat1, lon1 ,lat2, lon2);
			DISTANCE += dist_2p;
			lat2=30.049675638000775;
			lon2=31.384170348297996;
			
		}

			x = ceil(DISTANCE);
     Init();
     LCD_Cmd(clear_display);
     // WRITING IN THE FIRST ROW //
     LCD_Cmd(FirstRow); // Force cusor to begining of first row
		LCD_String("   GPS Team 67");
		 //	WRITING IN THE SECOND ROW //
     delay_ms(50);
	   LCD_Cmd(SecondRow); // Force cusor to begining of Second row     
			
		 LED(x);
		delay_ms(500); 	

}



            // UNUSED 7 SEGMENTS CODE //

/*unsigned char hundreds,tens,units;
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
void displayDigit( unsigned int digit){ // another way to display code
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


