#include "my_task.h"
#include "priority_ui.h"
#include "drive.h"
#include "ui.h"
/**
  * @Name    StartControlTask
  * @brief   控制任务
  * @param   
  * @retval 
  * @author  
  * @Date    
**/
extern IWDG_HandleTypeDef hiwdg;
void StartControlTask(void const * argument)
{
	Drive_Init();
  for(;;)
  {
    Ui_Info_Update();

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
    osDelay(1);
  }
}



