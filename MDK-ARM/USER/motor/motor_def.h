#ifndef __MOTOR_DEF_H
#define __MOTOR_DEF_H

#include "stm32f4xx_hal.h"

//RM2006 RM3508
#define RM_F_ID 0x200
#define RM_B_ID 0x1FF
//GM6020
#define GM_F_ID 0x1FF
#define GM_B_ID 0x2FF


/* 机腿命令字节枚举 */
typedef enum 
{
	PID_RX_ID									 = 0x30,
	PID_TX_RAM_ID							 = 0x31,
	PID_TX_ROM_ID							 = 0x32,
	ACCEL_RX_ID								 = 0x33,
	ACCEL_TX_ID								 = 0x34,
	ENCODER_RX_ID							 = 0x90,
	ZERO_ENCODER_TX_ID				 = 0x91,	
	ZERO_POSNOW_TX_ID					 = 0x19,	
	
	MOTOR_ANGLE_ID						 = 0x92,
	CIRCLE_ANGLE_ID						 = 0x94,
	STATE1_ID									 = 0x9A,
	CLEAR_ERROR_State_ID			 = 0x9B,
	STATE2_ID									 = 0x9C,
	STATE3_ID									 = 0x9D,
	MOTOR_STOP_ID							 = 0x80,
	MOTOR_CLOSE_ID						 = 0x81,
	MOTOR_RUN_ID							 = 0x88,
	
	TORQUE_OPEN_ID 			 		 	 = 0xA0,
	TORQUE_CLOSE_ID 			 		 = 0xA1,
	SPEED_CLOSE_ID 			 	 		 = 0xA2,
	POS_CLOSE1_ID 			 		 	 = 0xA3,
	POS_CLOSE2_ID 			 		   = 0xA4,
	POS_CLOSE3_ID 			 		 	 = 0xA5,
	POS_CLOSE4_ID 			 		 	 = 0xA6,
	POS_CLOSE5_ID 			 		 	 = 0xA7,
	POS_CLOSE6_ID 			 		   = 0xA8,
	
	
}motor_kt9025_command_e;



typedef enum 
{
	M_OFFLINE = 0,	
	
	M_ONLINE,

	M_TYPE_ERR,
	M_ID_ERR,
	M_INIT_ERR,	
	M_DATA_ERR,
	
}motor_state_e;//电机状态，失联为最高优先级

typedef enum{

	M_DEINIT = 0,		//	未初始化
	M_INIT,					//	初始化成功

}motor_init_e;//初始化枚举

typedef enum{
	M_CAN1,
	M_CAN2,
	
	M_PWM,

	M_USART1,
	M_USART2,
	M_USART3,	
	M_USART4,
	M_USART5,

}motor_drive_e;//电机驱动通信方式

typedef enum{
	
	GM6020 = 1,
	RM3508,
	RM2006,

	KT9015 = 4,
	KT9025,
	
}motor_type_e;//电机类型

typedef enum {
	MOTOR_F,
	MOTOR_B
} motor_dir_t;//电机方向


/*-----------------------------------------------------------------*/

typedef struct 
{
	int16_t		angle;						//0~8191 //电机最初始的信息
	int16_t 	speed;						//RPM    //电机速度
	int16_t 	current;					//       //实际转矩
	int16_t		temperature;			//°C    //温度
	int16_t 	torque;		
	
	int16_t		angle_prev;				// 先前角度
	int16_t		angle_offset;			//       //偏执 自定义角度范围
	int32_t		angle_sum;				//-2147683647~2147683647 上电开始到现在的角度和
	
}motor_rx_info_t;

typedef struct 
{
	int16_t     mec_mid;  			//机械中值
	motor_dir_t dir;	    			//方向
	
}motor_mec_info_t;						//机械信息

typedef struct
{
	int16_t		motor_out;
	float			pid_out;
	uint32_t  lock_cnt;
}motor_base_info_t;

