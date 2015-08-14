#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "delay.h"

int main(void)
{
	u8 led0 = 0, led1 = 0, led2 = 0, led3 = 0, t;
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
	delay_init(72);
	LED_Init();
	KEY_Init();
		
	while(1) {
		t = KEY_Scan();//得到键值
		
		if(t) {			//判断键值然后点亮相应的灯			   
			switch(t) {				 
				case 1:
					if(led0) {	
						GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
					}else {
						GPIO_SetBits(GPIOA,GPIO_Pin_4);
					}
					led0 = !led0;
					break;
				case 2:
					if(led1) {
						GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
					}else {
						GPIO_SetBits(GPIOA,GPIO_Pin_5);
					}
					led1 = !led1;
					break;
				case 3:				
					if(led2) {
						GPIO_ResetBits(GPIOA,GPIO_Pin_6);	
					}else {
						GPIO_SetBits(GPIOA,GPIO_Pin_6);
					}
					led2 = !led2;
					break;
			
				case 4:				
						if(led3) {
							GPIO_ResetBits(GPIOA,GPIO_Pin_7);	
						}else {
							GPIO_SetBits(GPIOA,GPIO_Pin_7);
						}
						led3 = !led3;
						break;
				}
			}
			else 
				delay_ms(10); 	
		}
}
