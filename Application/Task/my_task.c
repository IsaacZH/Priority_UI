#include "my_task.h"
#include "cmsis_os.h"
#include "drv_haltick.h"
#include "ui.h"
#include "priority_ui.h"

void Task_H1(void const * argument)
{

  for(;;)
  {

		Ui_Info_Update();
		Ui_Send();
    osDelay(1);
  }
}



void Task_H2(void const * argument)
{

  for(;;)
  {
		
			
    osDelay(1);
  }
}



void Task_M(void const * argument)
{


  for(;;)
  {


		
    osDelay(1);
  }

}












