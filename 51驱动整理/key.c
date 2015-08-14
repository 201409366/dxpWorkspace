#include "key.h"

sbit key1 = P3^7;
sbit key2 = P3^6;
sbit key3 = P3^5;
sbit key4 = P3^4;

sbit buzz = P2^3;

void delay_ms(unsigned int i) { //ʵ����0.001�����ʱ
	
	unsigned int x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

unsigned char getKey() {
	if(!key1 || !key2 || !key3 || !key4) { //����а���������
	 	delay_ms(15);//����
   		if(!key1 || !key2 || !key3|| !key4) { //������а��������£�˵��������ı�����
			if(key1 == 0) {
				buzz = 0;
				while(!key1); //�ȴ���������
				buzz = 1;
				return 1;				
			}
			else if(key2 == 0)  {
				buzz = 0;
				while(!key2); //�ȴ���������
				buzz = 1;
				return 2;
			}
			else if(key3 == 0) {
				buzz = 0;
				while(!key3); //�ȴ���������
				buzz = 1;
				return 3;
			}
			else if(key4 == 0) {
					buzz = 0;
					while(!key4); //�ȴ���������
					buzz = 1;
					return 4;
			}
		}		
	}
	return 0;	
}
