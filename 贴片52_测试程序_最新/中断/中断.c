#include <reg52.h>
#include <intrins.h>

//_crol_
sbit buzz = P2^3;
unsigned char noise = 0;
//_cror_
void Delay (int time)  {//实现了0.01秒的延时

	int i,j;
	 for(i = 0; i < time; i++) {
	 	for(j = 0; j < 1872; j++) {
		}
	 } 

}

void repeattion1() {	//循环移动函数

	unsigned int i;

	for(i = 0; i< 7; i++) {
	 //左移
	 Delay(20);
	 P0 = _crol_(P0,1);
	}
	 Delay(30);

	for(i = 0; i< 7; i++) {
	 //右移
	 P0 = _cror_(P0,1);
	 Delay(30);
	}

	 Delay(30);	
}

void flash() {			//闪烁函数
	char oldP0_ = P0;

	P0 = 0x0;
	Delay(30);
	P0 = 0xff;
	Delay(30);

	P0 = oldP0_;
}

void buzzs() {
	if(noise) {
		buzz = !buzz;
	}
}

void main()	 {
	unsigned int i;

	//中断部分
	EA = 1;//打开中断总开关
	EX0 = 1;//打开外部中断开关
	IT0 = 1;//设置触发事件的方式为跳变沿

	while(1) {
	   	P0 = 0xfe;	//点亮第一个灯
		 //流动两次
		for(i = 0; i < 2; i++) {
			repeattion1();		
			buzzs();
		}
	
		P0 = 0xff;//全灭和延时0.5s
		Delay(50);
		//全部闪动5次
	 
		for(i = 0; i < 5; i++) {
			flash();
			buzzs();
		}
				
	}
}

//中断处理函数

void test1() interrupt 0 {
	noise = !noise;	
}

