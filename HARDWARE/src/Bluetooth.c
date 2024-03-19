#include "Bluetooth.h"
#include "motor.h"
#include "LED.h"
#include "beep.h"

uint8 Car_State_number = 0; //小车状态值 ,蓝牙发送数据获取

//========================================================================
// 函数: void Calculation_Data(void)
// 描述: 根据状态数值去进行PWM调节
// 参数:
// 返回: Count_State_number  1  前进
// 返回: Count_State_number  2  后退
// 返回: Count_State_number  3  左转
// 返回: Count_State_number  4  右转
// 返回: Count_State_number  5  停止
// 版本: VER1.0
// 日期: 2022-9-24
// 备注:
//========================================================================
void Adjust_Pwm_data(void)
{
  switch(Car_State_number)
    {
    case 1:
      Car_Forword(PWM_Count);
      break;
    case 2:
      Car_Back(PWM_Count);
      break;
    case 3:
      Car_Turn_Left(PWM_Count);
      break;
    case 4:
      Car_Turn_Right(PWM_Count);
      break;
    case 5:
      Car_Stop();
      break;

    // 2024/01/15 添加，此处方向为小车移动方向，非转弯方向
    // Count_State_number  7  左后
    // Count_State_number  8  右后
    case 7:
      Car_Back_Left(PWM_Count);
      break;
    case 8:
      Car_Back_Right(PWM_Count);
      break;

    // 2024/01/17 添加按键控制 纯左掉头/右掉头
    // Count_State_number 9   纯左掉头
    // Count_State_number 10  纯右掉头
    case 9:
      Car_Pure_Left(PWM_Count);
      break;
    case 10:
      Car_Pure_Right(PWM_Count);
      break;

    default :
      Car_Stop();
      break;
    }
}





























