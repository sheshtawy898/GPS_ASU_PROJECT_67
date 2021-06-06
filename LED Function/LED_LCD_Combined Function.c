void LED(uint32_t distance) { 
	char print[100];
	if( distance >=100){ 
		GPIO_PORTF_DATA_R = GREEN;
		LCD_Cmd(0x01);
		LCD_Cmd(0x80);
		delay_ms(500);
		sprintf(print, "The Distance: %d, distance);
		LCD_String(print);
	}
	else{
		GPIO_PORTF_DATA_R = RED;
				LCD_Cmd(0x01);
		LCD_Cmd(0x80);
		delay_ms(500);
		sprintf(print, "The Distance: %d, distance);
		LCD_String(print);
	}
}
