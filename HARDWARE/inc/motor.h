#ifndef	__MOTOR_H
#define	__MOTOR_H 

#include <STC32G.H> 


#include "timer.h"  

void Motor_Init_Port(void); 
void Car_Forword(uint8 pwm_perent); 
void Car_Back(uint8 pwm_perent);
void Car_Turn_Left(uint8 pwm_perent);
void Car_Turn_Right(uint8 pwm_perent);
void Car_Stop(void);

// 2024/01/15 ��ӣ��˴�����ΪС���ƶ����򣬷�ת�䷽��
// Count_State_number  7  ���
// Count_State_number  8  �Һ�
void Car_Back_Left(uint8 pwm_perent);
void Car_Back_Right(uint8 pwm_perent);

// 2024/01/17 ��Ӱ������� �����ͷ/�ҵ�ͷ
// Count_State_number 9   �����ͷ
// Count_State_number 10  ���ҵ�ͷ
void Car_Pure_Left(uint8 pwm_perent);
void Car_Pure_Right(uint8 pwm_perent);

#endif 
