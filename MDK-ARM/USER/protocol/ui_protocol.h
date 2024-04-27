/**
  ******************************************************************************
  * @file           : my_judge.c\h
	* @author         : czf
	* @date           : 
  * @brief          : ���ݡ�RoboMaster_����ϵͳ����Э�鸽¼ V1.3����д
	                    ��Ի����˼佻������
	* @history        : 
  ******************************************************************************
  */
// - �Ƕ�ֵ����Ϊ��0��ָ 12 ���ӷ���˳ʱ����ƣ�
// - ��Ļλ�ã���0,0��Ϊ��Ļ���½ǣ�1920��1080��Ϊ��Ļ���Ͻǣ�
// - ����������������Ϊ 32 λ�����ڸ�������ʵ����ʾ��ֵΪ�����ֵ/1000���������� 1234����ʾ��ֵ��Ϊ 1.234��

/* Ŀ¼begin */

//����ϵͳ֡�ṹ
//**********֡ͷ
//**********���ݶ�ͷ�ṹ
//ö��
//**********����ID
//**********���ݶγ���
//**********��������
//**********��ɫ
//���ݶνṹ��
//**********ͼ������
//**********�ͻ��˻���һ��ͼ�����ݶ�
//**********�ͻ��˻��ƶ���ͼ�����ݶ�
//**********�ͻ��˻������ͼ�����ݶ�
//**********�ͻ��˻����߸�ͼ�����ݶ�
//**********�ͻ��˻����ַ����ݶ�
//����
//**********�����˼佻������ר��֡�ṹ
//**********�ͻ�����Ϣ

/* Ŀ¼end */

#ifndef __UI_PROTOCOL_H
#define __UI_PROTOCOL_H

#include "main.h"
#include "stdbool.h"

//1920*1080
#define CLIENT_MID_POSITION_X 960
#define CLIENT_MID_POSITION_Y 540

/********************����ϵͳ֡�ṹbegin********************/

/* ֡ͷ */
typedef struct __packed
{
	uint8_t  SOF;  //����֡��ʼ�ֽڣ��̶�ֵΪ 0xA5
	uint16_t data_length;  //����֡�� data �ĳ���
	uint8_t  seq;  //�����
	uint8_t  CRC8;  //֡ͷ CRC8 У��
}frame_header_t;

/* ���ݶ�ͷ�ṹ */
typedef struct __packed
{
	uint16_t data_cmd_id;  //����ID
	uint16_t sender_ID;  //�����ߵ� ID
	uint16_t receiver_ID;  //�����ߵ� ID
}ext_student_interactive_header_data_t;

/********************����ϵͳ֡�ṹend********************/

/********************ö��begin********************/

/* ����ID */
typedef enum
{
	//0x200-0x02ff 	�����Զ������� ��ʽ  INTERACT_ID_XXXX
	ID_delete_graphic 			= 0x0100,  //�ͻ���ɾ��ͼ��
	ID_draw_one_graphic 		= 0x0101,  //�ͻ��˻���һ��ͼ��
	ID_draw_two_graphic 		= 0x0102,  //�ͻ��˻��ƶ���ͼ��
	ID_draw_five_graphic 	  = 0x0103,  //�ͻ��˻������ͼ��
	ID_draw_seven_graphic 	= 0x0104,  //�ͻ��˻����߸�ͼ��
	ID_draw_char_graphic 	  = 0x0110,  //�ͻ��˻����ַ�ͼ��
}data_cmd_id_e;

/* ���ݶγ��� */
enum
{
	LEN_ID_delete_graphic     = 8,  //6+2
	LEN_ID_draw_one_graphic   = 21, //6+15
	LEN_ID_draw_two_graphic   = 36, //6+15*2
	LEN_ID_draw_five_graphic  = 81, //6+15*5
	LEN_ID_draw_seven_graphic = 111,//6+15*7
	LEN_ID_draw_char_graphic  = 51, //6+15+30���ַ������ݣ�
};

/* �������� */
typedef enum
{
	NONE   = 0,/*�ղ���*/
	ADD    = 1,/*����ͼ��*/
	MODIFY = 2,/*�޸�ͼ��*/
	DELETE = 3,/*ɾif��ͼ��*/
}operate_tpye_e;

/* ��ɫ */
typedef enum
{
	RED_BLUE  = 0,  //������ɫ	
	YELLOW    = 1,
	GREEN     = 2,
	ORANGE    = 3,
	FUCHSIA   = 4,	//�Ϻ�ɫ
	PINK      = 5,
	CYAN_BLUE = 6,	//��ɫ
	BLACK     = 7,
	WHITE     = 8
}graphic_color_e;

/********************ö��end********************/

/********************���ݶνṹ��begin********************/

/* ͼ������ */
typedef struct __packed
{ 
	uint8_t graphic_name[3];
	uint32_t operate_tpye:3;
	uint32_t graphic_tpye:3;
	uint32_t layer:4;
	uint32_t color:4;
	uint32_t start_angle:9;
	uint32_t end_angle:9;
	uint32_t width:10;
	uint32_t start_x:11;
	uint32_t start_y:11;
	uint32_t radius:10;
	uint32_t end_x:11;
	uint32_t end_y:11;
}graphic_data_struct_t;

/* �ͻ��˻���һ��ͼ�����ݶ� */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct;
} ext_client_custom_graphic_single_t;

/* �ͻ��˻��ƶ���ͼ�����ݶ� */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct[2];
} ext_client_custom_graphic_double_t;

