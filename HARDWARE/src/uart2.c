#include "uart2.h"
#include "timer.h"
#include "uart1.h"
#include "delay.h"
#include "Bluetooth.h"

void update_car(unsigned char temp);
void delay_with_BLE(unsigned char time);

volatile uint8 Flg=FALSE;
uint8 uart2temp=0;
unsigned char i;

/***************************************************************************
 * 描  述 : 串口2初始化函数
 * 入  参 : 无
 * 返回值 : 无
备注：波特率9600bps   晶振24MHz
 **************************************************************************/
void Uart2_Init(void)
{
  S2CON = 0x50;		//8位数据,可变波特率，启动串行接收器
  AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
  T2L = 0x8F;		  //设定定时初值
  T2H = 0xFD;     //设定定时初值

  AUXR |= 0x10;   //启动定时器2

  IE2 |= 0x01;    //串口2中断打开

  EA = 1;               //总中断打开

  delay_ms(100);

}

/***************************************************************************
 * 描  述 : 串口2中断服务函数
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************/
void Uart2() interrupt 8 using 1
{
  IE2 &= 0xFE; 			               // 串口2中断关闭
  Flg=TRUE;                       //接收到数据,接收标识符有效
  if (S2CON & S2RI)                //串行接收到停止位的中间时刻时，该位置1
    {
      S2CON &= ~S2RI;              //清除S2CON寄存器对应S2RI位（该位必须软件清零）
      uart2temp = S2BUF;
    }
  if (S2CON & S2TI)                //在停止位开始发送时，该位置1
    {
      S2CON &= ~S2TI;   			     //清除S2CON寄存器对应S2TI位（该位必须软件清零）
    }
  IE2 |= 0x01;                    // 串口2中断打开
}

/**************************************************************************************
 * 描  述 : 串口二接收函数数据
 * 入  参 : 无
 * 返回值 : 无
 **************************************************************************************/
void UART2_Rx_buff(void)
{
  if(Flg)      //有新数据通过串口被接收到
    {
      IE2 &= 0xFE; 			                     // 串口2中断关闭
      SendDataByUart1(uart2temp);            //发送字符


//      if(uart2temp==0x06)
//        {
//          PWM_Count+=5; //加速
//        }
//      else
//        {
//          if(uart2temp==0x07)
//            {
//              PWM_Count-=5; //减速
//            }
//          else
//            {
//              // 5 种小车状态，通过左右前后和速度进行计算得到
//                         //获取状态
//            }
//        }

//      if(uart2temp<0x10)
//        {
//          Car_State_number=uart2temp;
//        }
//      else
//        {
//          PWM_Count = uart2temp-0x10;
//        }

//			update_car(uart2temp);


      IE2 |= 0x01;                           // 串口2中断打开
      Flg=FALSE;                             //清除接收标识符
    }
}

void update_car(unsigned char temp)
{
  // 更新小车状态
  if(temp<0x10)
    {
      Car_State_number=temp;
    }
  else
    {
      PWM_Count = temp-0x10;
    }
}

void delay_with_BLE(unsigned char time)
{
  i = 0;
  while(++i <= time)
    {
      delay_ms(1);
      UART2_Rx_buff();
      update_car(uart2temp);
    }
}














