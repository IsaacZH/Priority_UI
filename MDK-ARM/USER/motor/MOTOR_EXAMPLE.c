/*
* EXAMPLE
*	RP MOTOR_BAG
*	2022.11.6 
* AUTHOR CCB HXZP
*
*ʹ�õ��ǰ�������úõ�������͡�id�š�������ʽ���Լ�initָ�뺯����ʼ��
*ʹ��pidǰҲ��Ҫ����pid��ʼ���������޷�ʹ��
*����ֱ��ʹ�����ú�������pid���� Ҳ����ֱ��ʹ�ÿ��ڶ��庯�������Լ�����ĺ���
*ktϵ�е����ʹ��ktϵ�е��ǰ��Ҫ��ʵ����motor_9025_info_t������motor�ڵ�ָ����ϵ�����ಽ������
*/

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "MOTOR_EXAMPLE.h"
#include "motor.h"
#include "drv_can.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*---------------------------����Ϊ����-------------------------------------*/

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
* ʹ�õ��ǰ�������úõ�������͡�id�š�������ʽ
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
	��Ҫ����һ��������Ϊ�����������ʹ�ýṹ������Ϊ�����ʼ��չ��Ϊһά�Ŀ������Ƚϼ�Լ������Ҫ��ס���ǵ�λ�úͺ���
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
	��������
*/
//int16_t send_buff[4];
//float tar;


//void moto_init()
//{
	//	//�����ʼ��
//	motor[GIMB_Y].init(&motor[GIMB_Y]);
//	//����ٶ�pid��ʼ��
//	motor[GIMB_Y].pid_init(&motor[GIMB_Y].pid.speed,gimb_y_speed_pid_param);
//}

//void moto_control()
//{
//		//��������������ж��Ƿ�ʧ��
//		motor[GIMB_Y].heartbeat(&motor[GIMB_Y]);

////		//pid����
//		send_buff[motor[GIMB_Y].id.buff_p] = motor[GIMB_Y].c_speed(&motor[GIMB_Y],tar);


////		//�������ݵķ���
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















