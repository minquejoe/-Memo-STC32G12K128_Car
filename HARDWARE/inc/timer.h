#ifndef	__TIMER_H
#define	__TIMER_H 

#include <STC32G.H> 



#define  uint32   unsigned long
#define  uint16   unsigned int  
#define  uint8    unsigned char  

typedef 	unsigned char	u8;
typedef 	unsigned int	u16;
typedef 	unsigned long	u32;

extern uint16 Time_Count;  
extern   uint8 PWM_Count ; //Õ¼¿Õ±È
void Timer4Init(void);
    


#endif 
