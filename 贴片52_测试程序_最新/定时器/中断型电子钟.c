#include <reg52.h>
#include <intrins.h>

#define uint  unsigned int
#define uchar unsigned char

u8 nums [] = "0123456789";
u8 num = 0;

//-------------1602部分------------------------------------------------------------------------
sbit lcdenable = P1^0;
sbit lcdRS = P1^2;
sbit lcdRW = P1^1;


void delay(uint i) { //实现了0.001秒的延时
	
	uint x,j;
	
	for(j=0;j<i;j++) {
		for(x=0;x<=148;x++) {
		}	
	}
}

void writeCommand(uchar c) {
	//RS = L为写指令状态,RS = H 为写数据状态
	lcdRS = 0;	 //设置液晶为写命令状态
	lcdRW = 0;	//设置为写状态
	P0 = c;	//送数据
	delay(5);  //按照手册,延时一会儿
	//给一个高脉冲,让数据有效的被读走
	lcdenable = 1; 
	delay(5);
	lcdenable = 0;
	P0 = 0xff;//关灯								
}

void writeData(uchar d,uchar position) {
	//RS = L为写指令状态,RS = H 为写数据状态
	if(position != -1) //如果没有postion == -1,说明没有设置位置.我没就接着上一次的地址写
		writeCommand(0x80 + position);	
	lcdRS = 1;	 //设置液晶为写数据状态
	lcdRW = 0;	//设置为写状态
	P0 = d;	//送数据
	delay(5);  //按照手册,延时一会儿
	//给一个高脉冲,让数据有效的被读走
	lcdenable = 1; 
	delay(5);
	lcdenable = 0;
	P0 = 0xff;//关灯
}

void init() {
	//初始化总的环境			   
	lcdenable = 0;//是液晶能接收信号
	writeCommand(0x38);//设置16x02显示,8位数据口
	writeCommand(0x01);//清楚当前显示的数据
	writeCommand(0x0c);//设置显示:开;光标:显示光标:开;闪烁:开
	writeCommand(0x06);//读写一个字符地址:自动加一;自动滚屏:否  
	writeCommand(0x80);//设置地址为第一个字符处
}

void main()	 {	
	/*
	0001 GATE=0 ,C/T=0,M0M1=01,
	GATE＝0时，只要用软件使TCON中的TR0或TR1为1，就可以启动定时/计数器工作
	C/T＝0为定时模式
	M0M1=01时,表示工作方式为16位定时/计数器
		*/
	TMOD = 0x01;//这个等效于GATE=0 ,C/T=0,M0M1=01
	TH0=(65536-50000)/256;//计数器装初值
	TL0=(65536-50000)%256;
	EA=1;//打开中断总开关
	ET0=1;//打开定时器中断
	TR0=1;//第一个计时器开始计时

	while(1) {
		//不停的显示
		writeData(nums[num],0);
		delay(10);
	}

}

void increase () {
	num ++;
	if(num > 9) 
		num = 0;
}

//内部中断0中断处理函数
void test1() interrupt 1 {
	//重装初值
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	increase();
}

