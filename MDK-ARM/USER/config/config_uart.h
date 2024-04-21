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

#define USART1_RX_BUF_LEN     350
#define USART2_RX_DATA_FRAME_LEN	(18u)	// 串口2数据帧长度
#define USART2_RX_BUF_LEN			(USART2_RX_DATA_FRAME_LEN + 6u)	// 串口2接收缓冲区长度
#define USART3_RX_BUF_LEN			200
#define USART4_RX_BUF_LEN			200
#define USART5_RX_BUF_LEN			200
#define USART6_RX_BUF_LEN			200




void USART1_rxDataHandler(uint8_t *rxBuf);
void USART2_rxDataHandler(uint8_t *rxBuf);
void USART3_rxDataHandler(uint8_t *rxBuf);
void USART4_rxDataHandler(uint8_t *rxBuf);
void USART5_rxDataHandler(uint8_t *rxBuf);
void USART6_rxDataHandler(uint8_t *rxBuf);

#endif
