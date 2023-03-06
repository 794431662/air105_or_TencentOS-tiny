#include "air105.h"
#include "timer.h"

void TimerPWM_Init(void)
{
    TIM_PWMInitTypeDef TIM_PWMInitStruct;

    SYSCTRL_APBPeriphClockCmd(SYSCTRL_APBPeriph_TIMM0, ENABLE);
    SYSCTRL_APBPeriphResetCmd(SYSCTRL_APBPeriph_TIMM0, ENABLE);
    
    //Timer4 -> PWM4
    TIM_PWMInitStruct.TIM_HighLevelPeriod = SYSCTRL->PCLK_1MS_VAL;
    TIM_PWMInitStruct.TIM_HighLevelPeriod = 0;
    TIM_PWMInitStruct.TIMx = TIM_4;
    TIM_PWMInit(TIMM0, &TIM_PWMInitStruct);
    TIM_Cmd(TIMM0, TIM_PWMInitStruct.TIMx, ENABLE);

    //Timer5 -> PWM5
    TIM_PWMInitStruct.TIMx = TIM_5;
    TIM_PWMInit(TIMM0, &TIM_PWMInitStruct);
    TIM_Cmd(TIMM0, TIM_PWMInitStruct.TIMx, ENABLE);
}
