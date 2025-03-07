/**
 ******************************************************************************
 * @file        drv_uart.h
 * @author      RobotPilots@2020
 * @brief       UART Driver Package(Based on HAL).
 ******************************************************************************
 * @attention
 * 
 * Copyright 2020 RobotPilots
 * 
 * @Version     V1.0
 * @date        15-August-2020
 ******************************************************************************
 */
#ifndef __DRV_UART_H
#define __DRV_UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void DRV_UART_IRQHandler(UART_HandleTypeDef *huart);
void USART1_Init(void);
void USART2_Init(void);
void USART3_Init(void);
void USART5_Init(void);
void USART6_Init(void);

#endif
