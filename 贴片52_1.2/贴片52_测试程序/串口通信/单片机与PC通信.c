#include <reg52.h>

void delay (unsigned int time)  {//实现了0.01秒的延时

	unsigned int i,j;

	 for(i = 0; i < time; i++) {
	 	for(j = 0; j < 1872; j++) {
		}
	 } 

}

void init() {//串口初始化函数
	//初始化串口通信,波特率9600
	//设置串口工作方式为工作方式1,8位异步收发,波特率可变
	SM0=0;
	SM1=1;
	TMOD=0x20;//设置定时器1为工作方式2(两个8位的。。。。)
	//给两个寄存器装初值,这个可以根据要设置的波特率来计算。。。。 公式查文档
	TH1=0xfd;
	TL1=0xfd;
	//打开定时器
	TR1=1;//打开定时器1
	REN=1;//串口通信允许位
	
	//开串口中断
	EA=1; //开总中断
	ES=1; //打开串口中断,ES(IE.4) 串行口中断允许位
}

void sendData(unsigned char d) {
	ES = 0;		//关闭串口中断,防止在写数据时触发中断
	SBUF = d; //数据赋值给缓冲区,等待发送
	while(!TI);	 //判断标志位TI,等待发送结束后继续执行
	TI = 0;		 //标志位清零
	ES = 1;		 //打开串口中断
}

void main() {
	unsigned char num = 0;
	//默认串口通讯是不工作的
	init();
	while(1) {
		sendData(num);		
		delay(100);
		num ++;		
	}
}

void handler() interrupt 4 {
	unsigned char temp;
	//中断种类一个5个
	/*其中RI必须由软件清零才能被单片机在接收到下一个信息时再次被置位*/
	ES = 0;		//关闭串口中断,防止在写数据时触发中断
	temp = SBUF;
	SBUF = temp; //数据赋值给缓冲区,等待发送
	while(!TI);	 //判断标志位TI,等待发送结束后继续执行
	TI = 0;		 //标志位清零
	ES = 1;		 //打开串口中断
	RI = 0;
}													  
