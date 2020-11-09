/*
 * @Descripttion: 
 * @version: ��һ��
 * @Author: ���˵�
 * @Date: 2020-10-17 09:37:55
 * @LastEditors: ���˵�
 * @LastEditTime: 2020-11-09 20:30:57
 * @FilePath: \F4�����\USER\INC\param.h
 */
#ifndef _PARAM_H_

#define _PARAM_H_

#include "stm32f4xx.h"

/**
  *@brief ������ѡ��
	*/
	
#define board_test 0//��������

/**
  *@brief ����ID
	*/
#define ID_Self 0x00010400

#define ID_Back 0x00040101

#define broadcast_ID 0x00010000

/**
  *@brief IO�ں궨��
	*/
#define PB3 3

#define PB4 4

#define PB7 7
/**��������ṹ��**/
struct Engine_Datadef
{
	u8 port;
	
	volatile u8 Start_Flag;
	
	float Start_Ratio;
	
	volatile u8 Move_Flag;
	
	float Move_Ratio;
	
	volatile u8 End_Flag;
	
	float End_Ratio;
};

/** �����ʱ����**/
typedef struct
{
	u16 Engine_PWM_arr;//pwm�Ƚ�ֵ����������899����ͨ���������������pwmռ�ձ�
	
	u16 Engine_PWM_psc;
	
 }Temp_Datadef;

void param_Init(void);

extern Temp_Datadef temp;
 
extern struct Engine_Datadef Steering_Engine[4];

#endif
