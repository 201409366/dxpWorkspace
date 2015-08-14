#include "led.h"
#include "reg52.h"

void turnOn (unsigned char no) {
	P2 = (~no) & P2;	
}

void turnOff (unsigned char no) {
	P2 = no | P2;
}

void toggle (unsigned char no) {
	P2 ^= no;
}
