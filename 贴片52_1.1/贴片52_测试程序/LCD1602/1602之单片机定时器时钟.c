#include <reg52.h>
#include <intrins.h>

#define uint  unsigned int
#define uchar unsigned char

//-------------1602部分------------------------------------------------------------------------
sbit lcdenable = P1^0;
sbit lcdRS = P1^2;
sbit lcdRW = P1^1;
//-------------原始部分------------------------------------------------------------------------------
 
//定义时钟模式显示的数码管的下标
uint indexOfMs0 = 0;
uint indexOfMs1 = 0;
uint indexOfS0 = 0;
uint indexOfS1 = 0;
uint indexOfM0 = 0;
uint indexOfM1 = 0;
uint indexOfH0 = 0;
uint indexOfH1 = 0;

//定义定时模式显示的数码管的下标
uint indexOfTimerOfMs0 = 0;
uint indexOfTimerOfMs1 = 0;
uint indexOfTimerOfS0 = 0;
uint indexOfTimerOfS1 = 0;
uint indexOfTimerOfM0 = 0;
uint indexOfTimerOfM1 = 0;
uint indexOfTimerOfH0 = 0;
uint indexOfTimerOfH1 = 0;


//用来时钟模式计时用了多少秒
uchar count = 0;
//用来计时器模式计时用了多少秒
uchar count2 = 0;


//用来计时的
uchar temp1 = 0;
//扫描时间计时器
uchar temp2 = 0;

//用来标识按键是否被按下
uchar bPress = 0;

//定义3个按键
sbit key1 = P2^0;
sbit key2 = P2^1;
sbit key3 = P2^2;

//计时器 用来判断按键按下的时间的
uchar isTimer = 0;

//标识定时器的开始与结束
uchar isStarted = 0;
uchar isStoped = 0;

uchar code initDate [] = "2011-11-11";
uchar code initTime [] = "00:00:00";
uchar code numbers [] = "01234567890";
uchar index;

//声明按键处理函数
void keyInterruptHandle();
void updateLED(uint i0, uint i1, uint i2, uint i3, uint i4, uint i5, uint i6, uint i7);

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
  //初始化时钟显示
  writeCommand(0x80+0x03);
  for(index = 0; index < 10; index++) {
  	   writeData(initDate[index],-1);
  }

  writeCommand(0x80+0x40+0x04);
  for(index = 0; index < 8; index++) {
  	   writeData(initTime[index],-1);
  }

}


void main()	 {	
	TMOD = 0x01;
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	EA=1;//打开中断总开关
	ET0=1;//打开定时器中断
	TR0=1;//第一个计时器开始计时

   //给按键端口初始化
   key1 = 1;
   key2 = 1;
   key3 = 1;
   init();
    
	while(1) {
		//用视频里面的方法来检测按键。也就是消抖。。。。因为现在的按键处理还不是非常的完美
		keyInterruptHandle();

	}

}

