#include "test_task.h"
#include "main.h"
#include "cmsis_os.h"
#include "led.h"
#include "buzzer.h"
#include "my_chassis.h"
#include "drv_can.h"
#include "my_posture.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

/**
  * @brief          test task
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
/**
  * @brief          test»ŒŒÒ
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
void Above_Normal_1(void const * argument)
{
//	  aRGB_led_off();
    while(1)
    {
			My_Posture_Update();
			
			My_Chassis_HeartBeat();
			
			My_Chassis_Data_Update();
			
			My_Chassis_Ctrl();
			
      osDelay(1);
    }
}



