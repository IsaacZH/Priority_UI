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
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X - 352,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 0,              // ��� y ����
    .ui_config.end_x = CLIENT_MID_POSITION_X - 176,                // �յ� x ����
    .ui_config.end_y = CLIENT_MID_POSITION_Y + 305,                // �յ� y ����
  },
    [RP_2] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X - 176,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 305,              // ��� y ����
    .ui_config.end_x = CLIENT_MID_POSITION_X + 176,                // �յ� x ����
    .ui_config.end_y = CLIENT_MID_POSITION_Y + 305,                // �յ� y ����
  },
    [RP_3] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X + 352,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 0,              // ��� y ����
    .ui_config.end_x = CLIENT_MID_POSITION_X + 176,                // �յ� x ����
    .ui_config.end_y = CLIENT_MID_POSITION_Y + 305,                // �յ� y ����
  },
    [RP_4] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X + 352,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 0,              // ��� y ����
    .ui_config.end_x = CLIENT_MID_POSITION_X + 176,                // �յ� x ����
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 305,                // �յ� y ����
  },
    [RP_5] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X + 58,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y - 305,              // ��� y ����
    .ui_config.end_x = CLIENT_MID_POSITION_X + 176,                // �յ� x ����
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 305,                // �յ� y ����
  },
    [RP_6] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X + 58,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y - 305,              // ��� y ����
    .ui_config.end_x = CLIENT_MID_POSITION_X - 4,                // �յ� x ����
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 153,                // �յ� y ����
  },
    [RP_7] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X - 49,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 145,              // ��� y ����
    .ui_config.end_x = CLIENT_MID_POSITION_X - 249,                // �յ� x ����
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 179,                // �յ� y ����
  },
    [RP_8] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X - 352,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 0,              // ��� y ����
    .ui_config.end_x = CLIENT_MID_POSITION_X - 249,                // �յ� x ����
    .ui_config.end_y = CLIENT_MID_POSITION_Y - 179,                // �յ� y ����
  },
    [RP_9] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = ARC,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X,              // Բ�� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y,              // Բ�� y ����
    .ui_config.end_x = 154,                // x ���᳤��
    .ui_config.end_y = 154,                // y ���᳤��
    .ui_config.start_angel = 360 - 2,          // ��ʼ�Ƕ�
    .ui_config.end_angel = 180 + 19,            // ��ֹ�Ƕ�
  },
  [VISION_CYCLE_1] = {
    /*******��������*********/
    .ui_config.priority = HIGH_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = CIRCLE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 2,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X - 610,              // Բ�� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 131,              // Բ�� y ����
    .ui_config.radius = 13,               // �뾶
  },
  [VISION_CYCLE_2] = {
    /*******��������*********/
    .ui_config.priority = HIGH_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = CIRCLE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 2,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X - 610,              // Բ�� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 131,              // Բ�� y ����
    .ui_config.radius = 22,               // �뾶
  },
  [TOP_MODE_CYCLE_1] = {
    /*******��������*********/
    .ui_config.priority = HIGH_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = CIRCLE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 2,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X - 610,              // Բ�� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 75,              // Բ�� y ����
    .ui_config.radius = 13,               // �뾶
  },
  [TOP_MODE_CYCLE_2] = {
    /*******��������*********/
    .ui_config.priority = HIGH_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = CIRCLE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 2,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X - 610,              // Բ�� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 75,              // Բ�� y ����
    .ui_config.radius = 22,               // �뾶
  },
  [NUM] = {
    /*******��������*********/
    .ui_config.priority = HIGH_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = INT,            // UI��������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 0,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.size = 100,                // �����С
    .ui_config.width = 5,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X + 610,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 75,              // ��� y ����
    .ui_config.int_num = 0,              // ��ʾ������
  },
  
};

ui_info_t const_ui_info [3] = 
{
  [0] = {
    /*******��������*********/
    .ui_config.ui_type = CHAR,           // UI��������
    /*******�ɱ�����*********/
    .ui_config.layer = 2,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.size = 20,                // �����С
    .ui_config.width = 2,                // �������
    .ui_config.start_x = CLIENT_MID_POSITION_X + 200,              // ��� x ����
    .ui_config.start_y = CLIENT_MID_POSITION_Y + 84,              // ��� y ����
    .ui_config.text = "LOL",            // ��ʾ������
  },
  
  [1] = {
    /*******��������*********/
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.layer = 3,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 2,                // �������
    .ui_config.start_x = AIM_X,              // ��� x ����
    .ui_config.start_y = AIM_Y + 75,              // ��� y ����
    .ui_config.end_x = AIM_X,                // �յ� x ����
    .ui_config.end_y = 10,                // �յ� y ����
  },
  
  [2] = {
    /*******��������*********/
    .ui_config.ui_type = LINE,         // UI��������
    /*******�ɱ�����*********/
    .ui_config.layer = 3,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 2,                // �������
    .ui_config.start_x = AIM_X - 80,              // ��� x ����
    .ui_config.start_y = AIM_Y - 32,              // ��� y ����
    .ui_config.end_x = AIM_X + 80,                // �յ� x ����
    .ui_config.end_y = AIM_Y - 32,                // �յ� y ����
  },
};


/**
  @brief: ��ʼ��UI���� main.c�е���
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

















/*����**********************************************************************************/

//#include <rp_math.h>
#define abs(x) 					((x)>0? (x):(-(x)))
#define one(x)					((x)>0? (1):(-1))
#define sgn(x) (((x)>0)?1:((x)<0?-1:0))
#include "math.h"
// ��ת����
void rotate(uint16_t *x, uint16_t *y, float mid_x, float mid_y, float angle) {
    float s = sin(angle);
    float c = cos(angle);

    // ƽ�Ƶ�ԭ��
    float origin_x = *x - mid_x;
    float origin_y = *y - mid_y;

    // ��ת
    float new_x = origin_x * c - origin_y * s;
    float new_y = origin_x * s + origin_y * c;

    // ƽ�ƻ�ȥ������ԭʼ����
    *x = new_x + mid_x;
    *y = new_y + mid_y;
}

void rotate_arc(ui_config_t *config, float mid_x, float mid_y, float angle) {
  // ��תԲ������
  uint16_t temp_start_x = config->start_x;
  uint16_t temp_start_y = config->start_y;
  rotate(&temp_start_x, &temp_start_y, mid_x, mid_y, angle);
  config->start_x = temp_start_x;
  config->start_y = temp_start_y;

  // ��ת��ʼ�ǶȺ���ֹ�Ƕ�
  config->start_angel += angle * (180.0 / 3.14);  // ������ת��Ϊ��
  config->end_angel += angle * (180.0 / 3.14);    // ������ת��Ϊ��

  // ȷ���Ƕ���0��360��֮��
  if (config->start_angel < 0) config->start_angel += 360;
  if (config->start_angel >= 360) config->start_angel -= 360;
  if (config->end_angel < 0) config->end_angel += 360;
  if (config->end_angel >= 360) config->end_angel -= 360;
}

// ����UI��Ϣ
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

