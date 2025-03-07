#include "ui.h"
#include "priority_ui.h"

#define AIM_X  956
#define AIM_Y  395
void rotate(uint16_t *x, uint16_t *y, float mid_x, float mid_y, float angle);
void rotate_arc(ui_config_t *config, float mid_x, float mid_y, float angle);
void Spin_Rp_Ui(void);

ui_info_t dynamic_ui_info [DYNAMIC_UI_NUM] = 
{
    [RP_1] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X - 352,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 0,              // 起点 y 坐标
    .ui_config.end_x = CLIENT_MID_POSITION_X - 176,                // 终点 x 坐标
    .ui_config.end_y = CLIENT_MID_POSITION_Y + 305,                // 终点 y 坐标
  },
    [RP_2] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X - 176,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 305,              // 起点 y 坐标
    .ui_config.end_x = CLIENT_MID_POSITION_X + 176,                // 终点 x 坐标
    .ui_config.end_y = CLIENT_MID_POSITION_Y + 305,                // 终点 y 坐标
  },
    [RP_3] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X + 352,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 0,              // 起点 y 坐标
    .ui_config.end_x = CLIENT_MID_POSITION_X + 176,                // 终点 x 坐标
    .ui_config.end_y = CLIENT_MID_POSITION_Y + 305,                // 终点 y 坐标
  },
    [RP_4] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X + 352,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 0,              // 起点 y 坐标
    .ui_config.end_x = CLIENT_MID_POSITION_X + 176,                // 终点 x 坐标
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 305,                // 终点 y 坐标
  },
    [RP_5] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X + 58,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y - 305,              // 起点 y 坐标
    .ui_config.end_x = CLIENT_MID_POSITION_X + 176,                // 终点 x 坐标
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 305,                // 终点 y 坐标
  },
    [RP_6] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X + 58,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y - 305,              // 起点 y 坐标
    .ui_config.end_x = CLIENT_MID_POSITION_X - 4,                // 终点 x 坐标
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 153,                // 终点 y 坐标
  },
    [RP_7] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X - 49,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 145,              // 起点 y 坐标
    .ui_config.end_x = CLIENT_MID_POSITION_X - 249,                // 终点 x 坐标
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 179,                // 终点 y 坐标
  },
    [RP_8] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X - 352,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 0,              // 起点 y 坐标
    .ui_config.end_x = CLIENT_MID_POSITION_X - 249,                // 终点 x 坐标
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 179,                // 终点 y 坐标
  },
    [RP_9] = {
    /*******不变配置*********/
    .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = ARC,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 3,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X,              // 圆心 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y,              // 圆心 y 坐标
    .ui_config.end_x = 154,                // x 半轴长度
    .ui_config.end_y = 154,                // y 半轴长度
    .ui_config.start_angel = 360 - 2,          // 起始角度
    .ui_config.end_angel = 180 + 19,            // 终止角度
  },
  [VISION_CYCLE_1] = {
    /*******不变配置*********/
    .ui_config.priority = HIGH_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = CIRCLE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 2,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X - 610,              // 圆心 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 131,              // 圆心 y 坐标
    .ui_config.radius = 13,               // 半径
  },
  [VISION_CYCLE_2] = {
    /*******不变配置*********/
    .ui_config.priority = HIGH_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = CIRCLE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 2,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X - 610,              // 圆心 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 131,              // 圆心 y 坐标
    .ui_config.radius = 22,               // 半径
  },
  [TOP_MODE_CYCLE_1] = {
    /*******不变配置*********/
    .ui_config.priority = HIGH_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = CIRCLE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 2,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X - 610,              // 圆心 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 75,              // 圆心 y 坐标
    .ui_config.radius = 13,               // 半径
  },
  [TOP_MODE_CYCLE_2] = {
    /*******不变配置*********/
    .ui_config.priority = HIGH_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = CIRCLE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 1,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 2,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X - 610,              // 圆心 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 75,              // 圆心 y 坐标
    .ui_config.radius = 22,               // 半径
  },
  [NUM] = {
    /*******不变配置*********/
    .ui_config.priority = HIGH_PRIORITY, // UI优先级(仅动态UI需要配置)
    .ui_config.ui_type = INT,            // UI内容类型
    /*******可变配置*********/
    .ui_config.operate_type = MODIFY,    // 操作类型
    .ui_config.layer = 0,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.size = 100,                // 字体大小
    .ui_config.width = 5,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X + 610,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 75,              // 起点 y 坐标
    .ui_config.int_num = 0,              // 显示的数字
  },
  
};

