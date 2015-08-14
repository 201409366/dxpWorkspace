#include <reg52.h>
#define uchar unsigned char
#define  uint unsigned int

uchar readData [4];
sbit IR = P3^3;

sbit buzz = P2^3;

sbit lcdRS = P1^2;
sbit lcdRW = P1^1;
sbit lcdenable = P1^0;

uchar code num [] = "0123456789ABCDEF";

//---------------------1602-------------------
void delay_DS1602(uint i) { //实现了0.001秒的延时

	uchar x,j;

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
	delay_DS1602(5);  //按照手册,延时一会儿
	//给一个高脉冲,让数据有效的被读走
	lcdenable = 1; 
	delay_DS1602(5);
	lcdenable = 0;
}

void write_data(uchar d,uchar position) {
	//RS = L为写指令状态,RS = H 为写数据状态
	if(position != -1) //如果没有postion == -1,说明没有设置位置.我没就接着上一次的地址写
		write_command(0x80 + position);	
	lcdRS = 1;	 //设置液晶为写数据状态
	lcdRW = 0;	//设置为写状态
	P0 = d;	//送数据
	delay_DS1602(5);  //按照手册,延时一会儿
	//给一个高脉冲,让数据有效的被读走
	lcdenable = 1; 
	delay_DS1602(5);
	lcdenable = 0;

}

void init_lcd() {
	//初始化总的环境			   
  lcdenable = 0;//是液晶能接收信号
  write_command(0x38);//设置16x02显示,8位数据口
  write_command(0x01);//清楚当前显示的数据
  write_command(0x0c);//设置显示:开;光标:显示光标:开;闪烁:开
  write_command(0x06);//读写一个字符地址:自动加一;自动滚屏:否  
  write_command(0x80);//设置地址为第一个字符处
}
			 
void main() {
	char a[] = "By 470716740";
	uchar i;
		
	EA = 1;//打开中断总开关
	EX1 = 1;//打开外部中断1
	IT0 = 0;//当IT0=0时，为电平触发方式(低电平)
	init_lcd();
	for(i = 0; i < 12; i++) {
		write_data(a[i],i + 3);	
	}

	while(1);
}

void delay(unsigned char x)    //x*0.14MS
{
	unsigned char i;
	while(x--)
	{
		for (i = 0; i<13; i++) {}
	}
}

void IRHandle() interrupt 2 using 0{
/*
这个是解析函数，按键的键码被放到了readData[2]里面

if (readData[2] == ~readData[3]) {	 //这里验证是为了保证解码成功
   	write_data(num[readData[2]/16],0);
	write_data(num[readData[2]%16],1);
	//这里放的是处理函数
}
*/
	unsigned char j,k,N=0;

	EX1 = 0; //关闭外部中断1  
	delay(15);//延时15*0.14MS=2.1ms
	if (IR==1) { //如果此时IR为高说明什么呢？好像是一开始应该是9ms的低电平
		EX1 =1;//信号没有出现，返回。这次是干扰
		return;
	} 
					   //确认IR信号出现
	while (!IR) {            //等IR变为高电平，跳过9ms的前导低电平信号。
		delay(1);
	}						//延时0.14ms

	for (j=0;j<4;j++)  {       //收集四组数据	 
		for (k=0;k<8;k++) {       //每组数据有8位
			while (IR) {           //等 IR 变为低电平，跳过4.5ms的前导高电平信号。
				delay(1);
			}
			while (!IR) {         //等 IR 变为高电平
				delay(1);
			}
			while (IR) {          //计算IR高电平时长
				delay(1);
				N++;           
				if (N>=30) {//这里会有抖动,所以千万别认为按一次键只解码了一次
					EX1=1;
					return;
				}                  //0.14ms计数过长自动离开。
			}                        //高电平计数完毕     		    
		//数据处理       
			readData[j]=readData[j] >> 1; //数据移位
			if (N>=8) { //8*0.14 = 1.12  如果超过了这个时间，该位为1
				readData[j] |= 0x80;
			}  
			N=0;
		}//end for k
	}//end for j

	if (readData[2] == ~readData[3]) {	 //这里验证是为了保证解码成功
		buzz = !buzz;
	   	write_data(num[readData[2]/16],0);
		write_data(num[readData[2]%16],1);
		//这里直接做解码后面的逻辑处理
		buzz = !buzz;
	}
	EX1 = 1; 
}