/* �ͻ��˻������ͼ�����ݶ� */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct[5];
} ext_client_custom_graphic_five_t;

/* �ͻ��˻����߸�ͼ�����ݶ� */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct[7];
}ext_client_custom_graphic_seven_t;

/* �ͻ��˻����ַ����ݶ� */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct;
	char data[30];
}ext_client_custom_character_t;

typedef struct __packed
{
  uint8_t operate_tpye;
  uint8_t layer;
}ext_client_custom_graphic_delete_t;

/********************���ݶνṹ��end********************/


/********************����begin********************/

/* �����˼佻������ר��֡�ṹ */
typedef struct __packed
{
	frame_header_t frame_header;  //֡ͷ
	uint16_t cmd_id;  //������ ID
	ext_student_interactive_header_data_t data_header;  //���ݶ�ͷ�ṹ
	uint16_t frame_tail;  //֡β
}frame_t;

/* �ͻ�����Ϣ */
typedef struct
{
	uint8_t robot_id;
	uint16_t client_id;
}client_info_t;

/********************����end********************/

void client_info_update(void);

//��ֱ��
graphic_data_struct_t draw_line(char *name,  //ͼ����
	             uint8_t operate_tpye,  //ͼ�β���
               uint8_t layer,  //ͼ������0~9
               uint8_t color,  //��ɫ
               uint16_t width,  //�������
               uint16_t start_x,  //��� x ����
               uint16_t start_y,  //��� y ����
               uint16_t end_x,  //�յ� x ����
               uint16_t end_y);  //�յ� y ����

//������
graphic_data_struct_t draw_rectangle(char *name,  //ͼ����
	             uint8_t operate_tpye,  //ͼ�β���
               uint8_t layer,  //ͼ������0~9
               uint8_t color,  //��ɫ
               uint16_t width,  //�������
               uint16_t start_x,  //��� x ����
               uint16_t start_y,  //��� y ����
               uint16_t end_x,  //�ԽǶ��� x ����
               uint16_t end_y);  //�ԽǶ��� y ����

//����Բ
graphic_data_struct_t draw_circle(char *name,  //ͼ����
	             uint8_t operate_tpye,  //ͼ�β���
               uint8_t layer,  //ͼ������0~9
               uint8_t color,  //��ɫ
               uint16_t width,  //�������
               uint16_t start_x,  //Բ�� x ����
               uint16_t start_y,  //Բ�� y ����
               uint16_t radius);  //�뾶

//����Բ
graphic_data_struct_t draw_ellipse(char *name,  //ͼ����
	             uint8_t operate_tpye,  //ͼ�β���
               uint8_t layer,  //ͼ������0~9
               uint8_t color,  //��ɫ
               uint16_t width,  //�������
               uint16_t start_x,  //Բ�� x ����
               uint16_t start_y,  //Բ�� y ����
               uint16_t end_x,  //x ���᳤��
               uint16_t end_y);  //y ���᳤��

//��Բ��
graphic_data_struct_t draw_arc(char *name,  //ͼ����
	             uint8_t operate_tpye,  //ͼ�β���
               uint8_t layer,  //ͼ������0~9
               uint8_t color,  //��ɫ
               uint16_t start_angle,  //��ʼ�Ƕ�
               uint16_t end_angle,  //��ֹ�Ƕ�
               uint16_t width,  //�������
               uint16_t start_x,  //Բ�� x ����
               uint16_t start_y,  //Բ�� y ����
               uint16_t end_x,  //x ���᳤��
               uint16_t end_y);  //y ���᳤��

//��������
graphic_data_struct_t draw_float(char *name,  //ͼ����
	             uint8_t operate_tpye,  //ͼ�β���
               uint8_t layer,  //ͼ������0~9
               uint8_t color,  //��ɫ
               uint16_t size,  //�����С
               uint16_t decimal,  //С��λ��Ч����
               uint16_t width,  //�������
               uint16_t start_x,  //��� x ����
               uint16_t start_y,  //��� y ����
               int32_t num);  //���� 1000 ���� 32 λ��������int32_t

//��������
graphic_data_struct_t draw_int(char *name,  //ͼ����
	             uint8_t operate_tpye,  //ͼ�β���
               uint8_t layer,  //ͼ������0~9
               uint8_t color,  //��ɫ
               uint16_t size,  //�����С
               uint16_t width,  //�������
               uint16_t start_x,  //��� x ����
               uint16_t start_y,  //��� y ����
               int32_t num);  //32 λ��������int32_t

//���ַ���
graphic_data_struct_t draw_char(char *name,  //ͼ����
	             uint8_t operate_tpye,  //ͼ�β���
               uint8_t layer,  //ͼ������0~9
               uint8_t color,  //��ɫ
               uint16_t size,  //�����С
               uint16_t length,  //�ַ�����
               uint16_t width,  //�������
               uint16_t start_x,  //��� x ����
               uint16_t start_y);  //��� y ����

uint8_t client_send_single_graphic(ext_client_custom_graphic_single_t data);
uint8_t client_send_double_graphic(ext_client_custom_graphic_double_t data);
uint8_t client_send_five_graphic(ext_client_custom_graphic_five_t data);
uint8_t client_send_seven_graphic(ext_client_custom_graphic_seven_t data);
uint8_t client_send_char(ext_client_custom_character_t data);
uint8_t client_graphic_delete_update(uint8_t delete_layer);

uint8_t uart_send_data(uint8_t *txbuf, uint16_t length);

//****************************************************************************************************end

#endif