ui_info_t const_ui_info [3] = 
{
  [0] = {
    /*******不变配置*********/
    .ui_config.ui_type = CHAR,           // UI内容类型
    /*******可变配置*********/
    .ui_config.layer = 2,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.size = 20,                // 字体大小
    .ui_config.width = 2,                // 线条宽度
    .ui_config.start_x = CLIENT_MID_POSITION_X + 200,              // 起点 x 坐标
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 84,              // 起点 y 坐标
    .ui_config.text = "LOL",            // 显示的文字
  },
  
  [1] = {
    /*******不变配置*********/
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.layer = 3,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 2,                // 线条宽度
    .ui_config.start_x = AIM_X,              // 起点 x 坐标
    .ui_config.start_y = AIM_Y + 75,              // 起点 y 坐标
    .ui_config.end_x = AIM_X,                // 终点 x 坐标
    .ui_config.end_y = 10,                // 终点 y 坐标
  },
  
  [2] = {
    /*******不变配置*********/
    .ui_config.ui_type = LINE,         // UI内容类型
    /*******可变配置*********/
    .ui_config.layer = 3,                // 图层数，0~9
    .ui_config.color = GREEN,            // 颜色
    .ui_config.width = 2,                // 线条宽度
    .ui_config.start_x = AIM_X - 80,              // 起点 x 坐标
    .ui_config.start_y = AIM_Y - 32,              // 起点 y 坐标
    .ui_config.end_x = AIM_X + 80,                // 终点 x 坐标
    .ui_config.end_y = AIM_Y - 32,                // 终点 y 坐标
  },
};


/**
  @brief: 初始化UI链表 main.c中调用
 */
void My_Ui_Init(void)
{
  Init_Ui_List(dynamic_ui_info, sizeof(dynamic_ui_info)/sizeof(ui_info_t),const_ui_info, sizeof(const_ui_info)/sizeof(ui_info_t));
}


extern uint8_t send_test;

uint8_t is_spin_flag = 0;
uint8_t is_vision_flag = 0;
uint8_t is_top_flag = 0;
uint16_t test_num = 0;
void Ui_Info_Update(void)
{
  if (send_test != 0)
  {
    return;
  }
  if (is_spin_flag == 1)
  {
    Spin_Rp_Ui();
  }
  static uint8_t last_is_vision_flag = 0;
  if (is_vision_flag != last_is_vision_flag)
  {
    if (is_vision_flag == 1)
    {
      dynamic_ui_info[VISION_CYCLE_1].ui_config.color = PINK;
      dynamic_ui_info[VISION_CYCLE_2].ui_config.color = PINK;
    }
    else
    {
      dynamic_ui_info[VISION_CYCLE_1].ui_config.color = BLACK;
      dynamic_ui_info[VISION_CYCLE_2].ui_config.color = BLACK;
    }
    Enqueue_Ui_For_Sending(&dynamic_ui_info[VISION_CYCLE_1]);
    Enqueue_Ui_For_Sending(&dynamic_ui_info[VISION_CYCLE_2]);
  }
  last_is_vision_flag = is_vision_flag;
  static uint8_t last_is_top_flag = 0;
  if (is_top_flag != last_is_top_flag)
  {
    if (is_top_flag == 1)
    {
      dynamic_ui_info[TOP_MODE_CYCLE_1].ui_config.color = PINK;
      dynamic_ui_info[TOP_MODE_CYCLE_2].ui_config.color = PINK;
    }
    else
    {
      dynamic_ui_info[TOP_MODE_CYCLE_1].ui_config.color = BLACK;
      dynamic_ui_info[TOP_MODE_CYCLE_2].ui_config.color = BLACK;
    }
    Enqueue_Ui_For_Sending(&dynamic_ui_info[TOP_MODE_CYCLE_1]);
    Enqueue_Ui_For_Sending(&dynamic_ui_info[TOP_MODE_CYCLE_2]);
  }
  last_is_top_flag = is_top_flag;
  static uint16_t last_test_num = 0;
  if (test_num != last_test_num)
  {
    dynamic_ui_info[NUM].ui_config.int_num = test_num;
    Enqueue_Ui_For_Sending(&dynamic_ui_info[NUM]);
  }
  last_test_num = test_num;
}

















