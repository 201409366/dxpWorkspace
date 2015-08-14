#include <reg52.h>
#include "key.h"
#include "led.h"

extern unsigned char ledStatus;

sbit soundSource1 = P1^3;
sbit soundSource2 = P1^2;
sbit soundSource3 = P1^1;
sbit soundSource4 = P1^0;

sbit volume1 = P0^3;
sbit volume2 = P0^7;
sbit volume3 = P2^4;
sbit volume4 = P2^0;

u8 volumeStatus = 0;

void changeVolume() {
	switch(ledStatus) {
		case 1:	  //音量最小
			volume1 = 0;
			volume2 = 1;
			volume3 = 1;
			volume4 = 1;
			break;
		case 3:
			volume1 = 0;
			volume2 = 0;
			volume3 = 1;
			volume4 = 1;
			break;
		case 5:
			volume1 = 0;
			volume2 = 0;
			volume3 = 0;
			volume4 = 1;
			break;
		case 7:
			volume1 = 0;
			volume2 = 0;
			volume3 = 0;
			volume4 = 0;
			break;
	}	
}

void increaseVolume() {
	lightALed();
	changeVolume();	
}

void decreaseVolume() {
	blowOutALed();
	changeVolume();	
}

void changeSoundSource() {
	switch(volumeStatus) {
		case 1 :
			soundSource1 = 0;
			soundSource2 = 1;	
			volumeStatus ++;	
			break; 	
		case 2 :
			soundSource2 = 0;
			soundSource3 = 1;	
			volumeStatus ++;	
			break; 
		case 3 :
			soundSource3 = 0;
			soundSource4 = 1;	
			volumeStatus ++;	
			break; 
		case 4 :
			soundSource4 = 0;
			soundSource1 = 1;	
			volumeStatus = 1;	
			break; 
	}
}
	
void init() {
	//音源选择第一个 
	soundSource1 = 0;
	soundSource2 = 0;
	soundSource3 = 0;
	soundSource4 = 0;
	volumeStatus = 1;

//音量初始化为最小
  	volume1 = 0;
	volume2 = 0;
	volume3 = 0;
	volume4 = 0;
	lightALed();//初始化的时候所有灯都没亮,这里点亮一个就好了
	//至于音量设置，有了继电器之后再说
}

void main() {
	u8 key = 0;
	init();
	
	while(1) {
		key = scanKey();
		if(key) {
			switch (key) {
				case 1:
					increaseVolume();
					break;
				case 2:
					decreaseVolume();
					break;
				case 3:
					changeSoundSource();
					break;
			}
		}
	}

}

