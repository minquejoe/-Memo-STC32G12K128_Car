#ifndef __BEEP_H
#define __BEEP_H

#include <STC32G.H>

void BeepInit();
void Timer0Init();
void DealBeep(unsigned short int time);
void DealBeep_with_BLE(unsigned char time_div_10, unsigned char pitch_num);

#endif