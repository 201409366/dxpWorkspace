#ifndef __LED_H__
#define __LED_H__

#include "led.h"
unsigned char ledStatus = 0;

void lightALed() {
	switch (ledStatus) {
		case 0: //�����һ����
			led1 = 0;
			ledStatus++;
			break;
		case 1: //�����һ����
			led2 = 0;
			ledStatus++;
			break;
		case 2:
			led3 = 0;
			ledStatus++;
			break;
		case 3:
			led4 = 0;
			ledStatus++;
			break;
		case 4:
			led5 = 0;
			ledStatus++;
			break;
		case 5:
			led6 = 0;
			ledStatus++;
			break;
		case 6:
			led7 = 0;
			ledStatus++;
			break;
		case 7:
			led8 = 0;
			ledStatus++;
			break;
	}
}


void blowOutALed() {
	switch (ledStatus) {
		case 2: //�������������
			led2 = 1;
			ledStatus--;
			break;
		case 3:
			led3 = 1;
			ledStatus--;
			break;
		case 4:
			led4 = 1;
			ledStatus--;
			break;
		case 5:
			led5 = 1;
			ledStatus--;
			break;
		case 6:
			led6 = 1;
			ledStatus--;
			break;
		case 7:
			led7 = 1;
			ledStatus--;
			break;
		case 8:
			led8 = 1;
			ledStatus--;
			break;
	}
}
#endif