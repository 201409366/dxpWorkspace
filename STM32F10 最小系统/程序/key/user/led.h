//led接在了板子上面的PF6,7，8,9
/*
在main函数里面用 
GPIO_SetBits(GPIOF,GPIO_Pin_6);
GPIO_ResetBits(GPIOF,GPIO_Pin_6);
两个库函数控制灯的亮灭 
*/	
void LED_Init(void);
