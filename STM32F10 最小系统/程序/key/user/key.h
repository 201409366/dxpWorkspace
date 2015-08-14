#include "stm32f10x.h"

//led接在了板子上面的PF6,7，8,9
/*
在main函数里面用 
GPIO_SetBits(GPIOF,GPIO_Pin_6);
GPIO_ResetBits(GPIOF,GPIO_Pin_6);
两个库函数控制灯的亮灭 
*/

//记得后面别加; 不然会错。。。。。好难查 ...函数的参数不要传错了  GPIO_Pin_13 而不是13。。。。
#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)   //PC13
#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)	//PA8
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)	//PA0  WK_UP
#define KEY3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)	//PA0  WK_UP
	
void KEY_Init(void);//IO初始化
u8 KEY_Scan(void);  //按键扫描函数	

/*
操作方式：1.首先初始化 2.读取键值 
	这里是把IO口做输入用          
*/
