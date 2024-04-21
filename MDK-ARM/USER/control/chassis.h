#ifndef _CHASSIS_H
#define _CHASSIS_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "judge_protocol.h"
#include "chassis_motor.h"
#include "communicate_protocol.h"
/* Exported macro ------------------------------------------------------------*/
#define CHASSIS_POWER_LIMIT         (judge.judge_work_state == DEV_ONLINE)//功率限制 开：1 关：0
#define CHASSIS_MAX_SPEED           (communicate.chassis_data_rx_info->chassis_max_speed)
/** 
  * @brief  状态枚举
  */ 
typedef enum 
{
	CHASSIS_OFFLINE = 0,	
	
	CHASSIS_ONLINE,

}chassis_work_state_e;



/** 
  * @brief  底盘基本信息定义
  */ 
typedef struct __packed 
{
	
	int16_t      target_front_speed;//目标前进速度
	int16_t      target_right_speed;//目标右移速度
	int16_t      target_cycle_speed;//目标旋转速度
	
	int16_t    	 output_chassisLF;
	int16_t    	 output_chassisLB;
	int16_t    	 output_chassisRF;
	int16_t    	 output_chassisRB;
	
	int16_t    	 target_chassisLF;
	int16_t    	 target_chassisLB;
	int16_t    	 target_chassisRF;
	int16_t    	 target_chassisRB;

}chassis_base_info_t;


/** 
  * @brief  底盘类定义
  */ 
typedef struct chassis_class_t
{	

	motor_t        		 *chassisLF;
	motor_t        		 *chassisLB;
	motor_t        		 *chassisRF;
	motor_t        		 *chassisRB;


	chassis_base_info_t   	base_info;
	motor_state_e   		work_sate;
	
	void                (*work)(struct chassis_class_t *chassis);
	
}chassis_t;


extern chassis_t chassis;



/* Exported functions --------------------------------------------------------*/

//总控
void Chassis_Work(chassis_t *chassis);




#endif
