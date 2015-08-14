#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char

uchar i;

void delay (unsigned int time)  {//实现了0.01秒的延时

	unsigned int i,j;

	 for(i = 0; i < time; i++) {
	 	for(j = 0; j < 1872; j++) {
		}
	 } 

}


void main() {
	P0 = 0xfe;
	while(1) {
		if(i < 8) {
			P0 = _crol_(P0,1);
			delay(10);
			i++;
		} else if(i < 16) {
			P0 = _crol_(P0,1);
			delay(25);	
			i++;
		} else{
			P0 = _crol_(P0,1);
			delay(50);
			i++;
		}
		if(i >= 24) {
			i = 0;
		}
	}

}