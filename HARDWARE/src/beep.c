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
* ��8λ
**********************************************************************/  
unsigned char HighFrequency[]={
//1			2 		3     4     5			6			7			8			9			10		11		12  
	0xE3, 0xE4, 0xE6, 0xE7, 0xE9, 0xEA, 0xEB, 0xEC, 0xEE, 0xEF, 0xF0, 0xF1,	//���� 
//do		do#		re		re#		mi		fa		fa#		so		so#		la		la#		si 
//13		14		15		16		17		18		19		20		21		22		23		24  
	0xF2, 0xF2, 0xF3, 0xF4, 0xF5, 0xF5, 0xF6, 0xF6, 0xF7, 0xF8, 0xF8, 0xF9,	//���� 
//25		26		27		28		29		30		31		32		33		34		35		36
	0xF9, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFB, 0xFB, 0xFC, 0xFC, 0xFC, 0xFD,	//����
};

/*********************************************************************
* ��8λ
**********************************************************************/  
unsigned char LowFrequency[]={  
//1			2 		3     4     5			6			7			8			9			10		11		12  
	0x05, 0xB3, 0x4A, 0xCA, 0x34, 0x8A, 0xCD, 0xFD, 0x1D, 0x2D, 0x2D, 0x1E,	//���� 
//do		do#		re		re#		mi		fa		fa#		so		so#		la		la#		si 
//13		14		15		16		17		18		19		20		21		22		23		24  
	0x03, 0xD9, 0xA5, 0x65, 0x1A, 0xC5, 0x66, 0xFE, 0x8E, 0x16, 0x96, 0x0F,	//���� 
//25		26		27		28		29		30		31		32		33		34		35		36
	0x81, 0xEC, 0x52, 0xB2, 0x0D, 0x62, 0xB3, 0xFE, 0x47, 0x8B, 0xCA, 0x08,	//����
};

unsigned char Timer0_TH0 = 0xFD;
unsigned char Timer0_TL0 = 0x08;

void BeepInit(void)
{
	P3M0 |= 0x50;	// 0001 0000 ����P3^6��Ϊ ������� ģʽ
	P3M1 = 0x00;
}

void Timer0Init(void)
{
	// �ο� STC32G �ֲ� 14.4.2
	// ��ʱ��0/1ģʽ�Ĵ���
	
//	TMOD = 0x01;	// 0000 0001 ��ʱ��0���Զ�����
	T0_M1 = 0;
	T0_M0 = 1;	// ��ʱ��0���Զ�����
	
	// �ο� STC32G �ֲ� 12.4.1
	EA = 1;	// ���жϿ���
	ET0 = 1;	// ��ʱ��T0����ж�����
	// ��������ȼ��� 
	// IE = 0x82 // 1000 0010 CPU���ж�,CT0���ж� 		
}

void timer0_int (void) interrupt 1
{  
		// �ο� STC32G �ֲ� 14.2.1
	  TR0 = 0;	// ��ʱ��0���п��ƣ�ֹͣ�������������ܼĴ��� TCON
	  BEEP = !BEEP; 
		TH0 = Timer0_TH0; // ��ʱ��0��8λ�Ĵ���
	  TL0 = Timer0_TL0; // ��ʱ��0��8λ�Ĵ���
		TR0 = 1;	// ��ʱ��0��ʼ����
		TF0 = 0;	// ���T0�ж������־λ���������ܼĴ��� TCON
}  

void DealBeep(unsigned short int time){
	TH0 = Timer0_TH0; // ��ʱ��0��8λ�Ĵ���
	TL0 = Timer0_TL0; // ��ʱ��0��8λ�Ĵ���
	TR0 = 1;	// ��ʱ��0��ʼ����

	// ��1/4 310ms ��2/4  250ms ��3/4  187ms ��4/4  125ms
	delay_n_ms(time);	// ����ʱ�䣬���Բ�Ҫ�������16λ��ʱ�Ĵ�����ʹĳ������������һ��ʱ��
	
	TR0 = 0;	// ��ʱ��0ֹͣ����
}

void DealBeep_with_BLE(unsigned char time, unsigned char pitch_num)
{
  TH0 = HighFrequency[pitch_num]; // ��ʱ��0��8λ�Ĵ���
  TL0 = LowFrequency[pitch_num]; // ��ʱ��0��8λ�Ĵ���
  TR0 = 1;	// ��ʱ��0��ʼ����

  // ��1/4 310ms ��2/4  250ms ��3/4  187ms ��4/4  125ms
  // delay_n_ms(time);	// ����ʱ�䣬���Բ�Ҫ�������16λ��ʱ�Ĵ�����ʹĳ������������һ��ʱ��

  delay_with_BLE(time);

  TR0 = 0;	// ��ʱ��0ֹͣ����
	
	delay_with_BLE(500);
}

