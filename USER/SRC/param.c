/*
 * @Descripttion: ���������ʼ��
 * @version: ��һ��
 * @Author: ���˵�
 * @Date: 2020-10-17 09:37:55
 * @LastEditors: ���˵�
 * @LastEditTime: 2020-11-09 20:30:25
 * @FilePath: \F4�����\USER\SRC\param.c
 */
#include "param.h"

Temp_Datadef temp;

struct Engine_Datadef Steering_Engine[4];

/**
  *@brief ������ʼ������
	**/
void param_Init(void)
{	
	temp.Engine_PWM_arr =8999;
	
	temp.Engine_PWM_psc =159;
	
	
	Steering_Engine[0].port=PB3;
	Steering_Engine[0].Move_Flag=0;
	Steering_Engine[0].Move_Ratio =1;
	

	Steering_Engine[1].port=PB4;
	Steering_Engine[1].Move_Flag=0;
	Steering_Engine[1].Move_Ratio =0;
	
	
	Steering_Engine[2].port=PB7;
	Steering_Engine[2].Move_Flag=0;
	Steering_Engine[2].Move_Ratio =0;
	
	
}

