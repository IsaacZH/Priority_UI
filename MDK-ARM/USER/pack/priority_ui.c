/**
 * @file priority_ui.c
 * @author Isaac (1812924685@qq.com)
 * @brief 通过优先队列实现UI优先级调度
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/* Includes ------------------------------------------------------------------*/
#include "priority_ui.h"

/*用户配置区******************************************************************************************/
#define HIGH_PRIORITY_WEIGHT 1000 // 高优先级权重
#define MID_PRIORITY_WEIGHT  500  // 中优先级权重
#define LOW_PRIORITY_WEIGHT  0    // 低优先级权重

#define HIGH_CHAR_PRIORITY_LEVEL 7  // 高优先级字符抢占图形UI的等级
#define MID_CHAR_PRIORITY_LEVEL  5  // 中优先级字符抢占图形UI的等级

#define SEND_INTERVAL        100 // 发送间隔时间(MS) [裁判系统上限是10HZ]
#define PER_INIT_UI_TIMES    1   // 每次初始化的UI次数

uint8_t send_test = 1;
/**
 * @brief 用户定义初始化UI的条件(所有发ADD)
 * 
 * @return true 开始初始化
 * @return false 正常发送
 */
bool Init_Ui_Condition()
{
  if (send_test == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}









/*目录******************************************************************************************/

// 排列相关函数
    /*计算消息的优先级*/uint32_t Calculate_Priority(ui_info_t *msg);                                     
    /*合并两个有序链表*/Node_u *SortedMerge(Node_u *a, Node_u *b);     
    /*将链表分成两半*/void FrontBackSplit(Node_u *source, Node_u **frontRef, Node_u **backRef);
    /*使用分治算法来对链表进行排序*/void mergeSort(Node_u **headRef);    
    /*将链表中优先级高的ui结构体存储到一个数组中*/ui_status_e Store_High_Priority_UI(Node_u* dynamic_list_head,Node_u* const_list_head,ui_info_t* graphic_priority_buffer, ui_info_t* character_priority_buffer, ui_send_mode_e *ui_send_mode); 

// 初始化链表函数
    /*初始化优先队列*/ui_status_e Init_Priority_LinkedList(Node_u** headRef, ui_info_t *ui_input, uint8_t num); 
    /*初始化两个链表*/ui_status_e Init_Type_LinkedLists(Node_u** graphic_link, Node_u** char_link, ui_info_t *dynamic_ui_info, ui_info_t *const_ui_info, uint8_t dynamic_num, uint8_t const_num); 

// 配置发送结构体函数
    /*配置字符信息进发送结构体*/ext_client_custom_character_t Process_Char_Info_To_Buffer(ui_info_t ui_info, uint8_t add_operate_enable); 
    /*配置图形信息进发送结构体*/ext_client_custom_graphic_seven_t Process_Graphic_To_Buffer(ui_info_t *ui_info, uint8_t ui_info_size, uint8_t add_operate_enable);

// UI发送函数
    /*UI正常发送*/ui_status_e Ui_Send_Normal();
    /*UI强行发送ADD*/ui_status_e Ui_Send_Add();

// 用户函数
    /*初始化UI链表*/void Init_Ui_List(ui_info_t *dynamic_ui_info, uint8_t dynamic_ui_num, ui_info_t *const_ui_info, uint8_t const_ui_num);
    /*UI发送函数*/void Ui_Send();
    /*添加对应UI到待发送*/ ui_status_e Enqueue_Ui_For_Sending(ui_info_t *ui_info);

  





/*底层函数*************************************************************************************************************/

/**
 * @brief 计算消息的优先级
 * 
 * @param msg 
 * @note 未更新低优先级阻塞1000ms等于未被阻塞高优先级
 * @return priority_value 
 */
uint32_t Calculate_Priority(ui_info_t *msg) 
{
  uint32_t priority_value = 0;
  uint32_t currentTick = HAL_GetTick();
  uint32_t age = currentTick - msg->updateTick;//消息的年龄

  // 根据消息的优先级计算优先级值
  if(msg->ui_config.priority == HIGH_PRIORITY)
  {
    priority_value = HIGH_PRIORITY_WEIGHT;
  }
  else if(msg->ui_config.priority == MID_PRIORITY)
  {
    priority_value = MID_PRIORITY_WEIGHT;
  }
  else
  {
    priority_value = LOW_PRIORITY_WEIGHT;
  }

  // 未发送的消息加上等待时间加权
  if(msg->sent_state == MESSAGE_NOT_SENT)
  {
    priority_value += age ;
  }

  return priority_value;
}
/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return Node* 
 */
Node_u* SortedMerge(Node_u* a, Node_u* b)
{
  Node_u* res = NULL;

  if (a == NULL)
    return (b);
  else if (b == NULL)
    return (a);

  a->ui->priority_value = Calculate_Priority(a->ui);
  b->ui->priority_value = Calculate_Priority(b->ui);

//优先判断消息是否发送(未发送的消息优先级最高)
  if (a->ui->sent_state == MESSAGE_NOT_SENT && b->ui->sent_state == MESSAGE_SENT)
  {
    res = a;
    res->next = SortedMerge(a->next, b);
  }
  else if (a->ui->sent_state == MESSAGE_SENT && b->ui->sent_state == MESSAGE_NOT_SENT)
  {
    res = b;
    res->next = SortedMerge(a, b->next);
  }
//发送状态相同，判断优先级
  else if (a->ui->priority_value >= b->ui->priority_value) 
  {
    res = a;
    res->next = SortedMerge(a->next, b);
  }
  else 
  {
    res = b;
    res->next = SortedMerge(a, b->next);
  }

  return res;
}

/**
 * @brief 用于将一个链表分成两半,在mergeSort中调用
 * 
 * @param source 表头地址
 * @param frontRef 用于储存前半段的开始地址
 * @param backRef 用于储存后半段的开始地址
 */
void FrontBackSplit(Node_u* source, Node_u** frontRef, Node_u** backRef)
{
   Node_u* fast;
   Node_u* slow;
   slow = source;
   fast = source->next;
 
   // 使用快慢指针法来找到链表的中点
   // 快指针每次移动两个节点，慢指针每次移动一个节点
   // 当快指针到达链表的末尾时，慢指针就在链表的中点
   while (fast != NULL) {
      fast = fast->next;
      if (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
      }
   }
 
   // 将链表分成两半
   // 前半部分的头节点是source，后半部分的头节点是slow->next
   *frontRef = source;
   *backRef = slow->next;
   slow->next = NULL;
}

/**
 * @brief 使用分治算法来对链表进行排序
 * 
 * @param headRef 
 */
void mergeSort(Node_u** headRef)
{
   Node_u* head = *headRef;
   Node_u* a;
   Node_u* b;
 
   // 如果链表为空，或者链表只有一个节点，那么链表已经是排序的，直接返回
   if ((head == NULL) || (head->next == NULL)) {
      return;
   }
 
   // 使用FrontBackSplit函数将链表分成两半
   FrontBackSplit(head, &a, &b);
 
   // 对每一半递归地进行归并排序
   mergeSort(&a);
   mergeSort(&b);
 
   // 使用SortedMerge函数将两个已排序的部分合并成一个完整的排序链表
   *headRef = SortedMerge(a, b);
}

/**
 * @brief 
 * 
 * @param headRef 链表头指针的地址
 * @param ui_input 要存进去的UI信息
 * @param num ui_info数组成员个数
 */
ui_status_e Init_Priority_LinkedList(Node_u** headRef, ui_info_t *ui_input, uint8_t num)
{
  // 如果headRef为空，直接返回
  if (headRef == NULL)
  {
    return UI_ERROR; // 没有声明链表头指针
  }
  
  Node_u* newNode = NULL;
  Node_u* cursor = *headRef;
  ui_info_t *ui_ptr = ui_input;
  // 创建一个零结构体
  ui_info_t zero_struct;
  memset(&zero_struct, 0, sizeof(ui_info_t));
  // 遍历ui_input数组的其余元素，并将每个元素添加到链表中
  for (uint8_t i = 0; i < num; i++) 
  {
    if (memcmp(ui_ptr, &zero_struct, sizeof(ui_info_t)) != 0)//防止某些傻逼注释掉了，结构体不全都是有东西
    {
      // 创建一个新的节点
      newNode = (Node_u*)malloc(sizeof(Node_u));
      if (newNode == NULL)
      {
        return UI_ERROR; // heap太小，申请不了内存
      }
      newNode->ui = ui_ptr;
      newNode->next = NULL;

      if (*headRef == NULL)//如果链表为空，将新节点设置为链表的头节点
      {
        *headRef = newNode;
      }
      else
      {
        // 将新节点添加到链表的末尾
        cursor->next = newNode;
      }
      cursor = newNode;
    }
    // 增加指针以访问下一个元素
    ui_ptr++;
  }
  return UI_OK;
}

/**
 * @brief 初始化两个链表，将dynamic_ui_info和const_ui_info两个数组中不是CHAR类型的UI存进其中一个链表，其他类型的UI存进另一个链表
 * 
 * @param graphic_link 存放图像链表头指针的地址
 * @param char_link 存放字符链表头指针的地址
 * @param dynamic_ui_info 动态UI信息数组
 * @param const_ui_info 静态UI信息数组
 * @param dynamic_num 动态UI信息数组成员个数
 * @param const_num 静态UI信息数组成员个数
 */
ui_status_e Init_Type_LinkedLists(Node_u** graphic_link, Node_u** char_link, ui_info_t *dynamic_ui_info, ui_info_t *const_ui_info, uint8_t dynamic_num, uint8_t const_num)
{
  if (graphic_link == NULL || char_link == NULL)
  {
    return UI_ERROR; // 没有声明链表头指针
  }

  Node_u* graphic_link_cursor = NULL;
  Node_u* char_link_cursor = NULL;
  
  // 创建一个零结构体
  ui_info_t zero_struct;
  memset(&zero_struct, 0, sizeof(ui_info_t));

  // 遍历dynamic_ui_info数组，将不是CHAR类型的UI添加到第一个链表中，其他类型的UI添加到第二个链表中
  ui_info_t *dynamic_ptr = dynamic_ui_info;
  for (uint8_t i = 0; i < dynamic_num; i++) 
  {
    if (memcmp(dynamic_ptr, &zero_struct, sizeof(ui_info_t)) == 0)
    {
      dynamic_ptr++;
      continue;
    }
    //分配内存存入当前的UI信息
    Node_u* newNode = (Node_u*)malloc(sizeof(Node_u));
    if (newNode == NULL)
    {
      return UI_ERROR; // heap太小，申请不了内存
    }
    newNode->ui = dynamic_ptr;
    newNode->next = NULL;
    //判断当前UI是否为CHAR类型
    if (dynamic_ptr->ui_config.ui_type != CHAR && dynamic_ptr->ui_config.operate_type != DELETE ) 
    {
      if (*graphic_link == NULL)//如果链表为空，将新节点设置为链表的头节点
      {
        *graphic_link = newNode;
      } 
      else //如果链表不为空，将新节点添加到链表的末尾
      {
        graphic_link_cursor->next = newNode;
      }
      graphic_link_cursor = newNode;//光标指向新节点
    } 
    else if (dynamic_ptr->ui_config.operate_type != DELETE)//如果当前UI为CHAR类型
    {
      if (*char_link == NULL) //如果链表为空，将新节点设置为链表的头节点
      {
        *char_link = newNode; //将新节点设置为链表的头节点
      } 
      else //如果链表不为空，将新节点添加到链表的末尾
      {
        char_link_cursor->next = newNode;
      }
      char_link_cursor = newNode; //光标指向新节点
    }
    dynamic_ptr++;
  }

  // 遍历const_ui_info数组，将不是CHAR类型的UI添加到第一个链表中，其他类型的UI添加到第二个链表中
  ui_info_t *const_ptr = const_ui_info;
  for (uint8_t i = 0; i < const_num; i++) 
  {
    if (memcmp(const_ptr, &zero_struct, sizeof(ui_info_t)) == 0)
    {
      const_ptr++;
      continue;
    }
    //分配内存存入当前的UI信息
    Node_u* newNode = (Node_u*)malloc(sizeof(Node_u));
    if (newNode == NULL)
    {
      return UI_ERROR;// heap太小，申请不了内存
    }
    newNode->ui = const_ptr;
    newNode->next = NULL;
    //判断当前UI是否为CHAR类型
    if (const_ptr->ui_config.ui_type != CHAR && const_ptr->ui_config.operate_type != DELETE) 
    {
      if (*graphic_link == NULL)//如果链表为空，将新节点设置为链表的头节点
      {
        *graphic_link = newNode;
      } 
      else //如果链表不为空，将新节点添加到链表的末尾
      {
        graphic_link_cursor->next = newNode;
      }
      graphic_link_cursor = newNode;
    } 
    else if(const_ptr->ui_config.operate_type != DELETE)//如果当前UI为CHAR类型
    {
      if (*char_link == NULL) //如果链表为空，将新节点设置为链表的头节点
      {
        *char_link = newNode;
      } 
      else //如果链表不为空，将新节点添加到链表的末尾
      {
        char_link_cursor->next = newNode;
      }
      char_link_cursor = newNode;
    }
    const_ptr++;
  }
  return UI_OK;
}


/**
 * @brief 将链表中优先级高的ui结构体存储到一个数组中，
 *        在调用此函数前应该先调用mergeSort函数对链表进行排序
 *
 * @param dynamic_list_head 动态UI链表的头节点
 * @param const_list_head 不变UI链表的头节点
 * @param graphic_buffer 存储ui结构体的数组
 * @return ui_status_e UI_ERROR：链表为空,没有初始化链表
 */
ui_status_e Store_High_Priority_UI(Node_u* dynamic_list_head,Node_u* const_list_head,ui_info_t* graphic_priority_buffer, ui_info_t* character_priority_buffer, ui_send_mode_e *ui_send_mode)
{
  uint8_t graphic_cnt = 0;
  uint8_t buffer_size = 7;
  Node_u* dynamic_list_cursor = dynamic_list_head;
  static Node_u* const_list_cursor = NULL;
  if (const_list_cursor == NULL)
  {
    const_list_cursor = const_list_head;
  }
  

  if (dynamic_list_cursor == NULL && const_list_cursor == NULL)
  {
    return UI_ERROR; // 跑到这里证明没有初始化链表
  }

  //第一个节点为字符，发送字符 PRIORITY_LOW的字符会在第一的时候发送
  if (dynamic_list_cursor->ui->ui_config.ui_type == CHAR)
  {
    if (dynamic_list_cursor != NULL)
    {
      character_priority_buffer = dynamic_list_cursor->ui;
      dynamic_list_cursor->ui->sent_state = MESSAGE_SENT;
      *ui_send_mode = SEND_CHAR_MODE;
      return UI_OK;
    }
  }
  
  // 指向链表的头节点不为空 且 数组下标小于数组大小 且 当前节点的发送状态为未发送
  if (dynamic_list_cursor != NULL)
  {
    while (graphic_cnt < buffer_size && dynamic_list_cursor->ui->sent_state == MESSAGE_NOT_SENT) 
    {
      if (dynamic_list_cursor->ui->ui_config.ui_type != CHAR)
      {
        graphic_priority_buffer[graphic_cnt] = *(dynamic_list_cursor->ui);//将当前节点的ui信息存储到数组中
        dynamic_list_cursor->ui->sent_state = MESSAGE_SENT;
        graphic_cnt++;//数组下标自增
      }
      else if (dynamic_list_cursor->ui->ui_config.priority == HIGH_PRIORITY)//如果当前节点为字符且优先级为高
      {
        if (graphic_cnt <= HIGH_CHAR_PRIORITY_LEVEL)
        {
          //将之前存入的图形信息的发送状态变回未发送
          dynamic_list_cursor = dynamic_list_head;
          for (uint8_t i = 0; i < graphic_cnt && dynamic_list_cursor->next != NULL; i++)
          {
            dynamic_list_cursor->ui->sent_state = MESSAGE_NOT_SENT;
            dynamic_list_cursor = dynamic_list_cursor->next;
          }
          //把要发送的字符信息存入buffer
          character_priority_buffer = dynamic_list_cursor->ui;
          dynamic_list_cursor->ui->sent_state = MESSAGE_SENT;
          *ui_send_mode = SEND_CHAR_MODE;
          return UI_OK;//发送字符
        }
      }
      else if (dynamic_list_cursor->ui->ui_config.priority == MID_PRIORITY)//如果当前节点为字符且优先级为中
      {
        if (graphic_cnt <= MID_CHAR_PRIORITY_LEVEL)//存入图形buffer的个数小于5就发送字符
        {
          //将之前存入的图形信息的发送状态变回未发送
          dynamic_list_cursor = dynamic_list_head;
          for (uint8_t i = 0; i < graphic_cnt && dynamic_list_cursor->next != NULL; i++)
          {
            dynamic_list_cursor->ui->sent_state = MESSAGE_NOT_SENT;
            dynamic_list_cursor = dynamic_list_cursor->next;
          }
          //把要发送的字符信息存入buffer
          character_priority_buffer = dynamic_list_cursor->ui;
          dynamic_list_cursor->ui->sent_state = MESSAGE_SENT;
          *ui_send_mode = SEND_CHAR_MODE;
          return UI_OK;//发送字符
        }
      }

      //如果下一个节点为空，退出循环
      if(dynamic_list_cursor->next == NULL)
      {
        break;
      }
      dynamic_list_cursor = dynamic_list_cursor->next;//指向下一个节点
    }
  }
// 剩下部分填入不变UI
  if (const_list_cursor != NULL)
  {
    while (graphic_cnt < buffer_size)
    {
      if (const_list_cursor->ui->ui_config.ui_type != CHAR)
      {
        graphic_priority_buffer[graphic_cnt] = *(const_list_cursor->ui);//将当前节点的ui信息存储到数组中
        graphic_priority_buffer[graphic_cnt].ui_config.operate_type = ADD;
        graphic_cnt++;//数组下标自增
      }
      //如果下一个节点为空，退出循环
      if(const_list_cursor->next == NULL)
      {
        const_list_cursor = const_list_head;
        break;
      }
      const_list_cursor = const_list_cursor->next;//指向下一个节点
    }
  }
  *ui_send_mode = SEND_GRAPHIC_MODE;
  return UI_OK;//发送图形
}


/**
 * @brief 配置字符信息进发送结构体
 * 
 * @param ui_info UI信息结构体
 * @param add_operate_enable 1：强行ADD 0：按照UI配置的operate_type
 * @return ext_client_custom_character_t 配置好的发送结构体
 */
ext_client_custom_character_t Process_Char_Info_To_Buffer(ui_info_t ui_info, uint8_t add_operate_enable)
{
  operate_tpye_e operate_tpye;
  if (add_operate_enable == 0)
  {
    operate_tpye = ui_info.ui_config.operate_type;
  }
  else
  {
    operate_tpye = ADD;
  }
  //获取UI配置信息
  char *name = ui_info.ui_config.name;
  uint8_t layer = ui_info.ui_config.layer;
  uint8_t color = ui_info.ui_config.color;
  uint16_t size = ui_info.ui_config.size;
  uint16_t length = strlen(ui_info.ui_config.text);
  uint16_t width = ui_info.ui_config.width;
  uint16_t start_x = ui_info.ui_config.start_x;
  uint16_t start_y = ui_info.ui_config.start_y;
  //配置信息进结构体
  graphic_data_struct_t char_buff;
	char_buff = draw_char(name,  //图形名
	                      operate_tpye,  //图形操作
                        layer,  //图层数，0~9
                        color,  //颜色
                        size,  //字体大小
                        length,  //字符长度
                        width,  //线条宽度
                        start_x,  //起点 x 坐标
                        start_y);  //起点 y 坐标

  //配置发送结构体
  ext_client_custom_character_t res;
  res.grapic_data_struct = char_buff;
  memcpy(&res.data,&ui_info.ui_config.text,sizeof(ui_info.ui_config.text));

  return res;
}

/**
 * @brief 配置图形信息进发送结构体
 * 
 * @param ui_info UI信息结构体
 * @param add_operate_enable 1：强行ADD 0：按照UI配置的operate_type
 * @return ext_client_custom_graphic_seven_t 配置好的发送结构体
 */
ext_client_custom_graphic_seven_t Process_Graphic_To_Buffer(ui_info_t *ui_info, uint8_t ui_info_size, uint8_t add_operate_enable)
{
  ext_client_custom_graphic_seven_t res;
  ui_info_t *ui_ptr = ui_info;
  for(uint8_t i = 0; i < 7; i++)
  {
    //判断是否会越界
    if (i >= ui_info_size)
    {
      return res;
    }
    //配置操作类型
    operate_tpye_e operate_tpye;
    if (add_operate_enable == 0)
    {
      operate_tpye = ui_ptr->ui_config.operate_type;
    }
    else
    {
      operate_tpye = ADD;
    }
    //获取UI配置信息
    char *name = ui_ptr->ui_config.name;
    uint8_t layer = ui_ptr->ui_config.layer;
    uint8_t color = ui_ptr->ui_config.color;
    uint16_t width = ui_ptr->ui_config.width;
    uint16_t start_x = ui_ptr->ui_config.start_x;
    uint16_t start_y = ui_ptr->ui_config.start_y;
    uint16_t end_x = ui_ptr->ui_config.end_x;        
    uint16_t end_y = ui_ptr->ui_config.end_y;       
    uint16_t radius = ui_ptr->ui_config.radius;      
    uint16_t start_angel = ui_ptr->ui_config.start_angel; 
    uint16_t end_angel = ui_ptr->ui_config.end_angel;   
    uint16_t size = ui_ptr->ui_config.size;
    float float_num = ui_ptr->ui_config.float_num; 
    uint16_t decimal = ui_ptr->ui_config.decimal;
    int32_t int_num = ui_ptr->ui_config.int_num;      
    //判断UI类型配置信息
    switch (ui_ptr->ui_config.ui_type)
    {
    case LINE:
      res.grapic_data_struct[i] = draw_line(name,  //图形名
                                            operate_tpye,  //图形操作
                                            layer,  //图层数，0~9
                                            color,  //颜色
                                            width,  //线条宽度
                                            start_x,  //起点 x 坐标
                                            start_y,  //起点 y 坐标
                                            end_x,  //终点 x 坐标
                                            end_y);  //终点 y 坐标
      break;
    case CIRCLE:
      res.grapic_data_struct[i] = draw_circle(name,  //图形名
                                              operate_tpye,  //图形操作
                                              layer,  //图层数，0~9
                                              color,  //颜色
                                              width,  //线条宽度
                                              start_x,  //圆心 x 坐标
                                              start_y,  //圆心 y 坐标
                                              radius);  //半径
      break;
    case RECTANGEL:
      res.grapic_data_struct[i] = draw_rectangle(name,  //图形名
                                                 operate_tpye,  //图形操作
                                                 layer,  //图层数，0~9
                                                 color,  //颜色
                                                 width,  //线条宽度
                                                 start_x,  //左上角 x 坐标
                                                 start_y,  //左上角 y 坐标
                                                 end_x,  //右下角 x 坐标
                                                 end_y);  //右下角 y 坐标
      break;
    case ELLIPSE:
      res.grapic_data_struct[i] = draw_ellipse(name,  //图形名
                                               operate_tpye,  //图形操作
                                               layer,  //图层数，0~9
                                               color,  //颜色
                                               width,  //线条宽度
                                               start_x,  //圆心 x 坐标
                                               start_y,  //圆心 y 坐标
                                               end_x,  //x 半轴长度
                                               end_y);  //y 半轴长度
      break;
    case ARC:
      res.grapic_data_struct[i] = draw_arc(name,  //图形名
                                           operate_tpye,  //图形操作
                                           layer,  //图层数，0~9
                                           color,  //颜色
                                           start_angel,  //起始角度
                                           end_angel,  //终止角度
                                           width,  //线条宽度
                                           start_x,  //圆心 x 坐标
                                           start_y,  //圆心 y 坐标
                                           end_x,  //x 半轴长度
                                           end_y);  //y 半轴长度
      break;
    case FLOAT:
      res.grapic_data_struct[i] = draw_float(name,  //图形名
                                             operate_tpye,  //图形操作
                                             layer,  //图层数，0~9
                                             color,  //颜色
                                             size,  //字体大小
                                             decimal,  //浮点数
                                             width,  //线条宽度
                                             start_x,  //起点 x 坐标
                                             start_y, //起点 y 坐标
                                             (int32_t) (float_num *1000));//乘以 1000 后，以 32 位整型数，int32_t  
      break;
    case INT:
      res.grapic_data_struct[i] = draw_int(name,  //图形名
                                           operate_tpye,  //图形操作
                                           layer,  //图层数，0~9
                                           color,  //颜色
                                           size,  //字体大小
                                           width,  //线条宽度
                                           start_x,  //起点 x 坐标
                                           start_y,  //起点 y 坐标
                                           int_num);  //整数
      break;
    default:
      break;
    }
    ui_ptr ++;
  }
  return res;
}















/*UI功能函数**************************************************************************************************************/
Node_u *dynamic_list_head = NULL; // 动态UI链表头
Node_u *const_list_head   = NULL; // 不变UI链表头
Node_u *graphic_list_head = NULL; // 图形UI链表头
Node_u *char_list_head    = NULL; // 字符UI链表头

ui_info_t graphic_priority_buffer[7]; // 优先级最高的7个图形
ui_info_t character_priority_buffer;  // 优先级最高的字符

ui_send_mode_e ui_send_mode; // 发送模式

/**
 * @brief 初始化UI链表 在外部调用 一定要在Ui_Send之前调用
 * 
 * @param dynamic_ui_info 
 * @param dynamic_ui_num 
 * @param const_ui_info 
 * @param const_ui_num 
 */
void Init_Ui_List(ui_info_t *dynamic_ui_info, uint8_t dynamic_ui_num, ui_info_t *const_ui_info, uint8_t const_ui_num)
{
  // 初始化动态UI链表
  Init_Priority_LinkedList(&dynamic_list_head, dynamic_ui_info, dynamic_ui_num);
  // 初始化不变UI链表
  Init_Priority_LinkedList(&const_list_head, const_ui_info, const_ui_num);
  // 初始化两个链表，将dynamic_ui_info和const_ui_info两个数组中不是CHAR类型的UI存进其中一个链表，其他类型的UI存进另一个链表
  Init_Type_LinkedLists(&graphic_list_head, &char_list_head, dynamic_ui_info, const_ui_info, dynamic_ui_num, const_ui_num);
}

/**
 * @brief 正常发送UI
 * 
 */
ui_status_e Ui_Send_Normal()
{
  ext_client_custom_graphic_seven_t graphic_tx_buffer;   // 图像发送缓存
  ext_client_custom_character_t     character_tx_buffer; // 字符发送缓存
  //对动态UI链表进行排序
  mergeSort(&dynamic_list_head);
  //将优先级最高的UI信息存储到数组中
  
  if (Store_High_Priority_UI(dynamic_list_head, const_list_head, graphic_priority_buffer, &character_priority_buffer, &ui_send_mode) == UI_ERROR)
  {
    return UI_ERROR; // 没有初始化链表
  }
  //根据发送模式进行发送
  switch (ui_send_mode)
  {
  case SEND_CHAR_MODE:
    character_tx_buffer = Process_Char_Info_To_Buffer(character_priority_buffer, 0);
    client_send_char(character_tx_buffer);
    break;
  case SEND_GRAPHIC_MODE:
    graphic_tx_buffer = Process_Graphic_To_Buffer(graphic_priority_buffer, 7, 0);
    client_send_seven_graphic(graphic_tx_buffer);
    break;
  default:
    break;
  }  
  return UI_OK;
}

/**
 * @brief UI强行发送ADD
 * @note  由于选手端登陆后，每个UI都需要发一次ADD，所以需要强制发送一次ADD
 *        
 * @return ui_status_e 0：error 1:发送完了 2:没发送完
 */
ui_status_e Ui_Send_Add()
{
  static uint8_t is_send_char_finish_flag = false;
  static uint8_t is_send_graphic_finish_flag = false;

  static Node_u* graphic_list_cursor = NULL;
  static Node_u* char_list_cursor = NULL;

/*判断graphic_list和char_list_head有某东西*******************************/
  if (graphic_list_head == NULL)
  {
    is_send_graphic_finish_flag = true;//某嘢就当发完了啰
  }
  if (char_list_head == NULL)
  {
    is_send_char_finish_flag = true;//某嘢就当发完了啰
  }
/*判断是第一次进来，初始化光标******************************************/
  if (graphic_list_cursor == NULL && graphic_list_head != NULL)
  {
    graphic_list_cursor = graphic_list_head;
  }
  if (char_list_cursor == NULL && char_list_head != NULL)
  {
    char_list_cursor = char_list_head;
  }
/*初始化发送缓存******************************************/
  ext_client_custom_graphic_seven_t graphic_tx_buffer;   // 图像发送缓存
  ext_client_custom_character_t     character_tx_buffer; // 字符发送缓存
  ui_info_t graphic_info_buffer[7];                      // 7个待发送图形信息
/*优先发送字符******************************************/
  if (char_list_cursor != NULL && is_send_char_finish_flag == false)
  {
    if (char_list_cursor->next == NULL)//如果到了链表尾部，就发送最后一次
    {
      character_tx_buffer = Process_Char_Info_To_Buffer(*char_list_cursor->ui, 1);
      client_send_char(character_tx_buffer);
      is_send_char_finish_flag = true;
      return UI_BUSY;
    }
    character_tx_buffer = Process_Char_Info_To_Buffer(*char_list_cursor->ui, 1);
    client_send_char(character_tx_buffer);
		char_list_cursor = char_list_cursor->next;
    return UI_BUSY;

  }
/*发送图形******************************************/
  if (graphic_list_cursor != NULL && is_send_graphic_finish_flag == false)
  {
    //从链表中取出7个图形信息
    for (uint8_t i = 0; i < 7 ; i++)
    {
      if (graphic_list_cursor->next == NULL)//如果到了链表尾部，就发送完了
      {
        graphic_info_buffer[i] = *graphic_list_cursor->ui;
        is_send_graphic_finish_flag = true;
        break;
      }
      graphic_info_buffer[i] = *graphic_list_cursor->ui;
      graphic_list_cursor = graphic_list_cursor->next;
    }
    graphic_tx_buffer = Process_Graphic_To_Buffer(graphic_info_buffer, 7, 1);
    client_send_seven_graphic(graphic_tx_buffer);
    return UI_BUSY;
  }
	/*判断是否都发完了******************************************/
	if (is_send_char_finish_flag == true && is_send_graphic_finish_flag == true)//都发完了
  {
    //复位，等待下一次发送
    char_list_cursor = char_list_head;//回到头节点
    graphic_list_cursor = graphic_list_head;//回到头节点
    is_send_char_finish_flag = false;
    is_send_graphic_finish_flag = false;
    return UI_OK;//返回1，证明发送完了
  }
  
  return UI_ERROR;//唔应该跑到尼到
}

/**
 * @brief 发送UI 在外部调用
 * 
 */
void Ui_Send()
{
  /*判断是否到了发送时间****************************/
  uint32_t currentTick = HAL_GetTick();
  static uint32_t lastTick = 0;
  if (currentTick - lastTick < SEND_INTERVAL)
  {
    return;
  }
  /*收到初始化指令切换标志位**********************/
  static uint8_t is_initing_ui = 0;
  if (Init_Ui_Condition())
  {
    if (is_initing_ui == 0)
    {
      is_initing_ui = 1;
    }
  }
  /*判断是否正在初始化****************************/
  static uint8_t init_times = 0;
  if (is_initing_ui == 1)//正在初始化UI
  {
    if (Ui_Send_Add() == 1)
    {
      init_times++; // 初始化完一次，次数加一
    }
    if (init_times >= PER_INIT_UI_TIMES)//初始化完PER_INIT_UI_TIMES次
    {
      is_initing_ui = 0;//初始化完毕
      init_times = 0;
    }
  }
	else/*正常发送UI*/
	{		
    Ui_Send_Normal();
	}
	lastTick = HAL_GetTick();
}

/**
 * @brief 更新完UI信息后调用此函数将UI设为准备发送状态
 * 
 * @param ui_info 
 */
ui_status_e Enqueue_Ui_For_Sending(ui_info_t *ui_info)
{
  if (ui_info == NULL)
  {
    return UI_ERROR;
  }

  if (ui_info->sent_state == MESSAGE_SENT)//发过先更新时间，未先之前一直某发又更新就会一直发唔出去
  {
    ui_info->updateTick = HAL_GetTick();
  }
  
  ui_info->sent_state = MESSAGE_NOT_SENT;

  return UI_OK;
}
