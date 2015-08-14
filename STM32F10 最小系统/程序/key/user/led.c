#ifndef __LED_H
#define __LED_H	

#include "stm32f10x.h"
#include "led.h"

void LED_Init(void)
{
	//led�����˰��������PA 4,5��6,7
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//	 APB2�����ϵ�ʱ��ʹ��	  RCC_APB2Periph_GPIOF ʹ�ܵĹܽ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/* ����LED��Ӧ������ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//����Ҫ��ʼ���Ĺܽ�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //���ƽ������
	
	/* һ�������漸��Ƶ�ʹ�ѡ��
	GPIO_Speed_10MHz
	GPIO_Speed_2MHz, 
	GPIO_Speed_50MHz
	*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//����IO��ģʽ,һ����8��.
	/*
	ģ������ 
	GPIO_Mode_AIN = 0x0,
	
	��������
	GPIO_Mode_IN_FLOATING = 0x04,
	
	����������
	GPIO_Mode_IPD = 0x28,
	
	����������
	GPIO_Mode_IPU = 0x48,
	
	��ʾ������Ӧ�ܽ�ΪGPIO��©���(��˫��IO) 
	GPIO_Mode_Out_OD = 0x14,
	
	ͨ���������ģʽ
	GPIO_Mode_Out_PP = 0x10,
	
	��ʾ������Ӧ�ܽ�Ϊ���ù��ܵĿ�©��� 
	GPIO_Mode_AF_OD = 0x1C,
	
	���ù��ܵ��������ģʽ 
	GPIO_Mode_AF_PP = 0x18
	*/	
	
	//��ʼ����ֵ���ú���֮�󣬾ͳ�ʼ��IO
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
#endif
