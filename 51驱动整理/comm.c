#include "comm.h"

void comm_init() {
	//默认串口通讯是不工作的
	//初始化串口通信
	//设置串口工作方式为工作方式1,8位异步收发,波特率可变
	SM0=0;	 //这两个东西在SCON里面
	SM1=1;

	TMOD=0x20;//设置定时器1为工作方式2(两个8位的。。。。)
	//给两个寄存器装初值,这个可以根据要设置的波特率来计算。。。。 公式查文档
	TH1=0xfd;
	TL1=0xfd;
	//打开定时器
	TR1=1;//启动定时器1

	REN=1;//串口通信允许位

	EA=1; //开总中断
	ES=1; //打开串口中断,ES(IE.4) 串行口中断允许位
}

void sendMsg(unsigned char d) {
	ES = 0;		//关闭串口中断,防止在写数据时触发中断
	SBUF = d; //数据赋值给缓冲区,等待发送
	while(!TI);	 //判断标志位TI,等待发送结束后继续执行
	TI = 0;		 //发送标志位清零
	ES = 1;		 //打开串口中断	
}

void sendMessgae(unsigned char *d) {
	sendMsg(*d);		
	d ++;
	sendMsg(*d);		
}

