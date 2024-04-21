#ifndef __MOTOR_H
#define __MOTOR_H

#include "motor_def.h"


#define m_abs(x) 					((x)>0? (x):(-(x)))
#define m_constrain(x, min, max)	((x>max)?max:(x<min?min:x))
#define m_anti_constrain(x, min, max)	(((x<max) && (x>min))?(0):x)




typedef struct motor_class_t
{
	motor_rx_info_t        rx_info;
	motor_state_info_t     state;
	motor_id_info_t        id;
  motor_mec_info_t       mec_info;
	motor_pid_all_t        pid;
	motor_base_info_t			 base_info;
	
	motor_9025_info_t      *kt9025_info;
	
	void (*init)(struct motor_class_t *motor);
	void (*heartbeat)(struct motor_class_t *motor);
  void (*pid_init)(motor_pid_t *pid, float *buff);	
	
	uint8_t (*tx)(struct motor_class_t *motor, uint8_t *buff,uint8_t len);
	uint8_t (*rx)(struct motor_class_t *motor, uint8_t *buff,uint8_t len);
	
	/*以下为控制函数*/
	float (*c_posit)(struct motor_class_t *motor,float target);
	float (*c_angle)(struct motor_class_t *motor,float target);	
	float (*c_speed)(struct motor_class_t *motor,float target);	
	float (*c_pid2)(motor_pid_t *out, motor_pid_t *inn, float meas1, float meas2, float tar, char err_cal_mode);	
	float (*c_pid1)(motor_pid_t *out, float meas1, float tar);	
	
	void  (*c_judge_dir)(struct motor_class_t *motor,uint16_t range);	
  void  (*c_offset)(struct motor_class_t *motor, uint16_t range);	
	
  uint8_t (*c_stuck_flag)(struct motor_class_t *motor);	
	
}motor_t;




void Motor_Class_Init(struct motor_class_t *motor);
void Motor_Class_HeartBeat(struct motor_class_t *motor);
void Motor_Class_Pid_Init(motor_pid_t *pid, float *buff);
uint8_t motor_class_stucking_flag(struct motor_class_t *motor);

void get_rm_can_drvie(struct motor_class_t *motor);
void get_rm_info(struct motor_class_t *motor, uint8_t *rxBuf);

void get_kt_9025_info(struct motor_class_t *motor, uint8_t *rxBuf);

float motor_cycle(float tar,float cycle);
float motor_half_cycle(float angle,float max);
void  motor_judge_dir(struct motor_class_t *motor,uint16_t range);
void  motor_offset(struct motor_class_t *motor, uint16_t range);

float motor_pid_err(motor_pid_t *pid,float measure);
float motor_pid_cal(motor_pid_t *pid);
float motor_pid_ctrl(motor_pid_t *out, motor_pid_t *inn, float meas1, float meas2, char err_cal_mode);
float KTmotor_pid_ctrl(motor_pid_t *out, motor_pid_t *inn, float meas1, float meas2, char err_cal_mode);

float motor_pid_position(struct motor_class_t *motor,float target);
float motor_pid_angle(struct motor_class_t *motor,float target);
float motor_pid_speed(struct motor_class_t *motor,float target);

float motor_pid_double(motor_pid_t *out, motor_pid_t *inn, float meas1, float meas2, float tar, char err_cal_mode);
float motor_pid_single(motor_pid_t *out, float meas1, float tar);


#endif

