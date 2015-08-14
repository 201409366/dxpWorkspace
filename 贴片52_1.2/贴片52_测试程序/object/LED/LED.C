#include "led.h"
#include "reg52.h"

void light (unsigned char num);
void blow (unsigned char num);

LED led = {
	light,
	blow
};


void light (unsigned char num) {
	P0 = (~num) & P0;	
}

void blow (unsigned char num) {
	P0 = num | P0;
}