#include "timer.h"   
#include "motor.h" 
#include "Bluetooth.h" 
/*--------------------------------------------------------------*/
/* --- -----------------实验内容 -------------------------------*/
/* --- 1-了解STC-ISP工具生产延时函数方法 -----------------------*/
/* --- 2-掌握子函数的创建与调用---------------------------------*/
/* --- 实验平台：未来电子STC32核心板----------------------------*/
/* --- 视频学习：https://space.bilibili.com/494969171 ----------*/
/* --- QQ交流群：702805632 -------------------------------------*/
/* --- 参考资料：STC32实验室参考例程 ---------------------------*/
/*--------------------------------------------------------------*/ 
uint8 Time_Count_pwm = 0; 
uint8 PWM_Count = 20; //占空比
/***********************************************************
功能描述：定时器4初始化  //250微秒@24.000MHz
入口参数：无
返回值：无
************************************************************/
void Timer4Init(void)
{
	T4T3M &= 0xBF;                  //定时器4设置为定时方式
	T4T3M |= 0x20;                  //设置定时器4为1T模式
	T4L = 0x90;                     //1T模式下初始装载值 
	T4H = 0xE8;                     //1T模式下初始装载值 
	IE2  |=  (1<<6);	              //使能定时器4中断
	T4T3M |= 0x80;                  //打开定时器4
} 
/***********************************************************
功能描述：定时器4中断服务程序
入口参数：无
返回值：无       250us进入1次中断 
************************************************************/
void timer4_int (void) interrupt 20
{
	if(++Time_Count_pwm>100)
	 {
		  Time_Count_pwm=0;
	 } 
	 if(Time_Count_pwm>=PWM_Count)//PWM调速
	 {
		  Car_Stop(); //置为低电平
		 
	 }else{		 
		 
		 Adjust_Pwm_data(); //调节PWM
		 
	 } 
} 

/*********************************END FILE********************************************/	




































