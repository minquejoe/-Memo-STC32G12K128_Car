#include <STC32G.H>
#include <delay.h>
#include <sr04.h>

sbit Trig = P1^3;
sbit Echo = P4^0;

void Start_SR04_Module();
void Timer3Init();
void calc_dist();
void Counter_Number_DATA();

unsigned int S = 0;	// ����

void Start_SR04_Module(void) {
	Trig=1;			                     //����һ��ģ��
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
	 Start_SR04_Module();	// ����ģ��
	 while(!Echo);	// ��RXΪ0ʱ�ȴ�
	 T3R = 1; // ��������
	 while(Echo);
	 T3R = 0;	// �رռ���
	 calc_dist();
 }
 
void Timer3Init(void)
{
	// �ο� STC32G �ֲ� 14.4.2
//	// ��ʱ��0/1ģʽ�Ĵ���
//	T1_M1 = 0;
//	T1_M0 = 1;	// ��ʱ��1 16λ���Զ�����
	
	T3_CT = 0;	// T3������ʱ��
	T3CLKO = 0;	// T3ʱ������ر�
	
	T3L = 0x00;	//1Tģʽ�³�ʼװ��ֵ       
	T3H = 0x00;	//1Tģʽ�³�ʼװ��ֵ  
	
	// �ο� STC32G �ֲ� 12.4.1
//	TF1 = 0;	//���T1�ж������־λ
//	ET1 = 1;	//ʹ�ܶ�ʱ��1������ж�����λ
//	TR1 = 1;	//��ʱ��1��ʼ��ʱ 
}

unsigned int time = 0; 
void calc_dist(void)
{
	 time = T3H*256 + T3L;
	 T3H=0;
	 T3L=0;
	 S = (time*1.87)/100/2;     //�������CM  	
}