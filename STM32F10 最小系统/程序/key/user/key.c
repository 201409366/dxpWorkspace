#ifndef __KEY_H
#define __KEY_H	

#include "stm32f10x.h"
#include "delay.h"
#include "key.h"

//������ʼ������
//�ر�ע�⣺�ڸú���֮��JTAG���޷�ʹ�ã�SWDҲ�޷�ʹ�ã�
//�����JTAG���棬�������θú�����
//PA0.8.PC13 ���ó�����
void KEY_Init(void)
{
	//���������� PC3 PA0 PA2 PA3 	
	GPIO_InitTypeDef GPIO_InitStructure;

	//	 APB2�����ϵ�ʱ��ʹ��	  RCC_APB2Periph_GPIOF ʹ�ܵĹܽ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* ����PA8 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3;//����Ҫ��ʼ���Ĺܽ�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //���ƽ������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

			/* ����PC13 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//����Ҫ��ʼ���Ĺܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
} 
//����������
//���ذ���ֵ
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2!!
u8 KEY_Scan(void)
{	 
	static u8 key_up = 1;//�������ɿ���־
	
	if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || KEY3 == 1)) {
		delay_ms(10);//ȥ���� 
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
	
	return 0;// �ް�������
}
#endif
