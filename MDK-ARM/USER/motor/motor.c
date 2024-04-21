/*
*	RP MOTOR_BAG
*	2022.11.6 
* AUTHOR CCB HXZP
*
*使用电机前必须配置好电机的类型、id号、驱动方式,以及初始化函数指针Motor_Class_Init
*使用pid前也需要进行pid初始化，否则无法使用
*可以直接使用内置函数进行pid控制 也可以直接使用库内定义函数或者自己定义的函数
*kt系列电机：使用kt系列电机前需要先实例化motor_9025_info_t，再与motor内的指针联系，其余步骤无异
*/

#include "motor.h"



/**
 *	@brief	电机发送信息
 *  
 */ 
uint8_t can_tx_buff(struct motor_class_t *motor, uint8_t *buff,uint8_t len)
{
	uint8_t res;
	uint8_t pos8;
	
	if(motor->id.motor_type > 0 && motor->id.motor_type <= 3)   //RM motor
	{
		pos8 = motor->id.buff_p*2;																//ID换算为数据域
		buff[pos8] 	 = (uint8_t)((int16_t)motor->base_info.motor_out >> 8);	//存入高8位
		buff[pos8+1] = (uint8_t)((int16_t)motor->base_info.motor_out);			//存入低8位
	}
	else if(motor->id.motor_type > 3 && motor->id.motor_type <= 5)	//kt motor
	{
		pos8 = 0;
		buff[pos8+1] = (uint8_t)((int16_t)motor->base_info.motor_out >> 8);
		buff[pos8] 	 = (uint8_t)((int16_t)motor->base_info.motor_out);
	}
	
	return res;
}

/**
 *	@brief	电机接收信息
 *   
 */
uint8_t can_rx_buff(struct motor_class_t *motor, uint8_t *buff,uint8_t len)
{
	uint8_t res;
	
	if(motor == NULL || buff == NULL)
	{
		return 0;
	}
	
	if(motor->state.init_flag == M_DEINIT)
	{
		return 0;	
	}
	
	if(motor->id.motor_type > 0 && motor->id.motor_type <= 3)		//RM motor
	{
		get_rm_info(motor,buff);
	}
	else if(motor->id.motor_type > 3 && motor->id.motor_type <= 5)	//kt motor	
	{
		get_kt_9025_info(motor,buff);
	}
	
	return res;
}


















/**
 *	@brief	电机pid初始化
 */
void Motor_Class_Pid_Init(struct motor_pid *pid, float *buff)
{
	if(pid == NULL || buff == NULL)
	{
		return;
	}
	//电机信息置零
	pid->info.target   = 0;
	pid->info.measure  = 0;	
	pid->info.err      = 0;	
	pid->info.last_err = 0;
	pid->info.integral = 0;
	pid->info.pout     = 0;
	pid->info.iout     = 0;
	pid->info.dout     = 0;	
	pid->info.out      = 0;		
	//PID 参数
	pid->set.kp           = buff[0];
	pid->set.ki           = buff[1];	
	pid->set.kd           = buff[2];
	pid->set.blind_err    = buff[3];
	pid->set.integral_max = buff[4];
	pid->set.iout_max     = buff[5];	
	pid->set.out_max        = buff[6];
	//初始化成功
	pid->info.init_flag = M_INIT;
	
}	

/**
 *	@brief	电机初始化
 */
