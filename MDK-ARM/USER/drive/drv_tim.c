/**
 * @file        drv_tim.c
 * @author      RobotPilots@2020
 * @Version     V1.0
 * @date        
 * @brief       TIMER Driver Package(Based on HAL).
 */

/* Includes ------------------------------------------------------------------*/
#include "drv_tim.h"
#include "main.h"
extern TIM_HandleTypeDef htim11;
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void PWM_Init(void)
{
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
	BUZZER_PwmOut(0);
}


//168000000 168 500 2kHz 占空比x/100
//168000000 642 1000 263Hz 占空比x/1000
//PE11
void BUZZER_PwmOut(int16_t pwm)
{
	pwm*=5;
	if(pwm>500)
		pwm=500;
	else if(pwm<0)
		pwm=0;
	
//	int16_t pwm_t=168000000/(pwm*642);
		
	
 	SERVO_PWM = pwm;
}


void BUZZER_SLEEP(void)
{
	HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);
}	

void BUZZER_WEAK(void)
{
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
}
