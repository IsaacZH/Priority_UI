/**
  ******************************************************************************
  * @file           : my_judge.c\h
	* @author         : czf
	* @date           : 
  * @brief          : 根据《RoboMaster_裁判系统串口协议附录 V1.3》编写
	                    针对机器人间交互数据
	* @history        : 
  ******************************************************************************
  */
// - 角度值含义为：0°指 12 点钟方向，顺时针绘制；
// - 屏幕位置：（0,0）为屏幕左下角（1920，1080）为屏幕右上角；
// - 浮点数：整型数均为 32 位，对于浮点数，实际显示的值为输入的值/1000，如在输入 1234，显示的值将为 1.234。

/* 目录begin */

//裁判系统帧结构
//**********帧头
//**********数据段头结构
//枚举
//**********内容ID
//**********数据段长度
//**********操作类型
//**********颜色
//数据段结构体
//**********图形数据
//**********客户端绘制一个图形数据段
//**********客户端绘制二个图形数据段
//**********客户端绘制五个图形数据段
//**********客户端绘制七个图形数据段
//**********客户端绘制字符数据段
//其他
//**********机器人间交互数据专用帧结构
//**********客户端信息

/* 目录end */

#ifndef __UI_PROTOCOL_H
#define __UI_PROTOCOL_H

#include "main.h"
#include "stdbool.h"

//1920*1080
#define CLIENT_MID_POSITION_X 960
#define CLIENT_MID_POSITION_Y 540

/********************裁判系统帧结构begin********************/

/* 帧头 */
typedef struct __packed
{
	uint8_t  SOF;  //数据帧起始字节，固定值为 0xA5
	uint16_t data_length;  //数据帧中 data 的长度
	uint8_t  seq;  //包序号
	uint8_t  CRC8;  //帧头 CRC8 校验
}frame_header_t;

/* 数据段头结构 */
typedef struct __packed
{
	uint16_t data_cmd_id;  //内容ID
	uint16_t sender_ID;  //发送者的 ID
	uint16_t receiver_ID;  //接收者的 ID
}ext_student_interactive_header_data_t;

/********************裁判系统帧结构end********************/

/********************枚举begin********************/

/* 内容ID */
typedef enum
{
	//0x200-0x02ff 	队伍自定义命令 格式  INTERACT_ID_XXXX
	ID_delete_graphic 			= 0x0100,  //客户端删除图形
	ID_draw_one_graphic 		= 0x0101,  //客户端绘制一个图形
	ID_draw_two_graphic 		= 0x0102,  //客户端绘制二个图形
	ID_draw_five_graphic 	  = 0x0103,  //客户端绘制五个图形
	ID_draw_seven_graphic 	= 0x0104,  //客户端绘制七个图形
	ID_draw_char_graphic 	  = 0x0110,  //客户端绘制字符图形
}data_cmd_id_e;

/* 数据段长度 */
enum
{
	LEN_ID_delete_graphic     = 8,  //6+2
	LEN_ID_draw_one_graphic   = 21, //6+15
	LEN_ID_draw_two_graphic   = 36, //6+15*2
	LEN_ID_draw_five_graphic  = 81, //6+15*5
	LEN_ID_draw_seven_graphic = 111,//6+15*7
	LEN_ID_draw_char_graphic  = 51, //6+15+30（字符串内容）
};

/* 操作类型 */
typedef enum
{
	NONE   = 0,/*空操作*/
	ADD    = 1,/*增加图层*/
	MODIFY = 2,/*修改图层*/
	DELETE = 3,/*删if除图层*/
}operate_tpye_e;

/* 颜色 */
typedef enum
{
	RED_BLUE  = 0,  //红蓝主色	
	YELLOW    = 1,
	GREEN     = 2,
	ORANGE    = 3,
	FUCHSIA   = 4,	//紫红色
	PINK      = 5,
	CYAN_BLUE = 6,	//青色
	BLACK     = 7,
	WHITE     = 8
}graphic_color_e;

/********************枚举end********************/

/********************数据段结构体begin********************/

/* 图形数据 */
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

/* 客户端绘制一个图形数据段 */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct;
} ext_client_custom_graphic_single_t;

/* 客户端绘制二个图形数据段 */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct[2];
} ext_client_custom_graphic_double_t;

/* 客户端绘制五个图形数据段 */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct[5];
} ext_client_custom_graphic_five_t;

/* 客户端绘制七个图形数据段 */
typedef struct __packed
{
	graphic_data_struct_t grapic_data_struct[7];
}ext_client_custom_graphic_seven_t;

/* 客户端绘制字符数据段 */
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

/********************数据段结构体end********************/


/********************其他begin********************/

/* 机器人间交互数据专用帧结构 */
typedef struct __packed
{
	frame_header_t frame_header;  //帧头
	uint16_t cmd_id;  //命令码 ID
	ext_student_interactive_header_data_t data_header;  //数据段头结构
	uint16_t frame_tail;  //帧尾
}frame_t;

/* 客户端信息 */
typedef struct
{
	uint8_t robot_id;
	uint16_t client_id;
}client_info_t;

/********************其他end********************/

void client_info_update(void);

//画直线
graphic_data_struct_t draw_line(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               uint16_t end_x,  //终点 x 坐标
               uint16_t end_y);  //终点 y 坐标

//画矩形
graphic_data_struct_t draw_rectangle(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               uint16_t end_x,  //对角顶点 x 坐标
               uint16_t end_y);  //对角顶点 y 坐标

//画整圆
graphic_data_struct_t draw_circle(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t start_x,  //圆心 x 坐标
               uint16_t start_y,  //圆心 y 坐标
               uint16_t radius);  //半径

//画椭圆
graphic_data_struct_t draw_ellipse(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t width,  //线条宽度
               uint16_t start_x,  //圆心 x 坐标
               uint16_t start_y,  //圆心 y 坐标
               uint16_t end_x,  //x 半轴长度
               uint16_t end_y);  //y 半轴长度

//画圆弧
graphic_data_struct_t draw_arc(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t start_angle,  //起始角度
               uint16_t end_angle,  //终止角度
               uint16_t width,  //线条宽度
               uint16_t start_x,  //圆心 x 坐标
               uint16_t start_y,  //圆心 y 坐标
               uint16_t end_x,  //x 半轴长度
               uint16_t end_y);  //y 半轴长度

//画浮点数
graphic_data_struct_t draw_float(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t decimal,  //小数位有效个数
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               int32_t num);  //乘以 1000 后，以 32 位整型数，int32_t

//画整型数
graphic_data_struct_t draw_int(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y,  //起点 y 坐标
               int32_t num);  //32 位整型数，int32_t

//画字符串
graphic_data_struct_t draw_char(char *name,  //图形名
	             uint8_t operate_tpye,  //图形操作
               uint8_t layer,  //图层数，0~9
               uint8_t color,  //颜色
               uint16_t size,  //字体大小
               uint16_t length,  //字符长度
               uint16_t width,  //线条宽度
               uint16_t start_x,  //起点 x 坐标
               uint16_t start_y);  //起点 y 坐标

uint8_t client_send_single_graphic(ext_client_custom_graphic_single_t data);
uint8_t client_send_double_graphic(ext_client_custom_graphic_double_t data);
uint8_t client_send_five_graphic(ext_client_custom_graphic_five_t data);
uint8_t client_send_seven_graphic(ext_client_custom_graphic_seven_t data);
uint8_t client_send_char(ext_client_custom_character_t data);
uint8_t client_graphic_delete_update(uint8_t delete_layer);

uint8_t uart_send_data(uint8_t *txbuf, uint16_t length);

//****************************************************************************************************end

#endif
