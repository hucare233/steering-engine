#include "main.h"
s32 pwm;
int main(void)

{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	param_Init(); //���ø��ֲ�����ֵ
	Beep_Configuration();
	//TIM4_Init(8999,8);//TIM4
	PWM_Init(temp.Engine_PWM_arr, temp.Engine_PWM_psc); //TIM2��TIM3
	LED_Configuration();
	TIM5_Init(11999, 7); //1 ms
	//u32 led0pwmval = 0;
	//u8 dir = 1;
	Beep_Show(2);
	//Sound(2);
	//play_Music_1();
	while (1)
	{
		Delay_ms(10);
		//              if(dir)led0pwmval++;//dir==1 led0pwmval ����
		//               else led0pwmval--; //dir==0 led0pwmval �ݼ�
		//               if(led0pwmval>8000)dir=0;//led0pwmval ���� 300 �󣬷���Ϊ�ݼ�
		//                   if(led0pwmval==0)dir=1; //led0pwmval �ݼ��� 0 �󣬷����Ϊ����
		//TIM_SetCompare2(TIM2, pwm); //�޸ıȽ�ֵ���޸�ռ�ձ�
		//(TIM3, 4400);
		//TIM_SetCompare2(TIM4, 4400);
		Led_Show();
	}
}