typedef struct
{
	uint32_t tx_id;   					//发送id
	uint32_t rx_id;   					//接收id
	uint32_t buff_p;  					//发送/接收 数组位置
	
	motor_drive_e drive_type; 
	motor_type_e  motor_type;
	
}motor_id_info_t;							//电机的ID信息

typedef struct
{
	motor_init_e  init_flag;	
	
	uint8_t       offline_cnt_max;
	uint8_t       offline_cnt;

	motor_state_e work_state;	
	
}motor_state_info_t;//电机的ID信息
/*-----------------------------------------------------------------*/

typedef struct 
{
	float	  target;
	float	  measure;
	float 	err;
	float 	last_err;
	
	float	  integral;
	
	float 	pout;
	float 	iout;
	float 	dout;
	float 	out;
	
	motor_init_e init_flag;
	
}motor_pid_info_t; //pid信息

typedef struct 
{
	/* 配置 */
	float	  kp;
	float 	ki;
	float 	kd;
	
	float   blind_err;	
	float 	integral_max;	
	float   iout_max;
	float 	out_max;
	
}motor_pid_set_t; //pid设置

typedef struct motor_pid
{
	motor_pid_info_t info;
	motor_pid_set_t  set;
	
}motor_pid_t; //pid最小单位


typedef struct
{
	motor_pid_t            speed;
	
	motor_pid_t            angle;	
	motor_pid_t            angle_in;		
	
	motor_pid_t            position;
	motor_pid_t            position_in;	
	
		
	motor_pid_t            gyro_in;	
	motor_pid_t            gyro_out;
			
	motor_pid_t            mec_in;	
	motor_pid_t            mec_out;
	
	motor_pid_t            user_define;
	
}motor_pid_all_t; //pid总汇


/*-----------------------------------------------------------------
 * KT9025
-----------------------------------------------------------------*/

typedef struct motor_9025_pid_rx_info_t
{
	uint8_t angleKp;
	uint8_t angleKi;
	uint8_t speedKp;
	uint8_t speedKi;
	uint8_t iqKp;
	uint8_t iqKi;
	
}motor_9025_pid_rx_info_t;

typedef struct motor_9025_pid_tx_info_t
{
	uint8_t angleKp;
	uint8_t angleKi;
	uint8_t speedKp;
	uint8_t speedKi;
	uint8_t iqKp;
	uint8_t iqKi;
	
}motor_9025_pid_tx_info_t;

typedef struct motor_9025_pid_info_t
{
	motor_9025_pid_rx_info_t rx;
	motor_9025_pid_tx_info_t tx;
	
}motor_9025_pid_info_t;

typedef struct motor_9025_state_info_t
{
	int8_t    temperature;       //°C
	uint16_t  voltage;					 //V
	uint8_t		errorState;				 //低四位0000都正常；0001温度正常+低压保护；1000过温保护+电压正常；1001都寄
	int16_t   current;           //转矩电流-2048~2048（-33~33A）
	uint16_t 	encoder;					 //编码器位置（0~16383）
	uint16_t 	encoder_prev;			 //编码器前位置（0~16383）
	uint16_t 	encoder_sum;			 //编码器总位置
	uint16_t 	encoderRaw;				 //编码器原始位置（0~16383）
	uint16_t 	encoderOffset;		 //编码器零偏（0~16383）
	int16_t 	current_A;				 //ABC三相电流数据 1A/64LSB
	int16_t 	current_B;
	int16_t 	current_C;
}motor_9025_state_info_t;

typedef struct motor_9025_info_t
{
	motor_9025_pid_info_t				 pid_info;
	motor_9025_state_info_t			 state_info;
	
	int32_t   circleAngle;       //电机单圈角度（0~36000*减速比-1）
	int64_t   motorAngle;        //-2^63~2^63
	int16_t   speed;             //电机转速（dps）（max = ）
	int16_t 	accel;						 //加速度 1dps/s
	int16_t   angle_add;         //-4096~4096
	
}motor_9025_info_t;


#endif