void Motor_Class_Init(struct motor_class_t *motor)
{
	if(motor == NULL)
	{
		return;
	}

	if(motor->id.motor_type == KT9025 && motor->kt9025_info == NULL)
	{
		return;
	}
	
	motor->state.work_state = M_OFFLINE;
	
	motor->state.offline_cnt_max = 100;	
	motor->state.offline_cnt = motor->state.offline_cnt_max;
	

	if(motor->id.drive_type == M_CAN1 || motor->id.drive_type == M_CAN2)
	{
		get_rm_can_drvie(motor);
	}
	else if(motor->id.drive_type == M_USART1 || motor->id.drive_type == M_USART2)
	{

	}	
	
\
	
	motor->pid_init     = Motor_Class_Pid_Init;
	motor->heartbeat    = Motor_Class_HeartBeat;	
	
	motor->c_stuck_flag = motor_class_stucking_flag;		//堵转判断
	motor->c_offset     = motor_offset;									
	motor->c_judge_dir  = motor_judge_dir;
	
	motor->c_speed = motor_pid_speed;
	motor->c_angle = motor_pid_angle;
	motor->c_posit = motor_pid_position;	
	
	motor->c_pid1 = motor_pid_single;
	motor->c_pid2 = motor_pid_double;		
	
	motor->state.init_flag = M_INIT; 										//初始化成功
}

/**
 *	@brief	电机心跳
 */
void Motor_Class_HeartBeat(struct motor_class_t *motor)
{
	if(motor == NULL)
	{
		return;
	}

	if(motor->state.init_flag == M_DEINIT)
	{
		return;	
	}
	
	motor->state.offline_cnt++;
	
	if(motor->state.offline_cnt > motor->state.offline_cnt_max) 
	{
		motor->state.offline_cnt = motor->state.offline_cnt_max;
		motor->state.work_state = M_OFFLINE;
	}
	else 
	{
		if(motor->state.work_state == M_OFFLINE)
			motor->state.work_state = M_ONLINE;
	}
}

// /**
// *	@brief	堵转判断：仅是必要条件，并不是一定堵住 torque_limit:扭矩阈值 return:1为是 0为否
//  */
// uint8_t motor_class_stucking_flag(struct motor_class_t *motor, float torque_limit)
// {
// 	uint8_t res = 0;
	
	
// 	if(motor->state.init_flag == M_DEINIT || motor->state.work_state == M_OFFLINE)return 0;	
	
// 	if(m_abs(motor->rx_info.torque) > torque_limit && m_abs(motor->rx_info.speed) < 5)
// 	{
// 		motor->base_info.lock_cnt++;
		
// 		if (motor->base_info.lock_cnt == 10)
// 			res = 1;
// 		else
// 			res = 0;
// 	}
// 	else
// 	{
// 		res = 0;
// 		motor->base_info.lock_cnt = 0;
// 	}
	
// 	return res;
	
// }

/**
 * @brief 堵转判断
 * 
 * @param motor 电机
 * @param pid pid类型
 * @return 堵转：1 不是堵转：0 
 */
uint8_t motor_class_stucking_flag(struct motor_class_t *motor)
{
	uint8_t res = 0;
	
	
	if(motor->state.init_flag == M_DEINIT || motor->state.work_state == M_OFFLINE)return 0;	
	
	if(m_abs(motor->pid.speed.info.integral) == motor->pid.speed.set.integral_max && m_abs(motor->rx_info.speed) < 5)
	{
		motor->base_info.lock_cnt++;
		
		if (motor->base_info.lock_cnt == 10)
			res = 1;
		else
			res = 0;
	}
	else
	{
		res = 0;
		motor->base_info.lock_cnt = 0;
	}
	return res;
}
/*-----------------------------------------------------------------
*数据处理
-----------------------------------------------------------------*/
/**
 *	@brief	周期处理 tar：源数据 cycle:数据范围
 */
float motor_cycle(float tar,float cycle)
{
	if(tar < 0)          tar += cycle;
	else if(tar >=cycle) tar -= cycle;
	
	return tar;
}
/**
 *	@brief	过半圈处理 angle：源数据 cycle:数据范围
 */
float motor_half_cycle(float angle,float max)
{
	if(m_abs(angle) > (max/2))
	{	
		if(angle >= 0)
			angle += -max;		
		else
			angle +=  max;
	}
	return angle;
}
/**
 *	@brief	计算电机方向  limit:电机数据范围
 */
