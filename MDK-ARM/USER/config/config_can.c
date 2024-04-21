/**
  ******************************************************************************
  * @file           : RP_drv
  * @brief          : 
  * @note           : start 2022-12-12 
  ******************************************************************************
  */

#include "config_can.h"
#include "communicate_protocol.h"
#include "chassis_motor.h"
#include "cap.h"
/**
 * @brief can2收
 * 
 * @param canId CAN ID
 * @param rxBuf 数据帧
 */
void CAN2_RX(uint32_t canId, uint8_t *rxBuf)
{
	switch (canId)
	{
		case ID_CHASSIS_LF:
			chassis_motor[CHASSIS_LF].rx(&chassis_motor[CHASSIS_LF],rxBuf,8);
			break;
		case ID_CHASSIS_LB:
			chassis_motor[CHASSIS_LB].rx(&chassis_motor[CHASSIS_LB],rxBuf,8);
			break;
		case ID_CHASSIS_RF:
			chassis_motor[CHASSIS_RF].rx(&chassis_motor[CHASSIS_RF],rxBuf,8);
			break;
		case ID_CHASSIS_RB:
			chassis_motor[CHASSIS_RB].rx(&chassis_motor[CHASSIS_RB],rxBuf,8);
			break;
		default:
			break;
	}	 
	cap.update(&cap,canId,rxBuf);
}

/**
  * @Name    CAN1_RX
  * @brief   can1收
  * @param   canId：canid  
	* @param   rxBuf：数据帧
  * @retval 
  * @author  
  * @Date    
**/
void CAN1_RX(uint32_t canId, uint8_t *rxBuf)
{
	switch (canId)
	{
    case CHASSIS_DATA_RX_ID:
      Chassis_Data_Rx(rxBuf);
      break;	
		case CAR_DATA_RX_ID:
			Car_Data_Rx(rxBuf);
			break;
		default:
			break;
	}
}




