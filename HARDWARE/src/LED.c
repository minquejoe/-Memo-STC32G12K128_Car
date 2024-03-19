#include <STC32G.H>
#include "LED.h"

sbit LED_L = P0^5;	// �ض��� P3.4 ����
sbit LED_R = P3^4;	// �ض��� P0.5 ����

void LEDInit()
{
	P0M0 |= 0x20;	// 0010 0000 ����P0^5��Ϊ�������ģʽ
	P0M1 |= 0x00;
	
	P3M0 |= 0x10;	// 0001 0000 ����P3^4��Ϊ�������ģʽ
	P3M1 |= 0x00;
	
	LED_L = 0;
	LED_R = 0;
}