void motor_judge_dir(struct motor_class_t *motor,uint16_t range)
{
	int16_t angle = 0;
	
	if(motor->rx_info.angle < motor->mec_info.mec_mid)
		 angle = motor->rx_info.angle - motor->mec_info.mec_mid + range;
	else
	   angle = motor->rx_info.angle - motor->mec_info.mec_mid;

	if(m_abs(angle - range/2) < range/4)
	{
		motor->mec_info.dir = MOTOR_B;
	}
	else 
	{
		motor->mec_info.dir = MOTOR_F;
	}	
}
/**
 *	@brief	对电机角度做偏置 类如yaw轴电机朝向，原始朝前为1777，修改后朝前为0 
 *            limit:电机数据范围
 */
void motor_offset(struct motor_class_t *motor, uint16_t range)
{
	motor_rx_info_t *info = &motor->rx_info;
	
	int16_t angle = 0;
	
	if(info->angle < motor->mec_info.mec_mid)
		 angle = info->angle - motor->mec_info.mec_mid + range;
	else
	   angle = info->angle - motor->mec_info.mec_mid;
	
  angle = -angle + range + range/4;
	
	if(angle > range)angle = angle - range;

	angle = motor_cycle(angle - range/4,range);
	
	info->angle_offset = angle;			
}


/*-----------------------------------------------------------------
*电机pid
-----------------------------------------------------------------*/

/**
 *	@brief	获取误差 tar - mea
 */
float motor_pid_err(motor_pid_t *pid,float measure)
{
	motor_pid_info_t *pid_info = &pid->info;
	
	if(pid->info.init_flag == M_DEINIT)
	{
		return 0;
	}
	
	pid_info->measure = measure;
	pid_info->err = pid_info->target - pid_info->measure;
	return pid_info->err;

}

/**
 *	@brief	pid计算 不包含err计算
 */
float motor_pid_cal(motor_pid_t *pid)
{
	
	if(pid->info.init_flag == M_DEINIT)
	{
		return 0;
	}
	
	motor_pid_info_t *pid_info = &pid->info;
	motor_pid_set_t  *pid_set = &pid->set;	
	
	//保存误差值(需要在外面自行计算误差)
	//pid->err = err;
	if(m_abs(pid_info->err)<=(pid_set->blind_err))
		pid_info->err = 0;
	
	//积分
	pid_info->integral += pid_info->err;
	pid_info->integral = m_constrain(pid_info->integral, -pid_set->integral_max, +pid_set->integral_max);
	
	//pid 输出项计算
	pid_info->pout = pid_set->kp * pid_info->err;
	pid_info->iout = pid_set->ki * pid_info->integral;
	pid_info->dout = pid_set->kd * (pid_info->err - pid_info->last_err);
	
	pid_info->iout = m_constrain(pid_info->iout, -pid_set->iout_max, pid_set->iout_max);	
	//累加pid输出值
	pid_info->out = pid_info->pout + pid_info->iout + pid_info->dout;
	pid_info->out = m_constrain(pid_info->out, -pid_set->out_max, pid_set->out_max);

	pid_info->last_err = pid_info->err;
	
	return pid_info->out;
}

/**
 *	@brief	pid总控制 参数：外环 内环 外环观测值 内环观测值 err处理方式
 *          err_cal_mode：err处理方式 半圈还是四分之一圈 0，1，2 速度环使用0 yaw轴使用1 
						陀螺仪角度环 3
 *          当内环为NULL则只计算外环，外环不能为NULL
 *
 *  @return 返回计算结果
 */
