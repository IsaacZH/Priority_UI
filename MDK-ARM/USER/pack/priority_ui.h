/**
 * @file priority_ui.h
 * @author Isaac (1812924685@qq.com)
 * @brief ͨ�����ȶ���ʵ��UI���ȼ�����
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
 * @brief UI���ȼ�ö��
 * 
 */
typedef enum {
  LOW_PRIORITY = 0,  // �����ȼ�(��̬UI�в���Ҫ��ˢ���ʵ�)
  MID_PRIORITY,      // �����ȼ�(��̬UI����Ҫһ��ˢ���ʵ�)
  HIGH_PRIORITY,     // �����ȼ�(��̬UI����Ҫ��ˢ���ʵ�)
}ui_priority_e;

/**
 * @brief ����ģʽö��
 * 
 */
typedef enum
{
  SEND_CHAR_MODE = 0,
  SEND_GRAPHIC_MODE,
} ui_send_mode_e;

/**
 * @brief UI����״̬ö��
 * 
 */
typedef enum {
    MESSAGE_SENT = 0, // ��Ϣ�ѷ���
    MESSAGE_NOT_SENT, // ��Ϣ���º�δ����
} ui_sent_state_e;

typedef enum {
  LINE = 0,  // ֱ��
  RECTANGEL, // ����
  CIRCLE,    // Բ
  ELLIPSE,   // ��Բ
  ARC,       // Բ��
  FLOAT,     // ������
  INT,       // ����
  CHAR,      // �ַ�
} ui_type_e;

/**
 * @brief ��������״̬
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
 * @brief UI������Ϣ�ṹ��
 * 
 */
typedef struct __packed {
  /*******��������*********/
  ui_priority_e priority;       // UI���ȼ�(����̬UI��Ҫ����)
  ui_type_e ui_type;            // UI��������
  char *name;                   // ͼ������

  /*******�ɱ�����*********/

  /*******ͨ������********/
  operate_tpye_e operate_type; // ��������
  uint8_t layer;           // ͼ������0~9
  graphic_color_e color;   // ��ɫ
  uint16_t width;          // �������
  uint16_t start_x;        // ��� x ����
  uint16_t start_y;        // ��� y ����
  uint16_t end_x;          // �յ� x ����
  uint16_t end_y;          // �յ� y ����
  /*******��������********/
  uint16_t radius;      // Բ���뾶
  uint16_t start_angel; // Բ������ʼ�Ƕ�
  uint16_t end_angel;   // Բ������ֹ�Ƕ�
  uint16_t size;        // �������֣������С
  float float_num;      // ������: ��ʾ������
  uint16_t decimal;     // ��������С��λ��Ч����
  int32_t int_num;      // ����: ��ʾ������
  char text[30];        // �ַ�������ʾ������
} ui_config_t;

/**
 * @brief UI��Ϣ�ṹ��
 * 
 */
typedef struct __packed {
  ui_sent_state_e sent_state; // ��Ϣ����״̬��־λ
  uint32_t updateTick;             // ������Ϣʱ��ʱ���
  uint16_t  priority_value;        // UI�����ȼ�ֵ
  ui_config_t ui_config;           // �û�����UI��Ϣ
} ui_info_t;

/**
 * @brief UI����ڵ�ṹ��
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