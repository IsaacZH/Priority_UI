/**
  ******************************************************************************
  * @file           : my_judge.c\h
	* @author         : czf
	* @date           : 
  * @brief          : 根据《RoboMaster_裁判系统串口协议附录 V1.3》编写
	                    针对机器人间交互数据 
  ******************************************************************************
  */

/* 目录begin */

//**********获取图像数据帧
//********************获取直线数据帧
//********************获取矩形数据帧
//********************获取整圆数据帧
//********************获取椭圆数据帧
//********************获取圆弧数据帧
//********************获取浮点数数据帧
//********************获取整型数数据帧
//********************获取字符数据帧
//**********发送帧数据
//********************发送绘制一个图形帧数据
//********************发送绘制二个图形帧数据
//********************发送绘制五个图形帧数据
//********************发送绘制七个图形帧数据
//********************发送绘制字符帧数据
//**********串口发送数据

/* 目录end */

#include "ui_protocol.h"
#include "crc.h"
#include "string.h"
#include "stdbool.h"
#include "stdio.h"
#include "judge_protocol.h"

/* 配置区 begin */
#define UI_huart huart4  //串口接口

extern UART_HandleTypeDef UI_huart;

client_info_t client_info = 
{
	.robot_id = 1,
	.client_id = 0x0101,
};
uint8_t client_tx_buf[128];

void client_info_update(void)
{
	switch(judge.game_robot_status.robot_id)
	{
		case 1:
			client_info.robot_id = 1;
		  client_info.client_id = 0x0101;
			break;
		case 101:
			client_info.robot_id = 101;
		  client_info.client_id = 0x0165;
			break;
		default:
			break;
	}
}
/* 配置区 end */

/******************************获取图像数据帧begin******************************/

/**
  * @brief  获取直线数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_line(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               uint16_t end_x,  //终点 x 坐标
               uint16_t end_y)  //终点 y 坐标
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 0;
	data.layer = layer;
	data.color = color;
	data.start_angle = 0;
	data.end_angle = 0;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = 0;
	data.end_x = end_x;
	data.end_y = end_y;
	
	return data;
}

/**
  * @brief  获取矩形数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_rectangle(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色DSFZa
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               uint16_t end_x,  //对角顶点 x 坐标
               uint16_t end_y)  //对角顶点 y 坐标
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 1;
	data.layer = layer;
	data.color = color;
	data.start_angle = 0;
	data.end_angle = 0;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = 0;
	data.end_x = end_x;
	data.end_y = end_y;
	
	return data;
}

/**
  * @brief  获取整圆数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_circle(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t ciclemid_x,  //圆心 x 坐标
               uint16_t ciclemid_y,  //圆心 y 坐标
               uint16_t radius)  //半径
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 2;
	data.layer = layer;
	data.color = color;
	data.start_angle = 0;
	data.end_angle = 0;
	data.width = width;
	data.start_x = ciclemid_x;
	data.start_y = ciclemid_y;
	data.radius = radius;
	data.end_x = 0;
	data.end_y = 0;
	
	return data;
}

/**
  * @brief  获取椭圆数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_ellipse(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t start_x,  //圆心 x 坐标
               uint16_t start_y,  //圆心 y 坐标
               uint16_t end_x,  //x 半轴长度
               uint16_t end_y)  //y 半轴长度
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 3;
	data.layer = layer;
	data.color = color;
	data.start_angle = 0;
	data.end_angle = 0;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = 0;
	data.end_x = end_x;
	data.end_y = end_y;
	
	return data;
}

/**
  * @brief  获取圆弧数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_arc(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t start_angle,  //起始角度
               uint16_t end_angle,  //终止角度
               uint16_t width,  //线条宽度
               uint16_t circlemin_x,  //圆心 x 坐标
               uint16_t circlemin_y,  //圆心 y 坐标
               uint16_t end_x,  //x 半轴长度
               uint16_t end_y)  //y 半轴长度
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 4;
	data.layer = layer;
	data.color = color;
	data.start_angle = start_angle;
	data.end_angle = end_angle;
	data.width = width;
	data.start_x = circlemin_x;
	data.start_y = circlemin_y;
	data.radius = 0;
	data.end_x = end_x;
	data.end_y = end_y;
	
	return data;
}

/**
  * @brief  获取浮点数数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_float(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t decimal,  //小数位有效个数
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               int32_t num)  //乘以 1000 后，以 32 位整型数，int32_t
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 5;
	data.layer = layer;
	data.color = color;
	data.start_angle = size;
	data.end_angle = decimal;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = num;
	data.end_x = num >> 10;
	data.end_y = num >> 21;
	
	return data;
}

/**
  * @brief  获取整型数数据帧
  * @param  
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_int(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               int32_t num)  //32 位整型数，int32_t
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 6;
	data.layer = layer;
	data.color = color;
	data.start_angle = size;
	data.end_angle = 0;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = num;
	data.end_x = num >> 10;
	data.end_y = num >> 21;
	
	return data;
}

/**
  * @brief  获取字符数据帧
  * @param  operate_tpye 图形操作
	* @param  layer 图层数，0~9
	* @param  color 颜色
	* @param  size 字体大小
	* @param  length 字符长度
	* @param  width 线条宽度
	* @param  start_x 起点 x 坐标
	* @param  start_y 起点 y 坐标 
  * @retval 图形数据结构体
  */