float motor_pid_ctrl(motor_pid_t *out, motor_pid_t *inn, float meas1, float meas2, char err_cal_mode)
{
	if(out == NULL)return 0;
	
	if(inn == NULL)
	{
		motor_pid_err(out , meas1);	
		switch(err_cal_mode)
		{
			case 0:			
				break;
			
			case 1:
				out->info.err = motor_half_cycle(out->info.err, 8191);
				break;				
			
			case 2:
				out->info.err = motor_half_cycle(out->info.err, 8191);
				out->info.err = motor_half_cycle(out->info.err, 4095);
				break;
			
      case 3:
				out->info.err = motor_half_cycle(out->info.err, 360);
				break;
		}
		motor_pid_cal(out);
		
		return out->info.out;	
	}
	else 
	{
		/*--外环计算--*/
		motor_pid_err(out , meas1);	
		switch(err_cal_mode)
		{
			case 0:			
				break;
			
			case 1:
				out->info.err = motor_half_cycle(out->info.err, 8191);
				break;				
			
			case 2:
				out->info.err = motor_half_cycle(out->info.err, 8191);
				out->info.err = motor_half_cycle(out->info.err, 4095);
				break;
			case 3:
				out->info.err = motor_half_cycle(out->info.err, 360);
				break;
		}
		motor_pid_cal(out);
		
		inn->info.target = out->info.out;	//目标值转移到速度环
		
		/*--内环计算--*/
		motor_pid_err(inn , meas2);  
		motor_pid_cal(inn);	
		
		return inn->info.out;	
	}
}

/**
 *	@brief	pid总控制 参数：外环 内环 外环观测值 内环观测值 err处理方式
 *          err_cal_mode：err处理方式 半圈还是四分之一圈 0，1，2 速度环使用0 yaw轴使用1
 *          当内环为NULL则只计算外环，外环不能为NULL
 *
 *  @return 返回计算结果
 */
float KTmotor_pid_ctrl(motor_pid_t *out, motor_pid_t *inn, float meas1, float meas2, char err_cal_mode)
{
	if(out == NULL)return 0;
	
	if(inn == NULL)
	{
		motor_pid_err(out , meas1);	
		switch(err_cal_mode)
		{
			case 0:			
				break;
			
			case 1:
				out->info.err = motor_half_cycle(out->info.err, 65535);
				break;				
			
			case 2:
				out->info.err = motor_half_cycle(out->info.err, 65535);
				out->info.err = motor_half_cycle(out->info.err, 32767);
				break;			
		}
		motor_pid_cal(out);
		
		return out->info.out;	
	}
	else 
	{
		/*--外环计算--*/
		motor_pid_err(out , meas1);	
		switch(err_cal_mode)
		{
			case 0:			
				break;
			
			case 1:
				out->info.err = motor_half_cycle(out->info.err, 65535);
				break;				
			
			case 2:
				out->info.err = motor_half_cycle(out->info.err, 65535);
				out->info.err = motor_half_cycle(out->info.err, 32767);
				break;			
		}
		motor_pid_cal(out);
		
		inn->info.target = out->info.out;	//目标值转移到速度环
		
		/*--内环计算--*/
		motor_pid_err(inn , meas2);  
		motor_pid_cal(inn);	
		
		return inn->info.out;	
	}
}

/**
 *	@brief	双环pid控制 
 *  @return 返回计算结果
 */
float motor_pid_double(motor_pid_t *out, motor_pid_t *inn, float meas1, float meas2, float tar, char err_cal_mode)
{

	out->info.target = tar;

	return motor_pid_ctrl(out,inn,meas1,meas2,err_cal_mode);

}


/**
 *	@brief	单pid控制 
 *  @return 返回计算结果
 */
float motor_pid_single(motor_pid_t *out, float meas1, float tar)
{

	out->info.target = tar;

	return motor_pid_ctrl(out,NULL,meas1,NULL,0);

}

/**
 *	@brief	位置pid控制 
 *  @return 返回计算结果
 */
float motor_pid_position(struct motor_class_t *motor,float target)
{
	
	if(motor->state.init_flag == M_DEINIT)
	{
		return 0;
	}
	
	if(motor->pid.position.info.init_flag == M_DEINIT)
	{
		return 0;
	}	
	
	motor->pid.position.info.target = target;
	
	if(motor->id.motor_type > 0 && motor->id.motor_type <= 3)
	{
		motor->base_info.pid_out = motor_pid_ctrl(&motor->pid.position,&motor->pid.position_in,motor->rx_info.angle_sum,motor->rx_info.speed,0);
	}
	else if(motor->id.motor_type > 3 && motor->id.motor_type <= 5)
	{
		motor->base_info.pid_out = KTmotor_pid_ctrl(&motor->pid.position,&motor->pid.position_in,motor->kt9025_info->state_info.encoder_sum,motor->kt9025_info->speed,0);
	}
	
	return motor->base_info.pid_out;
	
}

