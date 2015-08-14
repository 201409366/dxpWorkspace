#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit lcd12864_rs = P1^2;
sbit lcd12864_rw = P1^1;
sbit lcd12864_e = P1^0;

uchar name [] = "By  蓝色枫叶";
uchar qq [] = "QQ:470716740";
uchar time [] = "2012/02/22 15:48";


void delay(unsigned int i) { //实现了0.001秒的延时
	
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
	lcd12864_writeCommand(0x30);//设定指令集用基本指令集
	lcd12864_writeCommand(0x0c);//打开屏幕显示 (前1位是1后面三位分别表示 整体显示 游标 游标位置)
	lcd12864_writeCommand(0x01);//清屏指令，防止前面初始化时出现一些乱码在屏幕上面
	lcd12864_writeCommand(0x80);//设置显示地址。也就是屏幕上面的(0,0)点
}

void main() {
	uchar i;

	lcd12864_init();
	for(i = 0; i < 12; i++) {
		lcd12864_writeData(name[i]);
	}
	lcd12864_writeCommand(0x90);//光标切到第二行
	for(i = 0; i <12; i++) {
		lcd12864_writeData(qq[i]);
	}
	lcd12864_writeCommand(0x88);//光标切到第3行
	for(i = 0; i < 16; i++) {
		lcd12864_writeData(time[i]);
	}
	while(1);
}
