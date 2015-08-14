#include "stm32f10x.h"

void GPIO_Configuration(void);
void Delay(__IO uint32_t nCount);

int main(void) {  //时钟什么的都在system_stm32f10x.c 初始化了
	
	GPIO_Configuration();	
	/*
	GPIO_SetBits(GPIOA,GPIO_Pin_6);	
	GPIO_SetBits(GPIOB,GPIO_Pin_6);	
	GPIO_SetBits(GPIOC,GPIO_Pin_6);	
	GPIO_SetBits(GPIOD,GPIO_Pin_6);	
	GPIO_SetBits(GPIOE,GPIO_Pin_6);	
	*/
	GPIO_SetBits(GPIOA,GPIO_Pin_4);	
	GPIO_SetBits(GPIOA,GPIO_Pin_5);	
	GPIO_SetBits(GPIOA,GPIO_Pin_6);	
	GPIO_SetBits(GPIOA,GPIO_Pin_7);	
	while (1);
}

void GPIO_Configuration(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* 设置LED对应的引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	/*
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	 */
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void Delay(__IO uint32_t nCount) {
	for(; nCount != 0; nCount--);
}