/**
 *	@brief	角度pid控制 速度内环 角度外环
 *  @return 返回计算结果
 */
float motor_pid_angle(struct motor_class_t *motor,float target)
{
	
	if(motor->state.init_flag == M_DEINIT)
	{
		return 0;
	}

	if(motor->pid.angle.info.init_flag == M_DEINIT)
	{
		return 0;
	}	
	
	motor->pid.angle.info.target = target;
	
	
	if(motor->id.motor_type > 0 && motor->id.motor_type <= 3)
	{
		motor->base_info.pid_out = motor_pid_ctrl(&motor->pid.angle,&motor->pid.angle_in,motor->rx_info.angle,motor->rx_info.speed,1);
	}
	else if(motor->id.motor_type > 3 && motor->id.motor_type <= 5)
	{
		motor->base_info.pid_out = KTmotor_pid_ctrl(&motor->pid.angle,&motor->pid.angle_in,motor->kt9025_info->state_info.encoder,motor->kt9025_info->speed,1);
	}
	
	
	return motor->base_info.pid_out;
	
}

/**
 *	@brief	速度pid控制 
 *  @return 返回计算结果
 */
float motor_pid_speed(struct motor_class_t *motor,float target)
{
	
	if(motor->state.init_flag == M_DEINIT)
	{
		return 0;
	}	

	if(motor->pid.speed.info.init_flag == M_DEINIT)
	{
		return 0;
	}	
	
	motor->pid.speed.info.target = target;
	
	motor->base_info.pid_out = motor_pid_ctrl(&motor->pid.speed,NULL,motor->rx_info.speed,NULL,0);  
	
	return motor->base_info.pid_out;
	
}




/*-----------------------------------------------------------------
*大疆电机接收
-----------------------------------------------------------------*/

/**
 *	@brief	从CAN报文中读取电机的位置反馈
 */
static uint16_t CAN_GetMotorAngle(uint8_t *rxData)
{
	uint16_t angle;
	angle = ((uint16_t)rxData[0] << 8| rxData[1]);   //存入高8位和低8位
	return angle;
}

/**
 *	@brief	从CAN报文中读取电机的转子转速反馈
 */
static int16_t CAN_GetMotorSpeed(uint8_t *rxData)
{
	int16_t speed;
	speed = ((uint16_t)rxData[2] << 8| rxData[3]);
	return speed;
}

/**
 *	@brief	从CAN报文中读取电机的实际转矩电流反馈
 */
static int16_t CAN_GetMotorCurrent(uint8_t *rxData)
{
	int16_t current;
	current = ((int16_t)rxData[4] << 8 | rxData[5]);
	return current;
}

/**
 *	@brief	从CAN报文中读取电机的实际输出转矩
 */
static int16_t CAN_GetMotorTorque(uint8_t *rxData)
{
	int16_t torque;
	torque = ((int16_t)rxData[4] << 8 | rxData[5]);
	return torque;
}

/**
 *	@brief	从CAN报文中读取电机的实际温度
 */
static uint8_t CAN_GetMotorTemperature(uint8_t *rxData)
{
	uint8_t temperature;
	temperature = rxData[6];
	return temperature;
}

/**
 *	@brief	大疆电机can驱动信息
 *  @return 
 */
