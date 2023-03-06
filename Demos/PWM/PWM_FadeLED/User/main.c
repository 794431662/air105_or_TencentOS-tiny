#include <stdio.h>
#include "air105.h"
#include "delay.h"
#include "sysc.h"
#include "usart.h"
#include "timer.h"

#define STEP   1000

int main(void)
{
    uint32_t direction = 0, period = SYSCTRL->PCLK_1MS_VAL, high_period = SYSCTRL->PCLK_1MS_VAL;
    SystemClock_Config_HSE();
    Delay_Init();
    USART_Init();
    printf("USART Init\r\n");

    TimerPWM_Init();
    printf("Timer PWM Init\r\n");

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Remap = GPIO_Remap_2;
    GPIO_Init(GPIOB, &gpio);
    printf("GPIO Init\r\n");

    while (1)
    {
        if (direction)
        {
            high_period += STEP;
            if (high_period > period - STEP)
            {
                direction = 0;
            }
        }
        else
        {
            high_period -= STEP;
            if (high_period < STEP)
            {
                direction = 1;
            }
        }
        printf("PWM %d / %d\r\n", high_period, period);
        TIM_SetPWMPeriod(TIMM0, TIM_4, high_period, period - high_period);
        TIM_SetPWMPeriod(TIMM0, TIM_5, period - high_period, high_period);
        Delay_ms(50);
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
