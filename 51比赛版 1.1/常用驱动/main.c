#include "led.h"


void delay(unsigned int i) { //ʵ����0.001�����ʱ
	
	unsigned int x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void main() {
	turnOn(LED0);
	turnOn(LED1);
	delay(500);
	turnOff(LED0);
	while(1) {
		delay(500);
		toggle(LED0);
	}
}