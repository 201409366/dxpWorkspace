#include <reg52.h>
#include <intrins.h>//这个东西里面有_nop_这个函数

#define uchar unsigned char
#define uint unsigned int

sbit lcdenable = P1^0;
sbit lcdRS = P1^2;
sbit lcdRW = P1^1;

sbit DS18B20_DQ = P1^3;

uchar code num [] = "0123456789";

uchar DS18B20_ID [6];

//--------------------------------------DS1602--------------------------

void delay(uint i) { //实现了0.001秒的延时
	
	uint x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void write_command(uchar c) {
	//RS = L为写指令状态,RS = H 为写数据状态
	lcdRS = 0;	 //设置液晶为写命令状态
	lcdRW = 0;	//设置为写状态
	P0 = c;	//送数据
	delay(5);  //按照手册,延时一会儿
	//给一个高脉冲,让数据有效的被读走
	lcdenable = 1; 
	delay(5);
	lcdenable = 0;
}

void write_data(uchar d,uchar position) {
	//RS = L为写指令状态,RS = H 为写数据状态
	if(position != -1) //如果没有postion == -1,说明没有设置位置.我没就接着上一次的地址写
		write_command(0x80 + position);	
	lcdRS = 1;	 //设置液晶为写数据状态
	lcdRW = 0;	//设置为写状态
	P0 = d;	//送数据
	delay(5);  //按照手册,延时一会儿
	//给一个高脉冲,让数据有效的被读走
	lcdenable = 1; 
	delay(5);
	lcdenable = 0;
	
}

void init_lcd() {
	//初始化总的环境			   
	lcdenable = 0;//是液晶能接收信号
	write_command(0x38);//设置16x02显示,8位数据口
	write_command(0x01);//清楚当前显示的数据
	write_command(0x0c);//设置显示:开;光标:显示光标:关;闪烁:关
	write_command(0x06);//读写一个字符地址:自动加一;自动滚屏:否  
	write_command(0x80);//设置地址为第一个字符处
}
//--------------------------------DS18B20--------------------------

void flash(uchar i) {
	while(-- i);
}

bit ResetDS18B20() {//返回0说明正常
	DS18B20_DQ = 1;
	DS18B20_DQ = 0;
	flash(247);
	DS18B20_DQ = 1;
	flash(27);
	if(DS18B20_DQ == 0) {
		while(DS18B20_DQ == 0);//等待DQ被拉高
		return 0;
	}
	return 1;
	
}

void writeDS18B20(uchar d) {
	uchar i = 0;
	for(i = 0; i < 8; i ++)
		{
			DS18B20_DQ = 1;
			DS18B20_DQ = 0;
			flash(5);			
			DS18B20_DQ = d & 0x01;
			flash(20);
			DS18B20_DQ = 1;
			d >>= 1;
		}
}

uchar readDS18B20 () {
	uchar i = 0;   //就一个初始化的问题。。。困扰我这么久。。。。。fuck
	uchar d = 0;
	for(i = 0; i < 8; i ++) {
		DS18B20_DQ = 1;
		DS18B20_DQ = 0;
		flash(1);//7us
		DS18B20_DQ = 1;
		flash(1);
		if(DS18B20_DQ) {//读数据
			d |= 0x01 << i;
		}
		flash(17);//45us
		DS18B20_DQ = 1;
		_nop_();
	}
	return d;
}

uchar getTemperatur () {
	uchar tempL;
	uchar tempH;
	uchar temperature;//temperature
	
	ResetDS18B20();	//DS18B20复位
	writeDS18B20(0xCC);	//跳过ROM 0xcc
	writeDS18B20(0x44);	//开始温度转换
	ResetDS18B20();	//DS18B20复位
	writeDS18B20(0xCC);		//跳过ROM
	writeDS18B20(0xBE);	//读取温度值.因为温度值在暂存器里面。所以我们读取暂存器里面的东西。
	//因为发了读取指令过去，所以暂存器里面的东西会全部给我们发过来.根据它的结构，
	//我们只要连续读两次
	tempL = readDS18B20();	//先读低8位数据
	tempH = readDS18B20();	//再读高8位数据
	//合成温度数据.可以看存储结构图想到算法
	
	tempL >>= 4;
	tempH <<= 4;
	temperature = tempH | tempL;//得到整数部分
	//温度显示

	return temperature;
}

void main() {
	uchar t;
	init_lcd();
	while(1) {
		t = getTemperatur();
		write_data(num[t % 10],1);//个位
		write_data(num[t / 10],0);//十位
	}
}