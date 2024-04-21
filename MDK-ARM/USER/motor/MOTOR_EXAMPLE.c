/*
* EXAMPLE
*	RP MOTOR_BAG
*	2022.11.6 
* AUTHOR CCB HXZP
*
*使用电机前必须配置好电机的类型、id号、驱动方式，以及init指针函数初始化
*使用pid前也需要进行pid初始化，否则无法使用
*可以直接使用内置函数进行pid控制 也可以直接使用库内定义函数或者自己定义的函数
*kt系列电机：使用kt系列电机前需要先实例化motor_9025_info_t，再与motor内的指针联系，其余步骤无异
*/

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "MOTOR_EXAMPLE.h"
#include "motor.h"
#include "drv_can.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*---------------------------以下为正文-------------------------------------*/

//typedef enum
//{
//	CHAS_FL = 0,
//	CHAS_FR,
//	CHAS_BL,
//	CHAS_BR,
//	
//	GIMB_Y,
//	GIMB_P,
//	GIMB_R,
//	
//	MOTOR_LIST,
//}motor_list_e;


/*
* 使用电机前必须配置好电机的类型、id号、驱动方式
*/
//motor_t motor[MOTOR_LIST] =
//{
//	[GIMB_Y] = {
//	
//		.id.drive_type = M_CAN1,
//		.id.motor_type = GM6020,
//		.id.rx_id = 0x666,
//		
//		.init = Motor_Class_Init,
//	}
//};


/*
	需要定义一个数组作为传入参数，不使用结构体是因为数组初始化展开为一维的看起来比较简约，但是要记住他们的位置和含义
	float	  kp;
	float 	ki;
	float 	kd;
	
	float   blind_err;	
	float 	integral_max;	
	float   iout_max;
	float 	out_max;
*/
																		/*kp		ki		kd		b_err		int_max		iout_max		out_max*/
//float gimb_y_speed_pid_param[7] = {		5,		0,		0,		0,			0,				15000,			20000};

/*	
	发送数组
*/
//int16_t send_buff[4];
//float tar;


//void moto_init()
//{
	//	//电机初始化
//	motor[GIMB_Y].init(&motor[GIMB_Y]);
//	//电机速度pid初始化
//	motor[GIMB_Y].pid_init(&motor[GIMB_Y].pid.speed,gimb_y_speed_pid_param);
//}

//void moto_control()
//{
//		//电机心跳，用于判断是否失联
//		motor[GIMB_Y].heartbeat(&motor[GIMB_Y]);

////		//pid计算
//		send_buff[motor[GIMB_Y].id.buff_p] = motor[GIMB_Y].c_speed(&motor[GIMB_Y],tar);


////		//控制数据的发送
//		CAN1_Send_With_int16_to_uint8(motor[GIMB_Y].id.tx_id,send_buff);
//}

//void StartControlTask(void const * argument)
//{
//	
//moto_init()
//	
//  for(;;)
//  {

//	
//		moto_control();
//		
//		
//    osDelay(1);
//  }

//}















