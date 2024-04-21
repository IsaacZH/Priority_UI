/**
 * @file chassis_motor.c
 * @author your name (you@domain.com)
 * @brief �����ؿ��Ƶ��̵��
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "chassis_motor.h"

motor_t  chassis_motor[CHASSIS_MOTOR_LIST] =
{
	[CHASSIS_LF] = {
	
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = ID_CHASSIS_LF, 
		
		.init = Motor_Class_Init,
	},
	[CHASSIS_LB] = {
	
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = ID_CHASSIS_LB, 
		
		.init = Motor_Class_Init,
	},
	[CHASSIS_RF] = {
	
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = ID_CHASSIS_RF, 
		
		.init = Motor_Class_Init,
	},
	[CHASSIS_RB] = {
	
		.id.drive_type = M_CAN2,
		.id.motor_type = RM3508,
		.id.rx_id = ID_CHASSIS_RB, 
		
		.init = Motor_Class_Init,
	},
	
};



																			    	/*kp		 ki		  kd		 b_err		 int_max		iout_max		out_max*/
float chassis_3508_speed_pid_param[7] 	= {		8,		0.33,		0,			0,				6000,			  6000,			 15000};



/**
  * @name    Chassis_Motor_Init
  * @brief   �������ʼ����device�е���
  * @param   
  * @retval 
  * @author  
**/
void Chassis_Motor_Init(void)
{
	for(uint16_t i=0;i<CHASSIS_MOTOR_LIST;i++)
		{ //�����ʼ��
			chassis_motor[i].init(&chassis_motor[i]);
			//����ٶ�pid��ʼ��
			chassis_motor[i].pid_init(&chassis_motor[i].pid.speed,chassis_3508_speed_pid_param);
		}
}

/**
  * @name    Chassis_Motor_Heart_Beat
  * @brief   ���������device�е���
  * @param   
  * @retval 
  * @author  
**/
void Chassis_Motor_Heart_Beat(void)
{
	chassis_motor[CHASSIS_LF].heartbeat(&chassis_motor[CHASSIS_LF]);
	chassis_motor[CHASSIS_LB].heartbeat(&chassis_motor[CHASSIS_LB]);
	chassis_motor[CHASSIS_RF].heartbeat(&chassis_motor[CHASSIS_RF]);
	chassis_motor[CHASSIS_RB].heartbeat(&chassis_motor[CHASSIS_RB]);
}




