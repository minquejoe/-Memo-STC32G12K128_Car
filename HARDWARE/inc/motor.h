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

// 2024/01/15 添加，此处方向为小车移动方向，非转弯方向
// Count_State_number  7  左后
// Count_State_number  8  右后
void Car_Back_Left(uint8 pwm_perent);
void Car_Back_Right(uint8 pwm_perent);

// 2024/01/17 添加按键控制 纯左掉头/右掉头
// Count_State_number 9   纯左掉头
// Count_State_number 10  纯右掉头
void Car_Pure_Left(uint8 pwm_perent);
void Car_Pure_Right(uint8 pwm_perent);

#endif 