graphic_data_struct_t draw_char(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t length,  //字符长度
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y)  //起点 y 坐标
{
	graphic_data_struct_t data;
	
	memcpy(data.graphic_name, name, 3);
	data.operate_tpye = operate_tpye;
	data.graphic_tpye = 7;
	data.layer = layer;
	data.color = color;
	data.start_angle = size;
	data.end_angle = length;
	data.width = width;
	data.start_x = start_x;
	data.start_y = start_y;
	data.radius = 0;
	data.end_x = 0;
	data.end_y = 0;
	
	return data;
}

/******************************获取图像数据帧end******************************/

/******************************发送帧数据begin******************************/

/**
	* @brief  发送绘制一个图形帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_single_graphic(ext_client_custom_graphic_single_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_one_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_one_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], &data.grapic_data_struct, 15);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_one_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_one_graphic + 2);
}

/**
	* @brief  发送绘制二个图形帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_double_graphic(ext_client_custom_graphic_double_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_two_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_two_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], data.grapic_data_struct, 15*2);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_two_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_two_graphic + 2);
}

/**
	* @brief  发送绘制五个图形帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_five_graphic(ext_client_custom_graphic_five_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_five_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_five_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], data.grapic_data_struct, 15*5);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_five_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_five_graphic + 2);
}

/**
	* @brief  发送绘制七个图形帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_seven_graphic(ext_client_custom_graphic_seven_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_seven_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_seven_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], data.grapic_data_struct, 15*7);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_seven_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_seven_graphic + 2);
}

/**
	* @brief  发送绘制字符帧数据
  * @param  
  * @retval 
  */
uint8_t client_send_char(ext_client_custom_character_t data)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_char_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_draw_char_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	memcpy(&client_tx_buf[13], &data.grapic_data_struct, 15);
	memcpy(&client_tx_buf[28], data.data, 30);
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_draw_char_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_draw_char_graphic + 2);
}

/**
	* @brief  删除一个图层
  * @param  uint8_t delete_layer 删除的图层数
  * @retval 
  */
uint8_t client_graphic_delete_update(uint8_t delete_layer)
{
	frame_t frame;
	ext_student_interactive_header_data_t data_header;
	
	/* 帧头 */
	frame.frame_header.SOF = 0xA5;
	frame.frame_header.data_length = LEN_ID_draw_char_graphic;
	frame.frame_header.seq = 0;
	memcpy(client_tx_buf, &frame.frame_header, 4);
	Append_CRC8_Check_Sum(client_tx_buf, 5);
	
	/* 命令码ID */
	frame.cmd_id = 0x301;
	memcpy(&client_tx_buf[5], (void*)&frame.cmd_id, 2);
	
	/* 数据段 */
	data_header.data_cmd_id = ID_delete_graphic;
	data_header.sender_ID = client_info.robot_id;
	data_header.receiver_ID = client_info.client_id;
	memcpy(&client_tx_buf[7], &data_header, 6);
	client_tx_buf[13] = 1;//删除单个图层
	client_tx_buf[14] = delete_layer;//删除图层
	
	/* 帧尾 */
	Append_CRC16_Check_Sum(client_tx_buf, 5 + 2 + LEN_ID_delete_graphic + 2);
	
	/* 发送 */
	return uart_send_data(client_tx_buf, 5 + 2 + LEN_ID_delete_graphic + 2);
}

/******************************发送帧数据end****************************************/

/******************************串口发送数据begin************************************/

/**
	* @brief  串口发送数据
  * @param  
  * @retval 
  */
uint8_t uart_send_data(uint8_t *txbuf, uint16_t length)
{
	return HAL_UART_Transmit_DMA(&UI_huart, txbuf, length);

}

/******************************串口发送数据end**************************************/