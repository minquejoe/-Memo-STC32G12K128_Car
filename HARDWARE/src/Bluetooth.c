#include "Bluetooth.h"
#include "motor.h"
#include "LED.h"
#include "beep.h"

uint8 Car_State_number = 0; //С��״ֵ̬ ,�����������ݻ�ȡ

//========================================================================
// ����: void Calculation_Data(void)
// ����: ����״̬��ֵȥ����PWM����
// ����:
// ����: Count_State_number  1  ǰ��
// ����: Count_State_number  2  ����
// ����: Count_State_number  3  ��ת
// ����: Count_State_number  4  ��ת
// ����: Count_State_number  5  ֹͣ
// �汾: VER1.0
// ����: 2022-9-24
// ��ע:
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

    // 2024/01/15 ��ӣ��˴�����ΪС���ƶ����򣬷�ת�䷽��
    // Count_State_number  7  ���
    // Count_State_number  8  �Һ�
    case 7:
      Car_Back_Left(PWM_Count);
      break;
    case 8:
      Car_Back_Right(PWM_Count);
      break;

    // 2024/01/17 ��Ӱ������� �����ͷ/�ҵ�ͷ
    // Count_State_number 9   �����ͷ
    // Count_State_number 10  ���ҵ�ͷ
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





























