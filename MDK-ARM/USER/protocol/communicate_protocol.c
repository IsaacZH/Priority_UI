#include "communicate_protocol.h"
#include "judge_protocol.h"


game_robot_status_tx_info_t game_robot_status_tx_info;
power_heat_data_tx_info_t power_heat_data_tx_info;
shoot_data_tx_info_t shoot_data_tx_info;
chassis_data_rx_info_t chassis_data_rx_info;
car_data_rx_info_t car_data_rx_info;

communicate_status_t communicate_status =
{
  .chassis_data_offline_cnt = 0,
  .chassis_data_state = DEV_OFFLINE,
  
  .car_data_offline_cnt = 0,
  .car_data_state = DEV_OFFLINE,

  .offline_cnt_max = 50,
};

communicate_t communicate =
{
  .game_robot_status_tx_info = &game_robot_status_tx_info,
  .power_heat_data_tx_info = &power_heat_data_tx_info,
  .shoot_data_tx_info = &shoot_data_tx_info,
  .chassis_data_rx_info = &chassis_data_rx_info,
  .car_data_rx_info = &car_data_rx_info,
  .status = &communicate_status,
};

extern CAN_HandleTypeDef hcan1;

/**
  * @name    Power_Heat_Data_Tx
  * @brief   机器人功率热量数据发送给上主控
  * @param   
  * @retval  None
  * @note 在接收到power_heat_data数据后，调用此函数
  */
void Power_Heat_Data_Tx(void)
{
  power_heat_data_tx_info_t *tx_info = &power_heat_data_tx_info;
  uint8_t tx_buff[8];
  uint32_t txMailBox;

  tx_info->chassis_power_buffer = judge.power_heat_data.chassis_power_buffer;
  tx_info->shooter_cooling_heat = judge.power_heat_data.shooter_id1_42mm_cooling_heat;
  if (judge.rfid_status.rfid_status == 0x02)
  {
    tx_info->rfid = 1;
  }
  else
  {
    tx_info->rfid = 0;
  }
  tx_info->remain_HP = judge.game_robot_status.current_HP;
  tx_info->game_process = judge.game_status.game_progress;

  memcpy(tx_buff, tx_info, sizeof(power_heat_data_tx_info_t));
  HAL_CAN_TxHeadeInit(POWER_HEAT_DATA_TX_ID);//配置ID
  HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeadeType,tx_buff,&txMailBox);
}

/**
  * @name    Game_Robot_Status_Tx
  * @brief   机器人状态发送给上主控
  * @param   
  * @retval  None
  * @note 在接收到game_robot_status数据后，调用此函数
  */
void Game_Robot_Status_Tx(void)
{
  game_robot_status_tx_info_t *tx_info = &game_robot_status_tx_info;
  uint8_t tx_buff[8];
  uint32_t txMailBox;
  
  //机器人 42mm 枪口热量上限
  tx_info->shooter_cooling_limit = \
    judge.game_robot_status.shooter_barrel_heat_limit;
  //判断自己是什么颜色
  if (judge.game_robot_status.robot_id <= 10)
  {
    tx_info->car_color = 0;//红方
  }
  else
  {
    tx_info->car_color = 1;//蓝方
  }
  //底盘功率限制
  tx_info->chassis_power_limit = judge.game_robot_status.chassis_power_limit;
  
  //发送数据
  memcpy(tx_buff, tx_info, sizeof(game_robot_status_tx_info_t));
  HAL_CAN_TxHeadeInit(GAME_ROBOT_STATUS_TX_ID);//配置ID
	HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeadeType,tx_buff,&txMailBox);
}

/**
  * @name    Shoot_Data_Tx
  * @brief   射击数据发送给上主控
  * @param   
  * @retval  None
  * @note 在接收到shoot_data数据后，调用此函数
  */
void Shoot_Data_Tx(void)
{
  shoot_data_tx_info_t *tx_info = &shoot_data_tx_info;
  uint8_t tx_buff[8];
  uint32_t txMailBox;
  
  tx_info->shooting_speed = judge.shoot_data.bullet_speed;
  
  memcpy(tx_buff, tx_info, sizeof(shoot_data_tx_info_t));
  HAL_CAN_TxHeadeInit(SHOOT_DATA_TX_ID);//配置ID
  HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeadeType,tx_buff,&txMailBox);
}

/**
 * @brief 底盘信息接受
 * 
 * @param rxBuf 
 */
void Chassis_Data_Rx(uint8_t *rxBuf)
{
  memcpy(&chassis_data_rx_info, rxBuf, sizeof(chassis_data_rx_info_t));
  communicate.status->chassis_data_offline_cnt = 0;
}

/**
 * @brief 整车信息接受
 * 
 * @param rxBuf 
 */
void Car_Data_Rx(uint8_t *rxBuf)
{
  memcpy(&car_data_rx_info,rxBuf,sizeof(car_data_rx_info_t));
  communicate.status->car_data_offline_cnt = 0;
}

/**
 * @brief 通信心跳 监控任务中调用
 * 
 */
void Communicate_Heartbeat(void)
{
	uint8_t offline_cnt_max = communicate.status->offline_cnt_max;
  //整车信息包接受心跳
  communicate.status->car_data_offline_cnt ++;
	if(communicate.status->car_data_offline_cnt > offline_cnt_max)
  {
    communicate.status->car_data_offline_cnt = offline_cnt_max;
    communicate.status->car_data_state = DEV_OFFLINE;
  }
  else if(communicate.status->car_data_state == DEV_OFFLINE)
  {
    communicate.status->car_data_state = DEV_ONLINE;
  }
  //底盘包接受心跳 用于判断是否开控
  communicate.status->chassis_data_offline_cnt ++;
	if(communicate.status->chassis_data_offline_cnt > offline_cnt_max)
  {
    communicate.status->chassis_data_offline_cnt = offline_cnt_max;
    communicate.status->chassis_data_state = DEV_OFFLINE;
  }
  else if(communicate.status->chassis_data_state == DEV_OFFLINE)
  {
    communicate.status->chassis_data_state = DEV_ONLINE;
  }
}