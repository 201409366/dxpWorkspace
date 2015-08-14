#include <reg52.h>

#include "12864.h"

sbit lcd12864_rs = P1^2;
sbit lcd12864_rw = P1^1;
sbit lcd12864_e = P1^0;

void delay(unsigned int i) { //实现了0.001秒的延时
	
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
	lcd12864WriteCommand(0x30);//设定指令集用基本指令集
	lcd12864WriteCommand(0x0c);//打开屏幕显示 (前1位是1后面三位分别表示 整体显示 游标 游标位置)
	lcd12864WriteCommand(0x01);//清屏指令，防止前面初始化时出现一些乱码在屏幕上面
	lcd12864WriteCommand(0x80);//设置显示地址。也就是屏幕上面的(0,0)点
}

void lcd12864Print(uchar x, uchar y, uchar * data_) {
	// 128/8 = 16; 64/16 = 4; 这个lcd只能显示16x4(符号)或者8x4(汉字);
	//第一行首地址 0x80; 二 0x90; 三 0x88; 四 0x98;
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
