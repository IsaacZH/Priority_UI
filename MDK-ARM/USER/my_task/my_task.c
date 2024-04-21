#include "my_task.h"
#include "device.h"
#include "priority_ui.h"
#include "ui.h"
#include "drive.h"
#include "judge_protocol.h"
#include "communicate_protocol.h"
#include "can_protocol.h"
/**
  * @Name    StartControlTask
  * @brief   控制任务
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
extern IWDG_HandleTypeDef hiwdg;
uint8_t two_cnt=0;
void StartControlTask(void const * argument)
{
	Drive_Init();
  Device_Init();
  for(;;)
  {
    Device_Work();
    
    Ui_Info_Update();
    

    CAN_Send();
    CAP_txMessage();

		HAL_IWDG_Refresh(&hiwdg);
		osDelay(1);
  }
}

/**
  * @Name    StartRealTimeTask
  * @brief   实时任务更新
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void StartRealTimeTask(void const * argument)
{
	for(;;)
  {
		Ui_Send();
//		tick_task(1);
    osDelay(1);
  }
}

/**
  * @Name    StartHeartBeatTask
  * @brief   监控任务
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
void StartHeartBeatTask(void const * argument)
{
  for(;;)
  {
    Device_HeartBeat();
    
    Communicate_Heartbeat();//板间通信心跳
		check_judge_offline(&judge);
    osDelay(1);
  }
}



