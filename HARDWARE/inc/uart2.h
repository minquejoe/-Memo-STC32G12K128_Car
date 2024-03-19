#ifndef	__UART2_H
#define	__UART2_H

#include <STC32G.H>

#define  TRUE    1
#define  FALSE   0

#define S2_S  0x01
#define S2RI 0x01
#define S2TI 0x02

extern unsigned char uart2temp;

void Uart2_Init(void);
void Usart2_data(void);
void UART2_Rx_buff(void);
void update_car(unsigned char temp);
void delay_with_BLE(unsigned char time);
#endif
