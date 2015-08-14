#ifndef __USART_H
#define __USART_H

#define EN_USART1_RX 1

#include "stm32f10x.h"
#include "usart.h"

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* 按教程 我们把串口1中断放在组2，优先级设置为组2里面最低 记得定义宏 EN_USART1_RX */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

void Usart_Init(void) {
	 //相关结构体定义
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//时钟初始化
	/* Enable GPIO clock , 因为串口也要用到IO口  PA9_TX PA10_RX*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* Enable UART clock  RCC_APB2Periph_USART1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* USARTx configured as follow:
	    - BaudRate = 9600 baud  
	    - Word Length = 8 Bits
	    - One Stop Bit
	    - No parity
	    - Hardware flow control disabled (RTS and CTS signals)
	    - Receive and transmit enabled
	*/
	//结构体初始化
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // 板子上面的RX管脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);		

	 /* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能的推挽输出模式 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	// 板子上面的TX管脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	

	 /* USART configuration */
	USART_Init(USART1, &USART_InitStructure);

	//基本设置已经OK了，剩下的就是中断设置了。还得去读库函数..等下直接去例子里面找

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
	
	//允许串口中断
	NVIC_Configuration();//中断初始化
	//打开串口中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//还有中断函数没写,中断函数写在 stm32f10x_it.c 里面，中断名参考 启动文件
	//当收到一个数据时我们点亮一个数码管

	 //初始化LED灯管脚
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // 板子上面的RX管脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

}  

#endif
