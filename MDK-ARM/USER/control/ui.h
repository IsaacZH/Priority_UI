#ifndef __UI_H
#define __UI_H

#include "main.h"

typedef enum{
	RP_1,
	RP_2,
	RP_3,
	RP_4,
	RP_5,
	RP_6,
	RP_7,
	RP_8,
	RP_9,
	VISION_CYCLE_1,
	VISION_CYCLE_2,
	TOP_MODE_CYCLE_1,
	TOP_MODE_CYCLE_2,
	NUM,
	
}dynamic_ui_cnt_e;


void My_Ui_Init(void);
void Ui_Info_Update(void);
#endif