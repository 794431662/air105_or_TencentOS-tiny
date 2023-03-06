#include <stdio.h>
#include "air105.h"
#include "sysc.h"
#include "delay.h"
#include "usart.h"

#include "cmsis_os.h"

uint32_t ms = 0;


void test_task(void *arg)
{
	for(;;)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14|GPIO_Pin_15);
		printf("test_task \n");
		osDelay(1000);
	}
}


void led_task(void *arg)
{
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Pin = GPIO_Pin_3;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Remap = GPIO_Remap_1;
	GPIO_Init(GPIOC, &gpio);
	for(;;)
	{
		GPIO_ToggleBits(GPIOC, GPIO_Pin_3);
		printf("led_task \n");
		osDelay(100);
	}
}





void Timer_Init(void)
{
	TIM_InitTypeDef TIM_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;

	SYSCTRL_APBPeriphClockCmd(SYSCTRL_APBPeriph_TIMM0, ENABLE);
	SYSCTRL_APBPeriphResetCmd(SYSCTRL_APBPeriph_TIMM0, ENABLE);

	//Timer
	TIM_InitStruct.TIM_Period = SYSCTRL->PCLK_1MS_VAL;
	TIM_InitStruct.TIMx = TIM_0;
	TIM_Init(TIMM0, &TIM_InitStruct);
	TIM_ITConfig(TIMM0, TIM_InitStruct.TIMx, ENABLE);

	//NVIC
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_0);

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannel = TIM0_0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIMM0, (TIM_NumTypeDef)TIM_0, ENABLE);
}






osThreadDef(test_task, osPriorityLow, 1, 900);
osThreadDef(led_task, osPriorityLow, 1, 900);


int main(void)
{
    SystemClock_Config_HSE();
    Delay_Init();
    USART_Init();
		Timer_Init();
	
    printf("USART Init\r\n");

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Remap = GPIO_Remap_1;
    GPIO_Init(GPIOD, &gpio);
    printf("GPIO Init\r\n");

		osKernelInitialize(); //TOS Tiny kernel initialize
		osThreadCreate(osThread(test_task), NULL);  
		osThreadCreate(osThread(led_task), NULL);	
		osKernelStart(); //Start TOS Tiny
	
    while (1)
    {
        
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

     /* Infinite loop */
    while (1)
    {
    }
}
#endif
