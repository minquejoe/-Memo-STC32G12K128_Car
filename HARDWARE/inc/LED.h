#ifndef __LED_H
#define __LED_H

#include <STC32G.H>

sbit LED_L = P0^5;	// �ض��� P3.4 ����
sbit LED_R = P3^4;	// �ض��� P0.5 ����

void LEDInit();

#endif