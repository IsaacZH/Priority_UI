#ifndef __DRV_TIM_H
#define __DRV_TIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported macro ------------------------------------------------------------*/

#define SERVO_PWM	  TIM11->CCR1

/* Exported types ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void PWM_Init(void);
void BUZZER_PwmOut(int16_t pwm);
void BUZZER_SLEEP(void);
void BUZZER_WEAK(void);
#endif
