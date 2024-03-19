#include "motor.h"
#include "delay.h"
#include "motor.h"
#include "delay.h"
#include "timer.h"
#include "LED.h"

/***************************����˿ڶ���*************************************/
sbit LH_B=P2^0;
sbit LH_F=P2^1;

sbit RH_F=P2^2;
sbit RH_B=P2^3;

sbit RQ_F=P1^4;
sbit RQ_B=P1^5;

sbit LQ_F=P1^6;
sbit LQ_B=P1^7;

//========================================================================
// ����: void Motor_Init_Port(void)
// ����: ��ʱ������
// ����: ��ʼ������˿�
// ����: none.
// �汾: VER1.0
// ����: 2022-9-24
// ��ע:
//========================================================================
void Motor_Init_Port(void)
{
  P2M0 |= 0x0F;
  P2M1 |= 0x00;

  P1M0 |= 0xF0;
  P1M1 |= 0x00;

  delay_ms(50); //�ȴ��ȶ�
}
//========================================================================
// ����: void Car_Forword(void)
// ����: ǰ��
// ����:  pwm_perent ռ�ձȰٷֱ�
// ����: none.
// �汾: VER1.0
// ����: 2022-9-24
// ��ע:
//========================================================================
void Car_Forword(uint8 pwm_perent)//ǰ��
{

  PWM_Count = pwm_perent;

  LH_B=0;
  LH_F=1;

  RH_F=0;
  RH_B=1;

  RQ_F=0;
  RQ_B=1;

  LQ_F=0;
  LQ_B=1;
	
	LED_L = 0;
	LED_R = 0;
	
}
//========================================================================
// ����: void Car_Back(void)
// ����: ����
// ����: pwm_perent ռ�ձȰٷֱ�
// ����: none.
// �汾: VER1.0
// ����: 2022-9-24
// ��ע:
//========================================================================
void Car_Back(uint8 pwm_perent)//����
{
  PWM_Count = pwm_perent;

  LH_B=1;
  LH_F=0;

  LQ_F=1;
  LQ_B=0;

  RH_F=1;
  RH_B=0;

  RQ_F=1;
  RQ_B=0;

	LED_L = 1;
	LED_R = 1;

}
//========================================================================
// ����: void Car_Turn_Left(void)
// ����: ��ת
// ����: pwm_perent ռ�ձȰٷֱ�
// ����: none.
// �汾: VER1.0
// ����: 2022-9-24
// ��ע:
//========================================================================
void Car_Turn_Left(uint8 pwm_perent)//��ת
{
  PWM_Count = pwm_perent;
	
	LQ_F=0;
  LQ_B=1;

  LH_B=1;
  LH_F=0;

  RH_F=0;
  RH_B=1;

  RQ_F=0;
  RQ_B=1;
	
	LED_L = 1;
	LED_R = 0;

}
//========================================================================
// ����: void Car_Turn_Right(void)
// ����: ��ת
// ����: pwm_perent ռ�ձȰٷֱ�
// ����: none.
// �汾: VER1.0
// ����: 2022-9-24
// ��ע:
//========================================================================
void Car_Turn_Right(uint8 pwm_perent)//��ת
{
  PWM_Count = pwm_perent;

  LQ_F=0;
  LQ_B=1;

  LH_B=0;
  LH_F=1;

  RH_F=0;
  RH_B=1;

  RQ_F=1;
  RQ_B=0;
	
	LED_L = 0;
	LED_R = 1;

}
//========================================================================
// ����: void Car_Stop(void)
// ����: ��ת
// ����: pwm_perent ռ�ձȰٷֱ�
// ����: none.
// �汾: VER1.0
// ����: 2022-9-24
// ��ע:
//========================================================================
void Car_Stop(void)//ֹͣ
{

  LH_B=0;
  LH_F=0;

  RH_F=0;
  RH_B=0;

  RQ_F=0;
  RQ_B=0;

  LQ_F=0;
  LQ_B=0;
	
	LED_L = 0;
	LED_R = 0;
}

// 2024/01/15 ��ӣ��˴�����ΪС���ƶ����򣬷�ת�䷽��
// Count_State_number  7  ���
// Count_State_number  8  �Һ�

void Car_Back_Left(uint8 pwm_perent)//����
{
  PWM_Count = pwm_perent;

	LH_B=1;
  LH_F=0;

  LQ_F=1;
  LQ_B=0;

  RH_F=1;
  RH_B=0;

  RQ_F=0;
  RQ_B=1;
	
	LED_L = 0;
	LED_R = 1;

}

void Car_Back_Right(uint8 pwm_perent)//����
{
  PWM_Count = pwm_perent;

	LH_B=0;
  LH_F=1;

  LQ_F=1;
  LQ_B=0;

  RH_F=1;
  RH_B=0;

  RQ_F=1;
  RQ_B=0;
	
	LED_L = 1;
	LED_R = 0;

}

// 2024/01/17 ��Ӱ������� �����ͷ/�ҵ�ͷ
// Count_State_number 9   �����ͷ
// Count_State_number 10  ���ҵ�ͷ
void Car_Pure_Left(uint8 pwm_perent)// ����ת
{
  PWM_Count = pwm_perent;
	
	LQ_F=1;
  LQ_B=0;

  LH_B=1;
  LH_F=0;

  RH_F=0;
  RH_B=1;

  RQ_F=0;
  RQ_B=1;
	
	LED_L = 1;
	LED_R = 0;

}

void Car_Pure_Right(uint8 pwm_perent)// ����ת
{
  PWM_Count = pwm_perent;
	
  LQ_F=0;
  LQ_B=1;

  LH_B=0;
  LH_F=1;

  RH_F=1;
  RH_B=0;

  RQ_F=1;
  RQ_B=0;
	
	LED_L = 0;
	LED_R = 1;

}



























































