/*
 * @Descripttion: 主控
 * @version: 第一版
 * @Author: 叮咚蛋
 * @Date: 2020-10-17 09:37:55
 * @LastEditors: 叮咚蛋
 * @LastEditTime: 2020-11-09 20:56:07
 * @FilePath: \F4舵机板\USER\SRC\can1.c
 */
#include "can1.h"

void CAN1_Configuration(void)
{
    CAN_InitTypeDef CAN_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;         //非时间触发通道模式
    CAN_InitStructure.CAN_ABOM = DISABLE;         //软件对CAN_MCR寄存器的INRQ位置1，随后清0，一旦监测到128次连续11位的隐性位，就退出离线状态
    CAN_InitStructure.CAN_AWUM = DISABLE;         //睡眠模式由软件唤醒
    CAN_InitStructure.CAN_NART = DISABLE;         //禁止报文自动发送，即只发送一次，无论结果如何
    CAN_InitStructure.CAN_RFLM = DISABLE;         //报文不锁定，新的覆盖旧的
    CAN_InitStructure.CAN_TXFP = DISABLE;         //发送FIFO的优先级由标识符决定
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; // CAN硬件工作在正常模式

    /* Seting BaudRate */
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq; //重新同步跳跃宽度为一个时间单位
    CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq; //时间段1占用8个时间单位
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq; //时间段2占用7个时间单位
    CAN_InitStructure.CAN_Prescaler = 3;     //分频系数（Fdiv）
    CAN_Init(CAN1, &CAN_InitStructure);      //初始化CAN1

    CAN_FilterInitStructure.CAN_FilterNumber = 0; //屏蔽位模式
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = ((ID_Self << 3) & 0xFFFF0000) >> 16;
    CAN_FilterInitStructure.CAN_FilterIdLow = (ID_Self << 3) & 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = (0xFFFF00 << 3) >> 16;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = (0xFFFF << 3) & 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

void CAN1_RX0_IRQHandler(void)
{
    if (CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
    {
        CanRxMsg rx_message;

        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);

        CAN_Receive(CAN1, CAN_FIFO0, &rx_message);

        if ((rx_message.IDE == CAN_Id_Extended) && (rx_message.RTR == CAN_RTR_Data))
        {
            if (rx_message.Data[0] == 0x00) //广播帧
            {
                if (rx_message.Data[1] == 'C' && rx_message.Data[2] == 'W' && rx_message.Data[3] == 'H' && rx_message.Data[4] == 'U') //自检
                {
                    answer_master(&rx_message);
                }
            }
            if (rx_message.Data[0] == 0x04 && rx_message.Data[1] == 'S' + 0x40 && rx_message.Data[2] == 'N')
            {
                answer_master(&rx_message);

                Steering_Engine[rx_message.Data[3]].Move_Flag = 1;

                Steering_Engine[rx_message.Data[3]].Move_Flag = 1;
            }
            if (rx_message.Data[0] == 0x04 && rx_message.Data[1] == 'E' + 0x40 && rx_message.Data[2] == 'F')
            {
                answer_master(&rx_message);

                Steering_Engine[rx_message.Data[3]].Move_Flag = 1;

                Steering_Engine[rx_message.Data[3]].Move_Ratio = 0;
            }
            if (rx_message.Data[0] == 0x04 && rx_message.Data[1] == 'F' + 0x40 && rx_message.Data[2] == 'T')  //反馈
            {
                rx_message.Data[4] = Steering_Engine[1].Move_Ratio;

                rx_message.Data[5] = Steering_Engine[2].Move_Ratio;
                answer_master(&rx_message);
            }
            if (rx_message.Data[0] == 'C' && rx_message.Data[1] == 'Y')
            {
                answer_master(&rx_message);

                Steering_Engine[rx_message.Data[2]].Move_Flag = 1;

                if (Steering_Engine[rx_message.Data[2]].Move_Ratio == 1)
                    Steering_Engine[rx_message.Data[2]].Move_Ratio = 0;

                else if (Steering_Engine[rx_message.Data[2]].Move_Ratio == 0)
                    Steering_Engine[rx_message.Data[2]].Move_Ratio = 1;
            }
        }
    }
}

/**
  *@brief CAN报文应答
  */
void answer_master(CanRxMsg *rx_message)
{
    CanTxMsg tx_message;

    tx_message.ExtId = ID_Back;

    tx_message.RTR = CAN_RTR_Data;

    tx_message.IDE = CAN_Id_Extended;

    tx_message.DLC = rx_message->DLC;

    tx_message.Data[0] = rx_message->Data[0] + 0x40;

    tx_message.Data[1] = rx_message->Data[1];

    tx_message.Data[2] = rx_message->Data[2];

    tx_message.Data[3] = rx_message->Data[3];

    tx_message.Data[4] = rx_message->Data[4];

    tx_message.Data[5] = rx_message->Data[5];

    tx_message.Data[6] = rx_message->Data[6];

    tx_message.Data[7] = rx_message->Data[7];

    CAN_Transmit(CAN1, &tx_message);
}
/**
  *@brief CAN检测
  */
void can_test(void)
{
    CanTxMsg tx_message;

    tx_message.StdId = 0x00;

    tx_message.RTR = CAN_RTR_Data;

    tx_message.IDE = CAN_Id_Standard;

    tx_message.DLC = 4;

    tx_message.Data[0] = 'T';

    tx_message.Data[1] = 'E';

    tx_message.Data[2] = 'S';

    tx_message.Data[3] = 'T';

    CAN_Transmit(CAN1, &tx_message);
}
