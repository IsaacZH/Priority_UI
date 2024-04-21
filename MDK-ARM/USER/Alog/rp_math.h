#ifndef __MY_MATH_H
#define __MY_MATH_H

#include "stm32f4xx_hal.h"
#include "math_support.h"

/* ÊýÖµº¯Êý */
//#define constrain(x, min, max)	((x>max)?max:(x<min?min:x))
#define abs(x) 					((x)>0? (x):(-(x)))
#define one(x)					((x)>0? (1):(-1))
#define sgn(x) (((x)>0)?1:((x)<0?-1:0))
int16_t RampInt(int16_t final, int16_t now, int16_t ramp);
float RampFloat(float final, float now, float ramp);
float DeathZoom(float input, float center, float death);

#endif

