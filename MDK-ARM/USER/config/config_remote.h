/**
  ******************************************************************************
  * @file           : config_remote.c\h
  * @brief          : 
  * @note           : 
  ******************************************************************************
  */

#ifndef __CONFIG_REMOTE_H
#define __CONFIG_REMOTE_H

#define REMOTE_OFFLINE_CNT_MAX  50          //遥控器失联计数上限
/*摇杆最大值*/
#define RC_CNT_MAX							(660.f)
/* 检测按键长按时间 */
#define MOUSE_BTN_L_CNT_MAX     500         //ms 鼠标左键
#define MOUSE_BTN_R_CNT_MAX     500         //ms 鼠标右键
#define KEY_Q_CNT_MAX           500         //ms Q键
#define KEY_W_CNT_MAX           1000        //ms W键
#define KEY_E_CNT_MAX           500         //ms E键
#define KEY_R_CNT_MAX           500         //ms R键
#define KEY_A_CNT_MAX           1000        //ms A键
#define KEY_S_CNT_MAX           1000        //ms S键
#define KEY_D_CNT_MAX           1000        //ms D键
#define KEY_F_CNT_MAX           500         //ms F键
#define KEY_G_CNT_MAX           500         //ms G键
#define KEY_Z_CNT_MAX           500         //ms Z键
#define KEY_X_CNT_MAX           500         //ms X键
#define KEY_C_CNT_MAX           500         //ms C键
#define KEY_V_CNT_MAX           500         //ms V键
#define KEY_B_CNT_MAX           500         //ms B键
#define KEY_SHIFT_CNT_MAX       500         //ms SHIFT键
#define KEY_CTRL_CNT_MAX        500         //ms CTRL键
/* 平滑滤波次数 */
#define REMOTE_SMOOTH_TIMES     5          //鼠标平滑滤波次数
/* 旋钮临界值 */
#define WHEEL_JUMP_VALUE        550         //旋钮跳变判断值

#endif