void get_rm_can_drvie(struct motor_class_t *motor)
{
	if(motor == NULL)
	{
		return;
	}
	
	motor->rx = can_rx_buff;
	motor->tx = can_tx_buff;			
	
	if(motor->id.motor_type == GM6020)
	{
			if((motor->id.rx_id - 0x205U) < 4)
				motor->id.tx_id = 0x1FF;
			else
				motor->id.tx_id = 0x2FF;
			
			motor->id.buff_p = (motor->id.rx_id - 0x205U)%4;
	}
	else if(motor->id.motor_type == RM3508)
	{
			if((motor->id.rx_id - 0x201U) < 4)
				motor->id.tx_id = 0x200;
			else
				motor->id.tx_id = 0x1FF;
			
			motor->id.buff_p = (motor->id.rx_id - 0x201U)%4;
	}		
	else if(motor->id.motor_type == RM2006)
	{
			if((motor->id.rx_id - 0x201U) < 4)
				motor->id.tx_id = 0x200;
			else
				motor->id.tx_id = 0x1FF;
			
			motor->id.buff_p = (motor->id.rx_id - 0x201U)%4;
	}			

}

/**
 *	@brief	can接收信息处理
 *  @return
 */
void get_rm_info(struct motor_class_t *motor, uint8_t *rxBuf)
{
	int16_t err;							//两次检测角度差值

	motor_rx_info_t *motor_info = &(motor->rx_info);
	
	motor_info->angle   = CAN_GetMotorAngle(rxBuf);	
	motor_info->speed   = CAN_GetMotorSpeed(rxBuf);
	motor_info->current = CAN_GetMotorCurrent(rxBuf);
	motor_info->torque  = CAN_GetMotorTorque(rxBuf);	
	motor_info->temperature = CAN_GetMotorTemperature(rxBuf);

	if(!motor_info->angle_prev && !motor_info->angle_sum)	//初始化时清零
		err = 0;
	else
		err = motor_info->angle - motor_info->angle_prev;		//计算两次检测角度差值
	
	/* 过零点 */
	if(m_abs(err) > 4095)			
	{
		/* 0↓ -> 8191 */ 			//对应0°——360°
		if(err >= 0)
			motor_info->angle_sum += -8191 + err;
		/* 8191↑ -> 0 */
		else
			motor_info->angle_sum += 8191 + err;
	}
	/* 未过零点 */
	else
	{
		motor_info->angle_sum += err;
	}	
	
	motor_info->angle_prev = motor_info->angle;		
	
	motor->state.offline_cnt = 0;		//离线判断清零
}

/*-----------------------------------------------------------------
*KT电机接收
-----------------------------------------------------------------*/

/**
 *	@brief	can接收信息处理
 *  @return
 */
