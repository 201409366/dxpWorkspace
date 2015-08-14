#include <reg52.h>

#include "12864.h"

sbit lcd12864_rs = P1^2;
sbit lcd12864_rw = P1^1;
sbit lcd12864_e = P1^0;

void delay(unsigned int i) { //ʵ����0.001�����ʱ
	
	unsigned int x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void lcd12864WriteCommand(uchar comm) {
	lcd12864_e = 0;
	
	lcd12864_rs = 0;
	lcd12864_rw = 0;
	P0 = comm;
	lcd12864_e = 1;
	delay(5);
	
	lcd12864_e = 0;
	
}

void lcd12864WriteData(uchar data_) {
	lcd12864_e = 0;
	
	lcd12864_rs = 1;
	lcd12864_rw = 0;
	P0 = data_;
	lcd12864_e = 1;
	delay(5);
	
	lcd12864_e = 0;
	
}

void lcd12864Init() {
	lcd12864WriteCommand(0x30);//�趨ָ��û���ָ�
	lcd12864WriteCommand(0x0c);//����Ļ��ʾ (ǰ1λ��1������λ�ֱ��ʾ ������ʾ �α� �α�λ��)
	lcd12864WriteCommand(0x01);//����ָ���ֹǰ���ʼ��ʱ����һЩ��������Ļ����
	lcd12864WriteCommand(0x80);//������ʾ��ַ��Ҳ������Ļ�����(0,0)��
}

void lcd12864Print(uchar x, uchar y, uchar * data_) {
	// 128/8 = 16; 64/16 = 4; ���lcdֻ����ʾ16x4(����)����8x4(����);
	//��һ���׵�ַ 0x80; �� 0x90; �� 0x88; �� 0x98;
	uchar address;
	switch (y) {
		case 0: 
			address = 0x80 + x;
			break;
		case 1:
			address = 0x90 + x;
		break;
		case 2:
			address = 0x88 + x;
		break;
		case 3:
			address = 0x98 + x;
		break;
	}
	lcd12864WriteCommand(address);
		while(*data_ > 0) { 
		lcd12864WriteData(*data_);
		data_++;
    }
	
}
