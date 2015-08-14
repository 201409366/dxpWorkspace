#include "buzz.h"

void delay(unsigned int i) { //实现了0.001秒的延时
	unsigned int x,j;
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void main() {
	while(1) {
		buzz.noise();
		delay(10);
		buzz.quiet();
		delay(10);
	}
}

