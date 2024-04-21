#include "drive.h"


void Drive_Init(void)
{
	CAN1_Init();
	CAN2_Init();
	USART1_Init();
	USART2_Init();
	USART3_Init();
	USART4_Init();
	USART6_Init();
	PWM_Init();
}


