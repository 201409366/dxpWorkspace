#include "stm32f10x.h"
#include "usart.h"
#include <stdio.h>

int main(void)
{	/*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */
//     char msg[] = "Hello STM32 !";
//	 int i = 0;
	Usart_Init();
	  /* Output a message on Hyperterminal using printf function */
	//这里我们只向外输出一个字符串就好
	
//	for(i = 0; i < 13; i++) {
//		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//		USART_SendData(USART1,msg[i]);		
//	
//	}
		printf("Hello STM32 !\n");  		
	while(1) {
//		GPIO_SetBits(GPIOA,GPIO_Pin_6);
//		
//		GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	}
	
	//还有中断问题没有解决
}

//#ifdef __GNUC__
//  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
//     set to 'Yes') calls __io_putchar() */
//  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif /* __GNUC__ */
//

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f) {
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
	USART_SendData(USART1,(unsigned char)ch);
	while (!(USART1->SR & USART_FLAG_TXE));

  /* Loop until the end of transmission */

  return (ch);
}