void get_kt_9025_info(struct motor_class_t *motor, uint8_t *rxBuf)
{
	uint8_t ID = rxBuf[0];
	int16_t err;
	
	motor->state.offline_cnt = 0;
	
	motor_9025_info_t *base_info = motor->kt9025_info;
	motor_9025_state_info_t *state_info = &motor->kt9025_info->state_info;
	motor_9025_pid_rx_info_t *pid_rx_info = &motor->kt9025_info->pid_info.rx;


	switch (ID)
	{
		case PID_RX_ID:
			pid_rx_info->angleKp = rxBuf[2];
			pid_rx_info->angleKi = rxBuf[3];
			pid_rx_info->speedKp = rxBuf[4];
			pid_rx_info->speedKi = rxBuf[5];
			pid_rx_info->iqKp	   = rxBuf[6];
			pid_rx_info->iqKi	   = rxBuf[7];
			break;
		
		case ACCEL_RX_ID:
			base_info->accel  = rxBuf[7];
			base_info->accel <<= 8;
			base_info->accel |= rxBuf[6];
			base_info->accel <<= 8;
			base_info->accel |= rxBuf[5];
			base_info->accel <<= 8;
			base_info->accel |= rxBuf[4];
			base_info->accel <<= 8;
			break;
		
		case ENCODER_RX_ID:
			state_info->encoder = rxBuf[3];
			state_info->encoder <<= 8;
			state_info->encoder |= rxBuf[2];
			state_info->encoderRaw = rxBuf[5];
			state_info->encoderRaw <<= 8;
			state_info->encoderRaw |= rxBuf[4];
			state_info->encoderOffset = rxBuf[7];
			state_info->encoderOffset <<= 8;
			state_info->encoderOffset |= rxBuf[6];
			break;
		
		case MOTOR_ANGLE_ID:
			base_info->motorAngle  = rxBuf[7];
			base_info->motorAngle <<= 8;
			base_info->motorAngle |= rxBuf[6];
			base_info->motorAngle <<= 8;
			base_info->motorAngle |= rxBuf[5];
			base_info->motorAngle <<= 8;
			base_info->motorAngle |= rxBuf[4];
			base_info->motorAngle <<= 8;
			base_info->motorAngle |= rxBuf[3];
			base_info->motorAngle <<= 8;
			base_info->motorAngle |= rxBuf[2];
			base_info->motorAngle <<= 8;
			base_info->motorAngle |= rxBuf[1];
			break;
		
		case CIRCLE_ANGLE_ID:
			base_info->circleAngle  = rxBuf[7];
			base_info->circleAngle <<= 8;
			base_info->circleAngle |= rxBuf[6];
			base_info->circleAngle <<= 8;
			base_info->circleAngle |= rxBuf[5];
			base_info->circleAngle <<= 8;
			base_info->circleAngle |= rxBuf[4];
			break;
		
		case STATE1_ID:
			state_info->temperature = rxBuf[1]; 
			state_info->voltage = rxBuf[4];
			state_info->voltage <<= 8;
			state_info->voltage |= rxBuf[3];
			state_info->errorState = rxBuf[7];
			break;
		
		case STATE2_ID:
			state_info->temperature = rxBuf[1];
			state_info->current = rxBuf[3];
			state_info->current <<= 8;
			state_info->current |= rxBuf[2];
			base_info->speed = rxBuf[5];
			base_info->speed <<= 8;
			base_info->speed |= rxBuf[4];
			state_info->encoder = rxBuf[7];
			state_info->encoder <<= 8;
			state_info->encoder |= rxBuf[6];
			break;
		
		case STATE3_ID:
			state_info->temperature = rxBuf[1];
			state_info->current_A = rxBuf[3];
			state_info->current_A <<= 8;
			state_info->current_A |= rxBuf[2];
			state_info->current_B = rxBuf[5];
			state_info->current_B <<= 8;
			state_info->current_B |= rxBuf[4];
			state_info->current_C = rxBuf[7];
			state_info->current_C <<= 8;
			state_info->current_C |= rxBuf[6];
			break;
		
		case POS_CLOSE2_ID:
			state_info->temperature = rxBuf[1];
			state_info->current = rxBuf[3];
			state_info->current <<= 8;
			state_info->current |= rxBuf[2];
			base_info->speed = rxBuf[5];
			base_info->speed <<= 8;
			base_info->speed |= rxBuf[4];
			state_info->encoder = rxBuf[7];
			state_info->encoder <<= 8;
			state_info->encoder |= rxBuf[6];
			break;
		
		case TORQUE_CLOSE_ID:
			state_info->temperature = rxBuf[1];
			state_info->current = rxBuf[3];
			state_info->current <<= 8;
			state_info->current |= rxBuf[2];
			base_info->speed = rxBuf[5];
			base_info->speed <<= 8;
			base_info->speed |= rxBuf[4];
			state_info->encoder = rxBuf[7];
			state_info->encoder <<= 8;
			state_info->encoder |= rxBuf[6];
			break;
		
		default:
			break;
	}
	
	if(!state_info->encoder_prev && !state_info->encoder_sum)
		err = 0;
	else
		err = state_info->encoder - state_info->encoder_prev;	
	
	/* 过零点 */
	if(m_abs(err) > 32767)
	{
		/* 0↓ -> 65535 */
		if(err >= 0)
			state_info->encoder_sum += -65535 + err;
		/* 65535 -> 0 */
		else
			state_info->encoder_sum += 65535 + err;
	}
	/* 未过零点 */
	else
	{
		state_info->encoder_sum += err;
	}	
	
	state_info->encoder_prev = state_info->encoder;	
	
	motor->state.offline_cnt = 0;
}




