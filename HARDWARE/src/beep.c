#include <STC32G.H>
#include <stdlib.h>
#include <beep.h>
#include <delay.h>
#include "uart2.h"

#define MAX_IDX 35
#define MIN_IDX 0

sbit BEEP = P3^6;

void BeepInit();
void Timer0Init();
void DealBeep(unsigned short int time);

/*********************************************************************
* 高8位
**********************************************************************/  
unsigned char HighFrequency[]={
//1			2 		3     4     5			6			7			8			9			10		11		12  
	0xE3, 0xE4, 0xE6, 0xE7, 0xE9, 0xEA, 0xEB, 0xEC, 0xEE, 0xEF, 0xF0, 0xF1,	//低音 
//do		do#		re		re#		mi		fa		fa#		so		so#		la		la#		si 
//13		14		15		16		17		18		19		20		21		22		23		24  
	0xF2, 0xF2, 0xF3, 0xF4, 0xF5, 0xF5, 0xF6, 0xF6, 0xF7, 0xF8, 0xF8, 0xF9,	//中音 
//25		26		27		28		29		30		31		32		33		34		35		36
	0xF9, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC, 0xFC, 0xFC, 0xFD,	//高音
};

/*********************************************************************
* 低8位
**********************************************************************/  
unsigned char LowFrequency[]={  
//1			2 		3     4     5			6			7			8			9			10		11		12  
	0x05, 0xB3, 0x4A, 0xCA, 0x34, 0x8A, 0xCD, 0xFD, 0x1D, 0x2D, 0x2D, 0x1E,	//低音 
//do		do#		re		re#		mi		fa		fa#		so		so#		la		la#		si 
//13		14		15		16		17		18		19		20		21		22		23		24  
	0x03, 0xD9, 0xA5, 0x65, 0x1A, 0xC5, 0x66, 0xFE, 0x8E, 0x16, 0x96, 0x0F,	//中音 
//25		26		27		28		29		30		31		32		33		34		35		36
	0x81, 0xEC, 0x52, 0xB2, 0x0D, 0x62, 0xB3, 0xFE, 0x47, 0x8B, 0xCA, 0x08,	//高音
};

unsigned char Timer0_TH0 = 0xFD;
unsigned char Timer0_TL0 = 0x08;

void BeepInit(void)
{
	P3M0 |= 0x50;	// 0001 0000 配置P3^6口为 推挽输出 模式
	P3M1 = 0x00;
}

void Timer0Init(void)
{
	// 参考 STC32G 手册 14.4.2
	// 定时器0/1模式寄存器
	
//	TMOD = 0x01;	// 0000 0001 定时器0不自动重载
	T0_M1 = 0;
	T0_M0 = 1;	// 定时器0不自动重载
	
	// 参考 STC32G 手册 12.4.1
	EA = 1;	// 总中断控制
	ET0 = 1;	// 计时器T0溢出中断允许
	// 上面两句等价于 
	// IE = 0x82 // 1000 0010 CPU开中断,CT0开中断 		
}

void timer0_int (void) interrupt 1
{  
		// 参考 STC32G 手册 14.2.1
	  TR0 = 0;	// 定时器0运行控制，停止计数，隶属于总寄存器 TCON
	  BEEP = !BEEP; 
		TH0 = Timer0_TH0; // 定时器0高8位寄存器
	  TL0 = Timer0_TL0; // 定时器0低8位寄存器
		TR0 = 1;	// 定时器0开始计数
		TF0 = 0;	// 清除T0中断溢出标志位，隶属于总寄存器 TCON
}  

void DealBeep(unsigned short int time){
	TH0 = Timer0_TH0; // 定时器0高8位寄存器
	TL0 = Timer0_TL0; // 定时器0低8位寄存器
	TR0 = 1;	// 定时器0开始计数

	// 调1/4 310ms 调2/4  250ms 调3/4  187ms 调4/4  125ms
	delay_n_ms(time);	// 节拍时间，用以不要反复填充16位定时寄存器，使某个音调持续响一段时间
	
	TR0 = 0;	// 定时器0停止计数
}

void DealBeep_with_BLE(unsigned char time, unsigned char pitch_num)
{
  TH0 = HighFrequency[pitch_num]; // 定时器0高8位寄存器
  TL0 = LowFrequency[pitch_num]; // 定时器0低8位寄存器
  TR0 = 1;	// 定时器0开始计数

  // 调1/4 310ms 调2/4  250ms 调3/4  187ms 调4/4  125ms
  // delay_n_ms(time);	// 节拍时间，用以不要反复填充16位定时寄存器，使某个音调持续响一段时间

  delay_with_BLE(time);

  TR0 = 0;	// 定时器0停止计数
	
	delay_with_BLE(500);
}

