#include <reg52.h>

sbit key1 = P3^4;
sbit key2 = P3^5;
sbit key3 = P3^6;
sbit key4 = P3^7;

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
		if(!key1) {
			buzz = !buzz;
			delay(30);
			buzz = !buzz;
			while(!key1);	
		}
		if(!key2) {
			buzz = !buzz;
			delay(30);
			buzz = !buzz;
			while(!key2);
		}
		if(!key3) {
			buzz = !buzz;
			delay(30);
			buzz = !buzz;
			while(!key3);
		}
		if(!key4) {
			buzz = !buzz;
			delay(30);
			buzz = !buzz;
			while(!key4);
		}
	}
}