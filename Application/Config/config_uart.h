/**
  ******************************************************************************
  * @file           : config_uart.c\h
  * @brief          : 
  * @note           : finish 2022-2-12 12:24:28
  ******************************************************************************
  */

#ifndef __CONFIG_UART_H
#define __CONFIG_UART_H

#include "config.h"


void USART1_rxDataHandler(uint8_t *rxBuf);
void USART3_rxDataHandler(uint8_t *rxBuf);
void USART6_rxDataHandler(uint8_t *rxBuf);

#endif
