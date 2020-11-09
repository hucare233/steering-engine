/*
 * @Descripttion: 舵机参数初始化
 * @version: 第一版
 * @Author: 叮咚蛋
 * @Date: 2020-10-17 09:37:55
 * @LastEditors: 叮咚蛋
 * @LastEditTime: 2020-11-09 20:30:25
 * @FilePath: \F4舵机板\USER\SRC\param.c
 */
#include "param.h"

Temp_Datadef temp;

struct Engine_Datadef Steering_Engine[4];

/**
  *@brief 变量初始化函数
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

