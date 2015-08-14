#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit DS1302_SCLK = P2^2;
sbit DS1302_IO = P2^1;
sbit DS1302_RST = P2^0;

sbit lcdRS = P1^2;
sbit lcdRW = P1^1;
sbit lcdenable = P1^0;

uchar sec;
uchar min;
uchar h;
uchar date;
uchar month;
uchar day;
uchar year;

//因为时分秒，年月日，星期的读法和写法都不一样。。所以全部封装成方法
//uchar code readMap [] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};
//uchar code writeMap [] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
//sec min h date month day year

//unsigned char code ledNumbers[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar code num [] = "0123456789";

uchar code initData0 [] = "2011-12-23 Day:5";
uchar code initData1 [] = "00:00:00";

void delay(uint i) { //实现了0.001秒的延时

	uchar x,j;

	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}
////-----------------DS1602---------------------------------------
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

void writeLcd(uchar d,uchar position) {
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

void initLcd() {
	uchar i;
	//初始化总的环境			   
	lcdenable = 0;//是液晶能接收信号
	write_command(0x38);//设置16x02显示,8位数据口
	write_command(0x01);//清楚当前显示的数据
	write_command(0x0f);//设置显示:开;光标:显示光标:开;闪烁:开
	write_command(0x06);//读写一个字符地址:自动加一;自动滚屏:否  
	write_command(0x80);//设置地址为第一个字符处

		//初始化显示
	for(i = 0; i < 16; i ++) {
		writeLcd(initData0[i],-1);
	}
	write_command(0x80 + 0x40 + 0x04);//设置第二排地址
	for(i = 0; i < 8; i++) {
		writeLcd(initData1[i],-1);
	}

}
//------------------------------------------DS1302----------------------------

void writeDS1302(uchar command, uchar parameter) {
	uchar i;
	DS1302_SCLK = 0;
	DS1302_RST = 0;
	DS1302_RST = 1;
	for(i = 0; i < 8; i++) { //写指令
		DS1302_IO = command & 0x01;	//取command的最低位
		DS1302_SCLK = 1;
		command >>= 1;
		DS1302_SCLK = 0;
		
	}
	for(i = 0; i < 8; i++) { //写参数
		DS1302_IO = parameter & 0x01;
		DS1302_SCLK = 1;
		parameter >>= 1;
		DS1302_SCLK = 0;		
	}
	DS1302_RST = 0;	
}

uchar readDs1302(uchar command) {
	uchar i,d;
	DS1302_RST = 0;
	DS1302_SCLK = 0;
	DS1302_RST = 1;
	for(i = 0; i < 8; i++) { //写指令
		DS1302_SCLK = 0;
		DS1302_IO = command & 0x01;//取command的最低位
		DS1302_SCLK = 1;	//这里只能保持高，不然后面的一变低就就数据输出。这样就会出错
		command >>=	1;
	}
	/*
	注意在这里交界处的写法,中间时钟不能随便变化。注意对照datasheet来写。不然就会出错的
	*/
	for(i = 0; i < 8; i++) { //读数据
		DS1302_SCLK = 0;  //一拉低就能读取数据了
		if(DS1302_IO) //读走数据
			d |=  0x01 << i;
		DS1302_SCLK = 1;
	}

	DS1302_RST = 0;
	d = (d / 16 * 10) + (d % 16);
	return d;
}

void initDS1302() {


	writeDS1302(0x8E,0x00);//打开保护，是寄存器可读可写
	writeDS1302(0x84,0x00);//时寄存器全部置零,是计时器变为24小时制
	
	/*
	if(readDs1302(0xC1)) {
		//如果DS1302已经被初始化，直接关闭保护。返回即可
		writeDS1302(0x8E,0x80);//关闭保护
		return;
	}
   	 
	*/
	//写数据 min h date month day year
	writeDS1302(0x82,0x00);
	writeDS1302(0x84,0x12);
	writeDS1302(0x86,0x23);
	writeDS1302(0x88,0x12);
	writeDS1302(0x8a,0x05);
	writeDS1302(0x8c,0x11);//11年 因为这个芯片只有年的后面两位
	
	writeDS1302(0x80,0x00); //秒位全部置零,启动时钟
	//向DS1302的ram中写一个数，表示DS1302已经被启动了
	//ram的写指令:0xc0.读指令是:0xc1
	writeDS1302(0xc0,0x01);	//随便写个数表示DS1302已经被初始化
	writeDS1302(0x8E,0x80);//关闭保护
	
}


void main() {
	initDS1302();
	initLcd();
	while(1) {
		sec = readDs1302(0x81);//秒
		writeLcd(num[sec % 10],0x4b);//个位
		writeLcd(num[sec / 10],0x4a);//十位
			
		min = readDs1302(0x83);//分
		writeLcd(num[min % 10],0x48);
		writeLcd(num[min / 10],0x47);

		h = readDs1302(0x85);
		writeLcd(num[h % 10],0x45);
		writeLcd(num[h / 10],0x44);
		
		date = readDs1302(0x87);
		writeLcd(num[date % 10],0x09);
		writeLcd(num[date / 10],0x08);
		
		month = readDs1302(0x89);
		writeLcd(num[month % 10],0x06);
		writeLcd(num[month / 10],0x05);

		day = readDs1302(0x8b);
		writeLcd(num[day % 10],0x0f);

		year = readDs1302(0x8d);
		writeLcd(num[year % 10],0x03);
		writeLcd(num[year / 10],0x02);
	   	
		//读取秒的最高位，如果为1的话说明DS1302没有被初始化，或者出现了别的故障。我们就把初始化标识去掉
		
		/*	
		if(year == 0 && sec >= 60) {
			writeDS1302(0x8E,0x00);//打开保护，是寄存器可读可写	
			writeDS1302(0xc0,0x00);	
			writeDS1302(0x8E,0x80);//关闭保护
			while(1);
		}
		*/
	}
	

}

 