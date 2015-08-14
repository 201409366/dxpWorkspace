#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit lcd12864_rs = P1^2;
sbit lcd12864_rw = P1^1;
sbit lcd12864_e = P1^0;

uchar name [] = "By  ��ɫ��Ҷ";
uchar qq [] = "QQ:470716740";
uchar time [] = "2012/02/22 15:48";


void delay(unsigned int i) { //ʵ����0.001�����ʱ
	
	unsigned int x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void lcd12864_writeCommand(uchar comm) {
	lcd12864_e = 0;
	
	lcd12864_rs = 0;
	lcd12864_rw = 0;
	P0 = comm;
	lcd12864_e = 1;
	delay(5);
	
	lcd12864_e = 0;
	
}

void lcd12864_writeData(uchar data_) {
	lcd12864_e = 0;
	
	lcd12864_rs = 1;
	lcd12864_rw = 0;
	P0 = data_;
	lcd12864_e = 1;
	delay(5);
	
	lcd12864_e = 0;
	
}

void lcd12864_init() {
	lcd12864_writeCommand(0x30);//�趨ָ��û���ָ�
	lcd12864_writeCommand(0x0c);//����Ļ��ʾ (ǰ1λ��1������λ�ֱ��ʾ ������ʾ �α� �α�λ��)
	lcd12864_writeCommand(0x01);//����ָ���ֹǰ���ʼ��ʱ����һЩ��������Ļ����
	lcd12864_writeCommand(0x80);//������ʾ��ַ��Ҳ������Ļ�����(0,0)��
}

void main() {
	uchar i;

	lcd12864_init();
	for(i = 0; i < 12; i++) {
		lcd12864_writeData(name[i]);
	}
	lcd12864_writeCommand(0x90);//����е��ڶ���
	for(i = 0; i <12; i++) {
		lcd12864_writeData(qq[i]);
	}
	lcd12864_writeCommand(0x88);//����е���3��
	for(i = 0; i < 16; i++) {
		lcd12864_writeData(time[i]);
	}
	while(1);
}
