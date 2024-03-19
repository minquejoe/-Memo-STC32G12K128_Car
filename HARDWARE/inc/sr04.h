#ifndef __SR04_H
#define __SR04_H

#include <STC32G.H>

extern unsigned int S; 

void Start_SR04_Module();
void Timer3Init();
void calc_dist();
void Counter_Number_DATA();

#endif