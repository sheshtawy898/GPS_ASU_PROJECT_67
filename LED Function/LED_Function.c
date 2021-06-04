#include "stdint.h"
#define RED 0x02
#define GREEN 0x08

void LED(float distance) {
	if( distance >=100){
		GPIO_PORTF_DATA_R = GREEN;
	}
	else{
		GPIO_PORTF_DATA_R = RED;
	}
}

