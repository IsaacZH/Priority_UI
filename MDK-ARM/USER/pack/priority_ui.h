/**
 * @file priority_ui.h
 * @author Isaac (1812924685@qq.com)
 * @brief 通过优先队列实现UI优先级调度
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _PRIORITY_UI_H
#define _PRIORITY_UI_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include "ui_protocol.h"


/* Exported enum ------------------------------------------------------------*/

/**
 * @brief UI优先级枚举
 * 
 */
typedef enum {
  LOW_PRIORITY = 0,  // 低优先级(动态UI中不需要高刷新率的)
  MID_PRIORITY,      // 中优先级(动态UI中需要一定刷新率的)
  HIGH_PRIORITY,     // 高优先级(动态UI中需要高刷新率的)
}ui_priority_e;

/**
 * @brief 发送模式枚举
 * 
 */
typedef enum
{
  SEND_CHAR_MODE = 0,
  SEND_GRAPHIC_MODE,
} ui_send_mode_e;

/**
 * @brief UI发送状态枚举
 * 
 */
typedef enum {
    MESSAGE_SENT = 0, // 消息已发送
    MESSAGE_NOT_SENT, // 消息更新后未发送
} ui_sent_state_e;

typedef enum {
  LINE = 0,  // 直线
  RECTANGEL, // 矩形
  CIRCLE,    // 圆
  ELLIPSE,   // 椭圆
  ARC,       // 圆弧
  FLOAT,     // 浮点数
  INT,       // 整数
  CHAR,      // 字符
} ui_type_e;

/**
 * @brief 函数返回状态
 * 
 */
typedef enum 
{
  UI_ERROR    ,
  UI_OK       ,
  UI_BUSY     ,
} ui_status_e;

/* Exported struct ------------------------------------------------------------*/

/**
 * @brief UI配置信息结构体
 * 
 */
typedef struct __packed {
  /*******不变配置*********/
  ui_priority_e priority;       // UI优先级(仅动态UI需要配置)
  ui_type_e ui_type;            // UI内容类型
  char *name;                   // 图形名称

  /*******可变配置*********/

  /*******通用配置********/
  operate_tpye_e operate_type; // 操作类型
  uint8_t layer;           // 图层数，0~9
  graphic_color_e color;   // 颜色
  uint16_t width;          // 线条宽度
  uint16_t start_x;        // 起点 x 坐标
  uint16_t start_y;        // 起点 y 坐标
  uint16_t end_x;          // 终点 x 坐标
  uint16_t end_y;          // 终点 y 坐标
  /*******特殊配置********/
  uint16_t radius;      // 圆：半径
  uint16_t start_angel; // 圆弧：起始角度
  uint16_t end_angel;   // 圆弧：终止角度
  uint16_t size;        // 文字数字：字体大小
  float float_num;      // 浮点数: 显示的数字
  uint16_t decimal;     // 浮点数：小数位有效个数
  int32_t int_num;      // 整数: 显示的数字
  char text[30];        // 字符串：显示的文字
} ui_config_t;

/**
 * @brief UI信息结构体
 * 
 */
typedef struct __packed {
  ui_sent_state_e sent_state; // 消息发送状态标志位
  uint32_t updateTick;             // 更新消息时的时间戳
  uint16_t  priority_value;        // UI的优先级值
  ui_config_t ui_config;           // 用户配置UI信息
} ui_info_t;

/**
 * @brief UI链表节点结构体
 * 
 */
typedef struct Node_u 
{
  ui_info_t *ui;
  struct Node_u *next;
} Node_u;



/* Exported functions --------------------------------------------------------*/
void Init_Ui_List(ui_info_t *dynamic_ui_info, uint8_t dynamic_ui_num, ui_info_t *const_ui_info, uint8_t const_ui_num);
void Ui_Send();
ui_status_e Enqueue_Ui_For_Sending(ui_info_t *ui_info);
#endif