#include <reg52.h>

#include "buzz.h"

sbit buz = P2^3;

void delay1(unsigned int i) { //实现了0.001秒的延时
	
	unsigned int x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void buzz() {
	buz = !buz;
	delay1(10);
	buz = !buz;				
}

