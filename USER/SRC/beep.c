#include "beep.h"

void Beep_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	BEEP_OFF;
}

void Beep_Show(u8 num)
{
	for(int i=0; i<num; i++)
	{
		BEEP_ON;Delay_ms(100);
		BEEP_OFF;Delay_ms(100);
	}
}

//���Ʒ���
void Sound(u16 frq)
{
        u32 time;
        if(frq != 1000)//��ֹ��
        {
                time = 500000/((u32)frq);
                BEEP_ON;
                Delay_us(time);
                BEEP_OFF;
                Delay_us(time);
        }else
                Delay_us(1000);
}

//���ո�
void play_Music_1(void)
{
        //����         ��1  2   3   4   5   6   7  ��1  2   3   4   5   6   7  ��1    2   3     4    5    6    7  ������
        uc16 tone[] = {262,294,330,349,392,440,494,523,587,659,698,784,880,988,1047,1175,1319,1397,1568,1760,1967,1000};//��Ƶ���ݱ�
        //���          0   1   2   3   4   5   6   7   8   9   10  11  12  13  14   15   16    17   18   19   20  21
        
        //����
        u8 music[]={4,4,5,4,
                                                        7,6,21,
                                                        4,4,5,4,
                                                  8,7,21,
                                                        4,4,11,9,
                                                        7,6,5,21,
                                                        3,3,9,7,
                                                        8,7,21,
                                                        };
        //����
        u8 time[] = {2,2,4,4,        //ʱ��--2�������(100ms) 4����һ��(200ms) 8��������(400ms)
                                                         4,4,4, 
                                                         2,2,4,4,
                                                         4,4,4,
                                                         2,2,4,4,
                                                         4,4,4,4,
                                                         2,2,4,4,
                                                         4,4,4,
               };        
        u32 delayShow;
        u16 i,j;
        delayShow = 10;//���Ʋ��ſ���
        for(i=0;i<sizeof(music)/sizeof(music[0]);i++)//�Ÿ�
        {
                for(j=0;j<((u16)time[i])*tone[music[i]]/delayShow;j++)
                {
                        Sound((u32)tone[music[i]]);
                }        
        }
}

//�����������㻷�����
void play_Music_2(void)
{
        //���տ���    
                  // 0   1   2   3   4   5   6   7  ��1  ��2 ��3 ��4 ��5 ��6��7
    uc16 tone[] ={250,262,294,330,350,393,441,495,525,589,661,700,786,882,990}; //����        
    u8 music[]={5,5,6,5,8,7,5,5,6,5,9,8,5,5,12,10,8,7,6,11,
                  11,10,8,9,8,5,5,8,5,5,12,10,8,7,6,11,11,10,8,9,8    //��������
    };     
        u8 time[] = {1,2,2,2,2,4,1,2,2,2,2,4,1,2,2,2,1,4,
                      4,1,2,2,2,2,4,1,2,4,1,2,2,2,1,4, 4,1,2,2,2,2,4,4        //����ʱ��
        }; 
        u32 delayShow;
        u16 i,j;
        delayShow = 8;//�����ٶ�
        for(i=0;i<sizeof(music)/sizeof(music[0]);i++)//�Ÿ�
        {
                for(j=0;j<((u16)time[i])*tone[music[i]]/delayShow;j++)
                {
                        Sound((u32)tone[music[i]]);
                }        
        }
}