//内部中断0中断处理函数
void timeInterruptHandle() interrupt 1 {  
	//用最直观的方法来实现我们的时钟功能，在后面用算法来实现。用除60取余。。。来实现
	//当前时钟中断1ms触发一次
   	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	count++;
	if(isTimer) {
		count2++;
	}

	if(count >= 10) { //判断10ms;
		 indexOfMs0++;
		 count = 0;
		 if(indexOfMs0 >= 10) {
		 	indexOfMs0 = 0;
			 indexOfMs1++;
			if(indexOfMs1 >= 10) { //判断时间都一秒
				indexOfS0++;
				indexOfMs1 = 0;
				writeData(numbers[indexOfS0],0x40+0x0b);
				if(indexOfS0 >= 10) {
					indexOfS0 = 0;//当秒第一位到9后置0
					indexOfS1++;//当秒位的第一位满9后，向第二位进一
					writeData(numbers[indexOfS1],0x40+0x0a);
					if(indexOfS1 > 5) {
						indexOfS1 = 0; //当秒第二位到5后置0
						indexOfM0++;//向分位进一
						writeData(numbers[indexOfS1],0x40+0x0a);
						writeData(numbers[indexOfM0],0x40+0x08);
						if(indexOfM0 >= 10) {
							indexOfM0 = 0;//当分第一位到9后置0
							indexOfM1++;//当分位的第一位满9后，向第二位进一	
							writeData(numbers[indexOfM0],0x40+0x08);
							writeData(numbers[indexOfM1],0x40+0x07);
							if(indexOfM1 > 5) {
								indexOfM1 = 0; //当分第二位到5后置0
								indexOfH0++;//向时位进一
								writeData(numbers[indexOfM1],0x40+0x07);
								writeData(numbers[indexOfH0],0x40+0x05);
								if(indexOfH0 >= 10) {
									indexOfH0 = 0;//当时第一位到9后置0
									if(indexOfH0 ==4 && indexOfH1 == 2) {
										 indexOfH0 = 0;	 //当24小时时全部清零
										 indexOfH1 = 0;
									}else {
										indexOfH1++;//当时位的第一位满9后，向第二位进一	
										writeData(numbers[indexOfH0],0x40+0x05);
										writeData(numbers[indexOfH1],0x40+0x04);
									}						
								}
							}
						}		
					}
				}
			}

		}
	  }
	
	if(isTimer) { //如果启动计时功能 那么显示一套东西
		if(isStarted && !isStoped) { //如果开始了并且没有停止。我们就开始变化数字
			if(count2 >= 10) { //判断10ms;
			 indexOfTimerOfMs0++;
			 count2 = 0;
			 if(indexOfTimerOfMs0 >= 10) {
			 	indexOfTimerOfMs0 = 0;
				 indexOfTimerOfMs1++;
				if(indexOfTimerOfMs1 >= 10) { //判断时间都一秒
					indexOfTimerOfS0++;
					indexOfTimerOfMs1 = 0;
					if(indexOfTimerOfS0 >= 10) {
						indexOfTimerOfS0 = 0;//当秒第一位到9后置0
						indexOfTimerOfS1++;//当秒位的第一位满9后，向第二位进一
						if(indexOfTimerOfS1 > 5) {
							indexOfTimerOfS1 = 0; //当秒第二位到5后置0
							indexOfTimerOfM0++;//向分位进一
							if(indexOfTimerOfM0 >= 10) {
								indexOfTimerOfM0 = 0;//当分第一位到9后置0
								indexOfTimerOfM1++;//当分位的第一位满9后，向第二位进一	
								if(indexOfTimerOfM1 > 5) {
									indexOfTimerOfM1 = 0; //当分第二位到5后置0
									indexOfTimerOfH0++;//向时位进一
									if(indexOfTimerOfH0 >= 10) {
										indexOfTimerOfH0 = 0;//当时第一位到9后置0
										if(indexOfTimerOfH0 ==4 && indexOfH1 == 2) {
											 indexOfTimerOfH0 = 0;	 //当24小时时全部清零
											 indexOfTimerOfH1 = 0;
										}else {
											indexOfTimerOfH1++;//当时位的第一位满9后，向第二位进一	
										}						
									}
								}
							}		
						}
					}
				}
			}
	 	  }	
		}
		//updateLED(indexOfTimerOfMs0, indexOfTimerOfMs1, indexOfTimerOfS0, indexOfTimerOfS1, indexOfTimerOfM0, indexOfTimerOfM1, indexOfTimerOfH0, indexOfTimerOfH1);	

		//writeData(''+indexOfTimerOfH1,-1);
			//这里更新
	}else {	  //如果是时钟模式 则是显示时钟
	 	 //这里的实现可能就要用带参数的函数来做了
		//updateLED(indexOfMs0, indexOfMs1, indexOfS0, indexOfS1, indexOfM0, indexOfM1, indexOfH0, indexOfH1);
		//这里更新
	 }

	if(bPress) { //如果按键第一次被按下。那么开始计时
		temp1++;
	}								  
	temp2++;
	 
}


void keyInterruptHandle() {
	if(!key1 || !key2 || !key3) {
		bPress = 1;	
	}

	if(temp1 > 15) {	//当被按下的时间超过5ms才处理
		if(key1 == 0) { //表示第一个按键被按下	,这里规定为时
			if(isTimer) {
				 //按下开始，再按一次停止
				 if(isStarted) {	 
				 	isStoped = 1;
					isStarted = 0;
				 }else {
				 	isStarted = 1;
					isStoped = 0;
				 }
			}else if(indexOfH0 == 3 && indexOfH1 == 2) { //当时间是23时
				indexOfH0 = 0;	 //全部清零
				indexOfH1 = 0;
				}else if (indexOfH0 >= 9) {
					indexOfH0 = 0;
					indexOfH1++;	
				}else {
					indexOfH0++;
			}	
		   while(!key1);//等待按键被弹起
		}
		
	if(key2 == 0) { //表示第一个按键被按下 ，这里规定为分
		if(isTimer && isStoped) {
			 //	如果是timer 那么 计时清零
			 indexOfTimerOfMs0 = 0;
			 indexOfTimerOfMs1 = 0;
			 indexOfTimerOfS0 = 0;
			 indexOfTimerOfS1 = 0;
			 indexOfTimerOfM0 = 0;
			 indexOfTimerOfM1 = 0;
			 indexOfTimerOfH0 = 0;
			 indexOfTimerOfH0 = 0;

		}else if(indexOfM0 >= 9 && indexOfM1 >= 5) {
			indexOfM0 = 0;
			indexOfM1	= 0;
			indexOfH0++;
			}else if(indexOfM0 >= 9) {
				indexOfM0 = 0;
				indexOfM1++;
			}else {
				indexOfM0++;
		}							 
	   while(!key2);
	}
	
	//这里按键不能实现检测的主要原因是由于被写在了key2的if语句中间了...这里是一个bug。这个版本修正
	if(key3 == 0) { //表示第一个按键被按下	  这里规定为秒
		 //计时器代码 这个键用来充当模式切换功能
		 isTimer = !isTimer;
		 while(!key3);
	}

	temp1 = 0;
	}
}
