#ifndef __LED_H
#define __LED_H

#include <STC32G.H>

sbit LED_L = P0^5;	// 重定义 P3.4 引脚
sbit LED_R = P3^4;	// 重定义 P0.5 引脚

void LEDInit();

#endif