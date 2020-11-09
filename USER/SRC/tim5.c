#include "tim5.h"

/**
  *@brief 定时器4初始化函数
	**/
void TIM5_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = arr;

	TIM_TimeBaseStructure.TIM_Prescaler = psc;

	TIM_TimeBaseStructure.TIM_ClockDivision = 0;

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;

	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	TIM_ClearFlag(TIM5, TIM_FLAG_Update);

	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM5, ENABLE);
}

/**
  *@brief 定时器4中断服务函数
	**/

void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

		pwm_out(&Steering_Engine[0]);

		pwm_out(&Steering_Engine[1]);

		pwm_out(&Steering_Engine[2]);

		//	pwm_out(&Steering_Engine[3]);
	}
}
