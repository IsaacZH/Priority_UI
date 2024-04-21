/**
  ******************************************************************************
  * @file           : RP_drv
  * @brief          : 
  * @note           : start 2022-11-3 
  ******************************************************************************
  */
	
#ifndef __CONFIG_CAN_H
#define __CONFIG_CAN_H

#include "stm32f4xx_hal.h"


/* 电机can接收id */
/*can1*/

/*can2*/



void CAN1_RX(uint32_t canId, uint8_t *rxBuf);
void CAN2_RX(uint32_t canId, uint8_t *rxBuf);



#endif
