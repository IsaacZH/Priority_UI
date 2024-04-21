#ifndef __CAN_PROTOCOL_H
#define __CAN_PROTOCOL_H

#include "config.h"

/*CAN发送或是接收的ID*/
typedef enum
{
	CAN_0x200_ID	= 0x200,		
	CAN_0x1ff_ID = 0x1FF,	
	CAN_0x280_ID = 0x280,
}CAN_ID;

uint8_t CAN_Send(void);
void KT_motorAngle_rx(void);
void CAN1_rxDataHandler(uint32_t canId, uint8_t *rxBuf);
void CAN2_rxDataHandler(uint32_t canId, uint8_t *rxBuf);
void CAP_txMessage(void);

#endif

