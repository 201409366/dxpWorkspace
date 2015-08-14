#ifndef __LED_H
#define __LED_H	

#include "stm32f10x.h"
#include "led.h"

void LED_Init(void)
{
	//led接在了板子上面的PA 4,5，6,7
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//	 APB2总线上的时钟使能	  RCC_APB2Periph_GPIOF 使能的管脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* 设置LED对应的引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//设置要初始化的管脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //输出平率设置
	
	/* 一共有下面几种频率供选择
	GPIO_Speed_10MHz
	GPIO_Speed_2MHz, 
	GPIO_Speed_50MHz
	*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//设置IO的模式,一共有8中.
	/*
	模拟输入 
	GPIO_Mode_AIN = 0x0,
	
	浮空输入
	GPIO_Mode_IN_FLOATING = 0x04,
	
	带下拉输入
	GPIO_Mode_IPD = 0x28,
	
	带上拉输入
	GPIO_Mode_IPU = 0x48,
	
	表示配置相应管脚为GPIO开漏输出(真双向IO) 
	GPIO_Mode_Out_OD = 0x14,
	
	通用推挽输出模式
	GPIO_Mode_Out_PP = 0x10,
	
	表示配置相应管脚为复用功能的开漏输出 
	GPIO_Mode_AF_OD = 0x1C,
	
	复用功能的推挽输出模式 
	GPIO_Mode_AF_PP = 0x18
	*/	
	
	//初始化的值设置好了之后，就初始化IO
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
#endif
