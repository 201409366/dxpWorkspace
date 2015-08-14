#include <reg52.h>

sbit buzz = P2^3;

void delay (unsigned int time)  {//实现了0.01秒的延时

	unsigned int i,j;

	 for(i = 0; i < time; i++) {
	 	for(j = 0; j < 1872; j++) {
		}
	 } 

}

void main() {
	while(1) {
		buzz = !buzz;
		delay(30);		
	}
}