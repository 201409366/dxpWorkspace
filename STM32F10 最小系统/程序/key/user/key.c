#ifndef __KEY_H
#define __KEY_H	

#include "stm32f10x.h"
#include "delay.h"
#include "key.h"

//按键初始化函数
//特别注意：在该函数之后，JTAG将无法使用（SWD也无法使用）
//如果想JTAG仿真，可以屏蔽该函数。
//PA0.8.PC13 设置成输入
void KEY_Init(void)
{
	//按键接在了 PC3 PA0 PA2 PA3 	
	GPIO_InitTypeDef GPIO_InitStructure;

	//	 APB2总线上的时钟使能	  RCC_APB2Periph_GPIOF 使能的管脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* 设置PA8 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3;//设置要初始化的管脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出平率设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//带上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);

			/* 设置PC13 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//设置要初始化的管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//带下拉输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
} 
//按键处理函数
//返回按键值
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2!!
u8 KEY_Scan(void)
{	 
	static u8 key_up = 1;//按键按松开标志
	
	if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || KEY3 == 1)) {
		delay_ms(10);//去抖动 
		key_up = 0;
		
		if(KEY0 == 0) {
			return 1;
		}
		else if(KEY1 == 0) {
			return 2;
		}
		else if(KEY2 == 0) {
			return 3;
		}
		else if(KEY3 == 1) {
			return 4;
		}
	}else if(KEY0==1&&KEY1==1&&KEY2==1 &&KEY3==0) {
		key_up = 1; 	    
	}
	
	return 0;// 无按键按下
}
#endif
