#include "stm32f10x.h"

//led�����˰��������PF6,7��8,9
/*
��main���������� 
GPIO_SetBits(GPIOF,GPIO_Pin_6);
GPIO_ResetBits(GPIOF,GPIO_Pin_6);
�����⺯�����ƵƵ����� 
*/

//�ǵú�����; ��Ȼ��������������Ѳ� ...�����Ĳ�����Ҫ������  GPIO_Pin_13 ������13��������
#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)   //PC13
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)	//PA8
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)	//PA0  WK_UP
#define KEY3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)	//PA0  WK_UP
	
void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(void);  //����ɨ�躯��	

/*
������ʽ��1.���ȳ�ʼ�� 2.��ȡ��ֵ 
	�����ǰ�IO����������          
*/
