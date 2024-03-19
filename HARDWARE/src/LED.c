#include <STC32G.H>
#include "LED.h"

sbit LED_L = P0^5;	// 重定义 P3.4 引脚
sbit LED_R = P3^4;	// 重定义 P0.5 引脚

void LEDInit()
{
	P0M0 |= 0x20;	// 0010 0000 配置P0^5口为推挽输出模式
	P0M1 |= 0x00;
	
	P3M0 |= 0x10;	// 0001 0000 配置P3^4口为推挽输出模式
	P3M1 |= 0x00;
	
	LED_L = 0;
	LED_R = 0;
}