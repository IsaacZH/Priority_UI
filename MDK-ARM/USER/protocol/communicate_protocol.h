#ifndef _COMMUNICATE_PROTOCOL_H
#define _COMMUNICATE_PROTOCOL_H

// 在这里添加你的头文件包含
#include "main.h"
#include "drv_can.h"
#include "config.h"
#include "string.h"
// 在这里添加你的宏定义
#define POWER_HEAT_DATA_TX_ID    (0x100)//power_heat_data发送ID
#define GAME_ROBOT_STATUS_TX_ID  (0x101)//game_robot_status发送ID
#define SHOOT_DATA_TX_ID         (0x102)//shoot_data发送ID
#define CHASSIS_DATA_RX_ID       (0x103)//上主控底盘包的ID
#define CAR_DATA_RX_ID					 (0X104)//上主控整车信息包ID

/**
 * @brief 机器人状态发送结构体
 * 
 */
typedef struct __packed
{
	uint16_t shooter_cooling_limit;			//机器人 42mm 枪口热量上限
	uint8_t car_color;                  //蓝色:2  红色:1
	uint16_t chassis_power_limit;       //底盘功率限制
	uint16_t keep_null_;                //保留位
	uint8_t keep_null;											
}game_robot_status_tx_info_t;

/**
 * @brief 底盘功率和枪口热量发送结构体
 * 
 */
typedef struct __packed
{
  int16_t chassis_power_buffer;       //底盘缓存功率
	uint16_t shooter_cooling_heat; 			//机器人 42mm 枪口热量
	uint8_t rfid;                       //高地RFID状态 1：刷上 0：没刷上
	uint16_t remain_HP;                 //剩余血量
	uint8_t game_process;               //比赛状态
}power_heat_data_tx_info_t;

/**
 * @brief 射速发送结构体
 * 
 */
typedef struct __packed
{
	float shooting_speed;               //射速
	uint32_t keep_null;							    //保留位
}shoot_data_tx_info_t;


/**
 * @brief 底盘包接受结构体
 * 
 */
typedef struct __packed
{
	int16_t target_front_speed;        //前进速度
	int16_t target_right_speed;				 //右移速度
	int16_t target_cycle_speed;				 //旋转速度
	int16_t chassis_max_speed;				 //底盘最大速度 
}chassis_data_rx_info_t;

/**
 * @brief 整车信息包接受结构体
 * 
 */
typedef struct __packed
{
	int16_t target_f_speed;//前摩擦轮目标速度
	int16_t big_number;//联盟赛：平衡步数字 0 3 4
	uint8_t target_bullet_speed;//目标闭环弹速*10
	uint8_t car_move_mode;//移动模式
	union 
	{
		uint16_t state;  //整车状态
		struct
		{
				uint16_t is_find_target : 1;//视觉是否找到目标
				uint16_t is_hit_enable : 1;//视觉是否允许打弹
				uint16_t is_on_cap : 1;//是否开超电
				uint16_t is_fire : 1;//是否单发
				uint16_t is_firing : 1;//是否连发
				uint16_t is_load_ok : 1;//是否装弹完成
				uint16_t is_head_forward : 1;//头是否朝前
				uint16_t is_tele_on : 1;//是否使用倍镜
				uint16_t is_image_up : 1;//图传是否朝上
				uint16_t is_key_ctrl : 1;//是否为键盘模式
				
		}bit;
	}car_state;
}car_data_rx_info_t;

/**
 * @brief 板间通信状态结构体
 * 
 */
typedef struct __packed
{
	Dev_Work_State_e car_data_state;			//工作状态
	uint8_t car_data_offline_cnt;					//离线计数
	
	Dev_Work_State_e chassis_data_state;	//底盘包状态（开控上主控才会发，用于判断有无开控）
	uint8_t chassis_data_offline_cnt;     //离线计数

	uint8_t offline_cnt_max;						  //离线最大计数
}communicate_status_t;

/**
 * @brief 板间通信总结构体
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

// 在这里添加你的函数声明
void Game_Robot_Status_Tx(void);
void Power_Heat_Data_Tx(void);
void Shoot_Data_Tx(void);
void Chassis_Data_Rx(uint8_t *rxBuf);
void Car_Data_Rx(uint8_t *rxBuf);
void Communicate_Heartbeat(void);
#endif 
