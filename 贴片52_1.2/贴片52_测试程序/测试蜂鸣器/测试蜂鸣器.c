#include <reg52.h>

sbit buzz = P2^3;

void delay (unsigned int time)  {//ʵ����0.01�����ʱ

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