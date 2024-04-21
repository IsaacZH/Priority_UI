/*
* chassis
*	
*	2023.9.11
* 底盘
*/

/* Includes ------------------------------*/
#include "chassis.h"
#include "device.h"
#include "rp_math.h"
#include "communicate_protocol.h"

/* Private function prototypes -----------------------------------------------*/

void Chassis_Speed_Calculating(chassis_t *chassis);//麦轮底盘电机目标速度解算
void Chassis_Pid_Calculating(chassis_t *chassis);//底盘PID计算
void Chassis_Power_Limit(chassis_t * chassis);//底盘功率限制

/* Exported variables --------------------*/
chassis_t chassis = 
{
	.chassisLF = &chassis_motor[CHASSIS_LF],
	.chassisLB = &chassis_motor[CHASSIS_LB],
	.chassisRF = &chassis_motor[CHASSIS_RF],
	.chassisRB = &chassis_motor[CHASSIS_RB],
	

	.work = Chassis_Work,
	
};

/* Function  body --------------------------------------------------------*/

/**
 * @brief 从上主控更新底盘目标值
 * 
 * @param chassis 
 */
void Chassis_Master_Info_Update(chassis_t *chassis)
{
	chassis->base_info.target_cycle_speed = communicate.chassis_data_rx_info->target_cycle_speed;
	chassis->base_info.target_front_speed = communicate.chassis_data_rx_info->target_front_speed;
	chassis->base_info.target_right_speed = communicate.chassis_data_rx_info->target_right_speed;
}

/**
  * @Name    Chassis_Speed_Calculating
  * @brief   底盘电机目标速度计算
  * @param   
  * @retval
  * @author  HWX CCB Isaac 
  * @Date    2022-12-3
**/
void Chassis_Speed_Calculating(chassis_t *chassis)
{
	int16_t front = chassis->base_info.target_front_speed;
	int16_t right = chassis->base_info.target_right_speed;
	int16_t cycle = chassis->base_info.target_cycle_speed;
	
		
	int16_t speed_sum;
	float K;
	
	speed_sum = abs(front) + abs(right) + abs(cycle);
	
	if(speed_sum > CHASSIS_MAX_SPEED)
	{
		K = (float)CHASSIS_MAX_SPEED / (float)speed_sum;
	}
	else 
	{
		K = 1;
	}

	front *= K;
	right *= K;
	cycle *= K;
	
	chassis->base_info.target_chassisLF   =   front + right + cycle; 
	chassis->base_info.target_chassisLB   =   front - right + cycle;
	chassis->base_info.target_chassisRF   = - front + right + cycle; 
	chassis->base_info.target_chassisRB   = - front - right + cycle; 
	
}

/**
 * @brief PID计算
 * 
 * @param chassis 
 */
void Chassis_Pid_Calculating(chassis_t *chassis)
{
  chassis->base_info.output_chassisLF = chassis->chassisLF->c_speed(chassis->chassisLF, chassis->base_info.target_chassisLF);
  chassis->base_info.output_chassisLB = chassis->chassisLB->c_speed(chassis->chassisLB, chassis->base_info.target_chassisLB);
  chassis->base_info.output_chassisRF = chassis->chassisRF->c_speed(chassis->chassisRF, chassis->base_info.target_chassisRF);
  chassis->base_info.output_chassisRB = chassis->chassisRB->c_speed(chassis->chassisRB, chassis->base_info.target_chassisRB);
}

/**
  * @name    Chassis_Power_Limit
  * @brief   底盘功率限制(经典祖传算法)
  * @param   底盘 
  * @retval
  * @author  HWX
  * @date    2022-11-06
**/
void Chassis_Power_Limit(chassis_t * chassis)
{
	if(CHASSIS_POWER_LIMIT)
	{
		int16_t limit_output_current[4];
	
		float buffer = (float)judge.power_heat_data.chassis_power_buffer;
		float heat_rate,Limit_k, CHAS_LimitOutput, CHAS_TotalOutput;
		
		limit_output_current[0] = chassis->base_info.output_chassisLF;
		limit_output_current[1] = chassis->base_info.output_chassisRF;
		limit_output_current[2] = chassis->base_info.output_chassisLB;
		limit_output_current[3] = chassis->base_info.output_chassisRB;
		
		uint16_t OUT_MAX = 0;
	
		OUT_MAX = CHASSIS_MAX_SPEED * 4;
		
		if(buffer > 60)buffer = 60;//防止飞坡之后缓冲250J变为正增益系数
		
		Limit_k = buffer / 60.f;
		
		if(buffer < 25)
			Limit_k = Limit_k * Limit_k ;// * Limit_k; //3方
		else
			Limit_k = Limit_k;// * str->Limit_k; //平方
		
		if(buffer < 60)
			CHAS_LimitOutput = Limit_k * OUT_MAX;
		else 
			CHAS_LimitOutput = OUT_MAX;    
		
		CHAS_TotalOutput = c_abs(limit_output_current[0]) + c_abs(limit_output_current[1]) + c_abs(limit_output_current[2]) + c_abs(limit_output_current[3]) ;
		
		heat_rate = CHAS_LimitOutput / CHAS_TotalOutput;
		
	  if(CHAS_TotalOutput >= CHAS_LimitOutput)
	  {
			for(uint8_t i = 0 ; i < 4 ; i++)
			{	
				limit_output_current[i] = (int16_t)(limit_output_current[i] * heat_rate);	
			}
		}
		/*重新赋值*/
		chassis->base_info.output_chassisLF = limit_output_current[0];
		chassis->base_info.output_chassisRF = limit_output_current[1];
		chassis->base_info.output_chassisLB = limit_output_current[2];
		chassis->base_info.output_chassisRB = limit_output_current[3];	
	}
}
	

/**
  * @Name    Chassis_Work
  * @brief   总控
  * @param   
  * @retval 
  * @author  
  * @Date    
**/

void Chassis_Work(chassis_t *chassis)
{
	//没收到上主控信息，卸力
	if (communicate.status->chassis_data_state == DEV_OFFLINE)
	{
		chassis->base_info.output_chassisLF = 0;
		chassis->base_info.output_chassisLB = 0;
		chassis->base_info.output_chassisRF = 0;
		chassis->base_info.output_chassisRB = 0;
	}
	else
	{
		Chassis_Master_Info_Update(chassis);//从上主控更新底盘目标值
		Chassis_Speed_Calculating(chassis);//麦轮底盘电机目标速度解算
		Chassis_Pid_Calculating(chassis);//底盘PID计算
    Chassis_Power_Limit(chassis);//底盘功率限制
	}
	//底盘电机输出赋值
	chassis->chassisLF->base_info.motor_out = chassis->base_info.output_chassisLF;
	chassis->chassisLB->base_info.motor_out = chassis->base_info.output_chassisLB;
	chassis->chassisRF->base_info.motor_out = chassis->base_info.output_chassisRF;
	chassis->chassisRB->base_info.motor_out = chassis->base_info.output_chassisRB;
}

