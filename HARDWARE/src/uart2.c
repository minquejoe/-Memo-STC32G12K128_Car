#include "uart2.h"
#include "timer.h"
#include "uart1.h"
#include "delay.h"
#include "Bluetooth.h"

void update_car(unsigned char temp);
void delay_with_BLE(unsigned char time);

volatile uint8 Flg=FALSE;
uint8 uart2temp=0;
unsigned char i;

/***************************************************************************
 * ��  �� : ����2��ʼ������
 * ��  �� : ��
 * ����ֵ : ��
��ע��������9600bps   ����24MHz
 **************************************************************************/
void Uart2_Init(void)
{
  S2CON = 0x50;		//8λ����,�ɱ䲨���ʣ��������н�����
  AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
  T2L = 0x8F;		  //�趨��ʱ��ֵ
  T2H = 0xFD;     //�趨��ʱ��ֵ

  AUXR |= 0x10;   //������ʱ��2

  IE2 |= 0x01;    //����2�жϴ�

  EA = 1;               //���жϴ�

  delay_ms(100);

}

/***************************************************************************
 * ��  �� : ����2�жϷ�����
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************/
void Uart2() interrupt 8 using 1
{
  IE2 &= 0xFE; 			               // ����2�жϹر�
  Flg=TRUE;                       //���յ�����,���ձ�ʶ����Ч
  if (S2CON & S2RI)                //���н��յ�ֹͣλ���м�ʱ��ʱ����λ��1
    {
      S2CON &= ~S2RI;              //���S2CON�Ĵ�����ӦS2RIλ����λ����������㣩
      uart2temp = S2BUF;
    }
  if (S2CON & S2TI)                //��ֹͣλ��ʼ����ʱ����λ��1
    {
      S2CON &= ~S2TI;   			     //���S2CON�Ĵ�����ӦS2TIλ����λ����������㣩
    }
  IE2 |= 0x01;                    // ����2�жϴ�
}

/**************************************************************************************
 * ��  �� : ���ڶ����պ�������
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************************/
void UART2_Rx_buff(void)
{
  if(Flg)      //��������ͨ�����ڱ����յ�
    {
      IE2 &= 0xFE; 			                     // ����2�жϹر�
      SendDataByUart1(uart2temp);            //�����ַ�


//      if(uart2temp==0x06)
//        {
//          PWM_Count+=5; //����
//        }
//      else
//        {
//          if(uart2temp==0x07)
//            {
//              PWM_Count-=5; //����
//            }
//          else
//            {
//              // 5 ��С��״̬��ͨ������ǰ����ٶȽ��м���õ�
//                         //��ȡ״̬
//            }
//        }

//      if(uart2temp<0x10)
//        {
//          Car_State_number=uart2temp;
//        }
//      else
//        {
//          PWM_Count = uart2temp-0x10;
//        }

//			update_car(uart2temp);


      IE2 |= 0x01;                           // ����2�жϴ�
      Flg=FALSE;                             //������ձ�ʶ��
    }
}

void update_car(unsigned char temp)
{
  // ����С��״̬
  if(temp<0x10)
    {
      Car_State_number=temp;
    }
  else
    {
      PWM_Count = temp-0x10;
    }
}

void delay_with_BLE(unsigned char time)
{
  i = 0;
  while(++i <= time)
    {
      delay_ms(1);
      UART2_Rx_buff();
      update_car(uart2temp);
    }
}














