#include <STC32G.H>
#include <delay.h>
#include <sr04.h>

sbit Trig = P1^3;
sbit Echo = P4^0;

void Start_SR04_Module();
void Timer3Init();
void calc_dist();
void Counter_Number_DATA();

unsigned int S = 0;	// 距离

void Start_SR04_Module(void) {
	Trig=1;			                     //启动一次模块
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	_nop_(); 
	_nop_(); 
	_nop_(); 
	_nop_();
	Trig=0;
 }

 void Counter_Number_DATA(void){
	 Start_SR04_Module();	// 启动模块
	 while(!Echo);	// 当RX为0时等待
	 T3R = 1; // 开启计数
	 while(Echo);
	 T3R = 0;	// 关闭计数
	 calc_dist();
 }
 
void Timer3Init(void)
{
	// 参考 STC32G 手册 14.4.2
//	// 定时器0/1模式寄存器
//	T1_M1 = 0;
//	T1_M0 = 1;	// 定时器1 16位不自动重载
	
	T3_CT = 0;	// T3用作定时器
	T3CLKO = 0;	// T3时钟输出关闭
	
	T3L = 0x00;	//1T模式下初始装载值       
	T3H = 0x00;	//1T模式下初始装载值  
	
	// 参考 STC32G 手册 12.4.1
//	TF1 = 0;	//清除T1中断溢出标志位
//	ET1 = 1;	//使能定时器1的溢出中断允许位
//	TR1 = 1;	//定时器1开始计时 
}

unsigned int time = 0; 
void calc_dist(void)
{
	 time = T3H*256 + T3L;
	 T3H=0;
	 T3L=0;
	 S = (time*1.87)/100/2;     //算出来是CM  	
}