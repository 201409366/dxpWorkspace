#include <reg52.h>

unsigned char code numbers[16] = {0x5f,0x0a,0x9d,0xd5,0xc6,0xd3,0xdb,0x45,0xdf,0xd7,0xcf,0xda,0x1b,0xdc,0x9b,0x8b};
//unsigned char code ledIndex[8] = {0,1,2,3,4,5,6,7};
sbit p10 = P2^6;
sbit p11 = P2^5;
sbit p12 = P2^4;
sbit p13 = P2^7;

char i;

void delay(unsigned int i) { //实现了0.001秒的延时

	unsigned int x,j;

	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void main() {
   while(1) {
	for(i = 0; i<16; i++) {
	 	if(i == 0) {
				p10 = 0;
				p11 = 1;
				p12 = 1;
				p13 = 1;
			}else if(i == 1) {
				p10 = 1;
				p11 = 0;
				p12 = 1;
				p13 = 1;
			}else if(i == 2) {
				p10 = 1;
				p11 = 1;
				p12 = 0;
				p13 = 1;	
			}else if(i == 3) {
				p10 = 1;
				p11 = 1;
				p12 = 1;
				p13 = 0;	
			}
			P0 = numbers[i];		
			delay(500);
		}
	}
}