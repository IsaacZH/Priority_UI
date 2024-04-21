#include "my_task.h"
#include "priority_ui.h"
#include "drive.h"
#include "ui.h"
/**
  * @Name    StartControlTask
  * @brief   ��������
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
  * @brief   ʵʱ�������
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
  * @brief   �������
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



