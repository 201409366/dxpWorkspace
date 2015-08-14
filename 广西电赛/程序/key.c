#ifndef __KEY_H__
#define __KEY_H__

#include "key.h"

void Delay(unsigned int i) { //实现了0.001秒的延时

	unsigned char x,j;

	for(j = 0; j < i; j ++) {
		for(x = 0; x <= 148; x ++) {
		}	
	}
}

u8 scanKey() {
	if(!key1 || !key2 || !key3) {
		Delay(10);
		if(!key1 || !key2 || !key3) {
			Delay(10);
			if(key1 == 0) {
				while(!key1);	
				return 1;
			}else if(key2 == 0) {
				while(!key2);
				return 2;
			}else if(key3 == 0) {
				while(!key3);
				return 3;
			}
		}
	}
	return 0;
}
#endif