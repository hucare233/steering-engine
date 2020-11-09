/*
 * @Descripttion: 主控通信
 * @version: 第一版
 * @Author: 叮咚蛋
 * @Date: 2020-10-17 09:37:55
 * @LastEditors: 叮咚蛋
 * @LastEditTime: 2020-11-09 20:54:37
 * @FilePath: \F4舵机板\USER\INC\can1.h
 */
#ifndef __CAN1_H
#define __CAN1_H

#include "stm32f4xx_can.h"
#include "main.h"
#include "param.h"

void CAN1_Configuration(void);
void answer_master(CanRxMsg *rx_message);
void can_test(void);


#endif

