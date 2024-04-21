/**
  ******************************************************************************
  * @file           : device.c/h
  * @brief          : 
  * @note           :  
  ******************************************************************************
  */
#include "device.h"
#include "communicate_protocol.h"
device_t device [] =
{
	[DEVICE_01] = {
	 .motor = &chassis_motor[CHASSIS_LF],	
	},
	[DEVICE_02] = {
	 .motor = &chassis_motor[CHASSIS_RB],	
	},
  [DEVICE_03] = {
   .motor = &chassis_motor[CHASSIS_RF],	
  },
  [DEVICE_04] = {
   .motor = &chassis_motor[CHASSIS_LB],	
  },
};
/**
  * @Name    Device_Init
  * @brief   设备初始化
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Device_Init(void)
{
  Chassis_Motor_Init();
}

/**
  * @Name    Device_HeartBeat
  * @brief   设备心跳
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Device_HeartBeat(void)
{
  Chassis_Motor_Heart_Beat();
  cap.heart_beat(&cap);
}

/**
  * @Name    Device_Work
  * @brief   设备总控，任务中调用
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void Device_Work(void)
{
  Chassis_Work(&chassis);

	if(communicate.status->chassis_data_state != DEV_ONLINE)
	{
		for(uint16_t i=0;i<DEVICE_CNT;i++)
		{
			device[i].motor->base_info.motor_out = 0;
			device[i].motor->base_info.pid_out = 0;
		}
	}
}