/*整活**********************************************************************************/

//#include <rp_math.h>
#define abs(x) 					((x)>0? (x):(-(x)))
#define one(x)					((x)>0? (1):(-1))
#define sgn(x) (((x)>0)?1:((x)<0?-1:0))
#include "math.h"
// 旋转函数
void rotate(uint16_t *x, uint16_t *y, float mid_x, float mid_y, float angle) {
    float s = sin(angle);
    float c = cos(angle);

    // 平移到原点
    float origin_x = *x - mid_x;
    float origin_y = *y - mid_y;

    // 旋转
    float new_x = origin_x * c - origin_y * s;
    float new_y = origin_x * s + origin_y * c;

    // 平移回去并更新原始坐标
    *x = new_x + mid_x;
    *y = new_y + mid_y;
}

void rotate_arc(ui_config_t *config, float mid_x, float mid_y, float angle) {
  // 旋转圆心坐标
  uint16_t temp_start_x = config->start_x;
  uint16_t temp_start_y = config->start_y;
  rotate(&temp_start_x, &temp_start_y, mid_x, mid_y, angle);
  config->start_x = temp_start_x;
  config->start_y = temp_start_y;

  // 旋转起始角度和终止角度
  config->start_angel += angle * (180.0 / 3.14);  // 将弧度转换为度
  config->end_angel += angle * (180.0 / 3.14);    // 将弧度转换为度

  // 确保角度在0到360度之间
  if (config->start_angel < 0) config->start_angel += 360;
  if (config->start_angel >= 360) config->start_angel -= 360;
  if (config->end_angel < 0) config->end_angel += 360;
  if (config->end_angel >= 360) config->end_angel -= 360;
}

// 更新UI信息
void spin_angle(float angle) {
  for (int i = 0; i < 8; i++) {
    rotate(&dynamic_ui_info[i].ui_config.start_x, &dynamic_ui_info[i].ui_config.start_y, CLIENT_MID_POSITION_X, CLIENT_MID_POSITION_Y, angle);
    rotate(&dynamic_ui_info[i].ui_config.end_x, &dynamic_ui_info[i].ui_config.end_y, CLIENT_MID_POSITION_X, CLIENT_MID_POSITION_Y, angle);
    Enqueue_Ui_For_Sending(&dynamic_ui_info[i]);
  }
 rotate_arc(&dynamic_ui_info[RP_9].ui_config, CLIENT_MID_POSITION_X, CLIENT_MID_POSITION_Y, angle);
 Enqueue_Ui_For_Sending(&dynamic_ui_info[RP_9]);
}
uint16_t test_spin_fre = 10;
void Spin_Rp_Ui(void)
{
  static uint16_t test_cnt = 0;
  test_cnt++;
  if (test_cnt < test_spin_fre) {
    return;
  }
  else
  {
    test_cnt = 0;
  }
  spin_angle(4/3.14);
}

