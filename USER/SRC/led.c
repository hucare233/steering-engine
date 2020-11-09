/*
 * @Descripttion: led
 * @version: 第二版
 * @Author: 叮咚蛋
 * @Date: 2020-10-17 14:52:41
 * @LastEditors: 叮咚蛋
 * @LastEditTime: 2020-11-06 20:36:12
 * @FilePath: \MotoPro\USER\SRC\led.c
 */
#include "led.h"
#include "delay.h"
void LED_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	LED_RED_OFF;
	LED_YELLOW_OFF;
	LED_BLUE_OFF;
	LED_GREEN_OFF;
}

/**
 * @author: 叮咚蛋
 * @brief: 流水灯
 */

void Led_Show(void)
{
	LED_RED_ON;
	Delay_ms(200);
	LED_YELLOW_ON;
	Delay_ms(200);
	LED_BLUE_ON;
	Delay_ms(200);
	LED_GREEN_ON;
	Delay_ms(200);
	LED_RED_OFF;
	Delay_ms(200);
	LED_YELLOW_OFF;
	Delay_ms(200);
	LED_BLUE_OFF;
	Delay_ms(200);
	LED_GREEN_OFF;
	Delay_ms(200);
}
