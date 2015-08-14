#ifndef __USART_H
#define __USART_H

#define EN_USART1_RX 1

#include "stm32f10x.h"
#include "usart.h"

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* ���̳� ���ǰѴ���1�жϷ�����2�����ȼ�����Ϊ��2������� �ǵö���� EN_USART1_RX */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

void Usart_Init(void) {
	 //��ؽṹ�嶨��
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ʱ�ӳ�ʼ��
	/* Enable GPIO clock , ��Ϊ����ҲҪ�õ�IO��  PA9_TX PA10_RX*/
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
	//�ṹ���ʼ��
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* Configure USART Rx as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // ���������RX�ܽ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);		

	 /* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù��ܵ��������ģʽ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	// ���������TX�ܽ�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	

	 /* USART configuration */
	USART_Init(USART1, &USART_InitStructure);

	//���������Ѿ�OK�ˣ�ʣ�µľ����ж������ˡ�����ȥ���⺯��..����ֱ��ȥ����������

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
	
	//�������ж�
	NVIC_Configuration();//�жϳ�ʼ��
	//�򿪴����ж�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//�����жϺ���ûд,�жϺ���д�� stm32f10x_it.c ���棬�ж����ο� �����ļ�
	//���յ�һ������ʱ���ǵ���һ�������

	 //��ʼ��LED�ƹܽ�
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // ���������RX�ܽ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

}  

#endif
