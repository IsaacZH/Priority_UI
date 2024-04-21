#ifndef _COMMUNICATE_PROTOCOL_H
#define _COMMUNICATE_PROTOCOL_H

// ������������ͷ�ļ�����
#include "main.h"
#include "drv_can.h"
#include "config.h"
#include "string.h"
// �����������ĺ궨��
#define POWER_HEAT_DATA_TX_ID    (0x100)//power_heat_data����ID
#define GAME_ROBOT_STATUS_TX_ID  (0x101)//game_robot_status����ID
#define SHOOT_DATA_TX_ID         (0x102)//shoot_data����ID
#define CHASSIS_DATA_RX_ID       (0x103)//�����ص��̰���ID
#define CAR_DATA_RX_ID					 (0X104)//������������Ϣ��ID

/**
 * @brief ������״̬���ͽṹ��
 * 
 */
typedef struct __packed
{
	uint16_t shooter_cooling_limit;			//������ 42mm ǹ����������
	uint8_t car_color;                  //��ɫ:2  ��ɫ:1
	uint16_t chassis_power_limit;       //���̹�������
	uint16_t keep_null_;                //����λ
	uint8_t keep_null;											
}game_robot_status_tx_info_t;

/**
 * @brief ���̹��ʺ�ǹ���������ͽṹ��
 * 
 */
typedef struct __packed
{
  int16_t chassis_power_buffer;       //���̻��湦��
	uint16_t shooter_cooling_heat; 			//������ 42mm ǹ������
	uint8_t rfid;                       //�ߵ�RFID״̬ 1��ˢ�� 0��ûˢ��
	uint16_t remain_HP;                 //ʣ��Ѫ��
	uint8_t game_process;               //����״̬
}power_heat_data_tx_info_t;

/**
 * @brief ���ٷ��ͽṹ��
 * 
 */
typedef struct __packed
{
	float shooting_speed;               //����
	uint32_t keep_null;							    //����λ
}shoot_data_tx_info_t;


/**
 * @brief ���̰����ܽṹ��
 * 
 */
typedef struct __packed
{
	int16_t target_front_speed;        //ǰ���ٶ�
	int16_t target_right_speed;				 //�����ٶ�
	int16_t target_cycle_speed;				 //��ת�ٶ�
	int16_t chassis_max_speed;				 //��������ٶ� 
}chassis_data_rx_info_t;

/**
 * @brief ������Ϣ�����ܽṹ��
 * 
 */
typedef struct __packed
{
	int16_t target_f_speed;//ǰĦ����Ŀ���ٶ�
	int16_t big_number;//��������ƽ�ⲽ���� 0 3 4
	uint8_t target_bullet_speed;//Ŀ��ջ�����*10
	uint8_t car_move_mode;//�ƶ�ģʽ
	union 
	{
		uint16_t state;  //����״̬
		struct
		{
				uint16_t is_find_target : 1;//�Ӿ��Ƿ��ҵ�Ŀ��
				uint16_t is_hit_enable : 1;//�Ӿ��Ƿ������
				uint16_t is_on_cap : 1;//�Ƿ񿪳���
				uint16_t is_fire : 1;//�Ƿ񵥷�
				uint16_t is_firing : 1;//�Ƿ�����
				uint16_t is_load_ok : 1;//�Ƿ�װ�����
				uint16_t is_head_forward : 1;//ͷ�Ƿ�ǰ
				uint16_t is_tele_on : 1;//�Ƿ�ʹ�ñ���
				uint16_t is_image_up : 1;//ͼ���Ƿ���
				uint16_t is_key_ctrl : 1;//�Ƿ�Ϊ����ģʽ
				
		}bit;
	}car_state;
}car_data_rx_info_t;

/**
 * @brief ���ͨ��״̬�ṹ��
 * 
 */
typedef struct __packed
{
	Dev_Work_State_e car_data_state;			//����״̬
	uint8_t car_data_offline_cnt;					//���߼���
	
	Dev_Work_State_e chassis_data_state;	//���̰�״̬�����������زŻᷢ�������ж����޿��أ�
	uint8_t chassis_data_offline_cnt;     //���߼���

	uint8_t offline_cnt_max;						  //����������
}communicate_status_t;

/**
 * @brief ���ͨ���ܽṹ��
 * 
 */
typedef struct __packed
{
	game_robot_status_tx_info_t *game_robot_status_tx_info;
	power_heat_data_tx_info_t   *power_heat_data_tx_info;
	shoot_data_tx_info_t        *shoot_data_tx_info;
	chassis_data_rx_info_t      *chassis_data_rx_info;
	car_data_rx_info_t          *car_data_rx_info;
	communicate_status_t        *status;
}communicate_t;

extern communicate_t communicate;

// �����������ĺ�������
void Game_Robot_Status_Tx(void);
void Power_Heat_Data_Tx(void);
void Shoot_Data_Tx(void);
void Chassis_Data_Rx(uint8_t *rxBuf);
void Car_Data_Rx(uint8_t *rxBuf);
void Communicate_Heartbeat(void);
#endif 
