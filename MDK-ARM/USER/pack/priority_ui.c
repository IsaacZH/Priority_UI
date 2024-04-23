/**
 * @file priority_ui.c
 * @author Isaac (1812924685@qq.com)
 * @brief ͨ�����ȶ���ʵ��UI���ȼ�����
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/* Includes ------------------------------------------------------------------*/
#include "priority_ui.h"

/*�û�������******************************************************************************************/
#define HIGH_PRIORITY_WEIGHT 1000 // �����ȼ�Ȩ��
#define MID_PRIORITY_WEIGHT  500  // �����ȼ�Ȩ��
#define LOW_PRIORITY_WEIGHT  0    // �����ȼ�Ȩ��

#define HIGH_CHAR_PRIORITY_LEVEL 7  // �����ȼ��ַ���ռͼ��UI�ĵȼ�
#define MID_CHAR_PRIORITY_LEVEL  5  // �����ȼ��ַ���ռͼ��UI�ĵȼ�

#define SEND_INTERVAL        100 // ���ͼ��ʱ��(MS) [����ϵͳ������10HZ]
#define PER_INIT_UI_TIMES    1   // ÿ�γ�ʼ����UI����

uint8_t send_test = 1;
/**
 * @brief �û������ʼ��UI������(���з�ADD)
 * 
 * @return true ��ʼ��ʼ��
 * @return false ��������
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









/*Ŀ¼******************************************************************************************/

// ������غ���
    /*������Ϣ�����ȼ�*/uint32_t Calculate_Priority(ui_info_t *msg);                                     
    /*�ϲ�������������*/Node_u *SortedMerge(Node_u *a, Node_u *b);     
    /*������ֳ�����*/void FrontBackSplit(Node_u *source, Node_u **frontRef, Node_u **backRef);
    /*ʹ�÷����㷨���������������*/void mergeSort(Node_u **headRef);    
    /*�����������ȼ��ߵ�ui�ṹ��洢��һ��������*/ui_status_e Store_High_Priority_UI(Node_u* dynamic_list_head,Node_u* const_list_head,ui_info_t* graphic_priority_buffer, ui_info_t* character_priority_buffer, ui_send_mode_e *ui_send_mode); 

// ��ʼ��������
    /*��ʼ�����ȶ���*/ui_status_e Init_Priority_LinkedList(Node_u** headRef, ui_info_t *ui_input, uint8_t num); 
    /*��ʼ����������*/ui_status_e Init_Type_LinkedLists(Node_u** graphic_link, Node_u** char_link, ui_info_t *dynamic_ui_info, ui_info_t *const_ui_info, uint8_t dynamic_num, uint8_t const_num); 

// ���÷��ͽṹ�庯��
    /*�����ַ���Ϣ�����ͽṹ��*/ext_client_custom_character_t Process_Char_Info_To_Buffer(ui_info_t ui_info, uint8_t add_operate_enable); 
    /*����ͼ����Ϣ�����ͽṹ��*/ext_client_custom_graphic_seven_t Process_Graphic_To_Buffer(ui_info_t *ui_info, uint8_t ui_info_size, uint8_t add_operate_enable);

// UI���ͺ���
    /*UI��������*/ui_status_e Ui_Send_Normal();
    /*UIǿ�з���ADD*/ui_status_e Ui_Send_Add();

// �û�����
    /*��ʼ��UI����*/void Init_Ui_List(ui_info_t *dynamic_ui_info, uint8_t dynamic_ui_num, ui_info_t *const_ui_info, uint8_t const_ui_num);
    /*UI���ͺ���*/void Ui_Send();
    /*��Ӷ�ӦUI��������*/ ui_status_e Enqueue_Ui_For_Sending(ui_info_t *ui_info);

  





/*�ײ㺯��*************************************************************************************************************/

/**
 * @brief ������Ϣ�����ȼ�
 * 
 * @param msg 
 * @note δ���µ����ȼ�����1000ms����δ�����������ȼ�
 * @return priority_value 
 */
uint32_t Calculate_Priority(ui_info_t *msg) 
{
  uint32_t priority_value = 0;
  uint32_t currentTick = HAL_GetTick();
  uint32_t age = currentTick - msg->updateTick;//��Ϣ������

  // ������Ϣ�����ȼ��������ȼ�ֵ
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

  // δ���͵���Ϣ���ϵȴ�ʱ���Ȩ
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

//�����ж���Ϣ�Ƿ���(δ���͵���Ϣ���ȼ����)
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
//����״̬��ͬ���ж����ȼ�
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
 * @brief ���ڽ�һ������ֳ�����,��mergeSort�е���
 * 
 * @param source ��ͷ��ַ
 * @param frontRef ���ڴ���ǰ��εĿ�ʼ��ַ
 * @param backRef ���ڴ�����εĿ�ʼ��ַ
 */
void FrontBackSplit(Node_u* source, Node_u** frontRef, Node_u** backRef)
{
   Node_u* fast;
   Node_u* slow;
   slow = source;
   fast = source->next;
 
   // ʹ�ÿ���ָ�뷨���ҵ�������е�
   // ��ָ��ÿ���ƶ������ڵ㣬��ָ��ÿ���ƶ�һ���ڵ�
   // ����ָ�뵽�������ĩβʱ����ָ�����������е�
   while (fast != NULL) {
      fast = fast->next;
      if (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
      }
   }
 
   // ������ֳ�����
   // ǰ�벿�ֵ�ͷ�ڵ���source����벿�ֵ�ͷ�ڵ���slow->next
   *frontRef = source;
   *backRef = slow->next;
   slow->next = NULL;
}

/**
 * @brief ʹ�÷����㷨���������������
 * 
 * @param headRef 
 */
void mergeSort(Node_u** headRef)
{
   Node_u* head = *headRef;
   Node_u* a;
   Node_u* b;
 
   // �������Ϊ�գ���������ֻ��һ���ڵ㣬��ô�����Ѿ�������ģ�ֱ�ӷ���
   if ((head == NULL) || (head->next == NULL)) {
      return;
   }
 
   // ʹ��FrontBackSplit����������ֳ�����
   FrontBackSplit(head, &a, &b);
 
   // ��ÿһ��ݹ�ؽ��й鲢����
   mergeSort(&a);
   mergeSort(&b);
 
   // ʹ��SortedMerge����������������Ĳ��ֺϲ���һ����������������
   *headRef = SortedMerge(a, b);
}

/**
 * @brief 
 * 
 * @param headRef ����ͷָ��ĵ�ַ
 * @param ui_input Ҫ���ȥ��UI��Ϣ
 * @param num ui_info�����Ա����
 */
ui_status_e Init_Priority_LinkedList(Node_u** headRef, ui_info_t *ui_input, uint8_t num)
{
  // ���headRefΪ�գ�ֱ�ӷ���
  if (headRef == NULL)
  {
    return UI_ERROR; // û����������ͷָ��
  }
  
  Node_u* newNode = NULL;
  Node_u* cursor = *headRef;
  ui_info_t *ui_ptr = ui_input;
  // ����һ����ṹ��
  ui_info_t zero_struct;
  memset(&zero_struct, 0, sizeof(ui_info_t));
  // ����ui_input���������Ԫ�أ�����ÿ��Ԫ����ӵ�������
  for (uint8_t i = 0; i < num; i++) 
  {
    if (memcmp(ui_ptr, &zero_struct, sizeof(ui_info_t)) != 0)//��ֹĳЩɵ��ע�͵��ˣ��ṹ�岻ȫ�����ж���
    {
      // ����һ���µĽڵ�
      newNode = (Node_u*)malloc(sizeof(Node_u));
      if (newNode == NULL)
      {
        return UI_ERROR; // heap̫С�����벻���ڴ�
      }
      newNode->ui = ui_ptr;
      newNode->next = NULL;

      if (*headRef == NULL)//�������Ϊ�գ����½ڵ�����Ϊ�����ͷ�ڵ�
      {
        *headRef = newNode;
      }
      else
      {
        // ���½ڵ���ӵ������ĩβ
        cursor->next = newNode;
      }
      cursor = newNode;
    }
    // ����ָ���Է�����һ��Ԫ��
    ui_ptr++;
  }
  return UI_OK;
}

/**
 * @brief ��ʼ������������dynamic_ui_info��const_ui_info���������в���CHAR���͵�UI�������һ�������������͵�UI�����һ������
 * 
 * @param graphic_link ���ͼ������ͷָ��ĵ�ַ
 * @param char_link ����ַ�����ͷָ��ĵ�ַ
 * @param dynamic_ui_info ��̬UI��Ϣ����
 * @param const_ui_info ��̬UI��Ϣ����
 * @param dynamic_num ��̬UI��Ϣ�����Ա����
 * @param const_num ��̬UI��Ϣ�����Ա����
 */
ui_status_e Init_Type_LinkedLists(Node_u** graphic_link, Node_u** char_link, ui_info_t *dynamic_ui_info, ui_info_t *const_ui_info, uint8_t dynamic_num, uint8_t const_num)
{
  if (graphic_link == NULL || char_link == NULL)
  {
    return UI_ERROR; // û����������ͷָ��
  }

  Node_u* graphic_link_cursor = NULL;
  Node_u* char_link_cursor = NULL;
  
  // ����һ����ṹ��
  ui_info_t zero_struct;
  memset(&zero_struct, 0, sizeof(ui_info_t));

  // ����dynamic_ui_info���飬������CHAR���͵�UI��ӵ���һ�������У��������͵�UI��ӵ��ڶ���������
  ui_info_t *dynamic_ptr = dynamic_ui_info;
  for (uint8_t i = 0; i < dynamic_num; i++) 
  {
    if (memcmp(dynamic_ptr, &zero_struct, sizeof(ui_info_t)) == 0)
    {
      dynamic_ptr++;
      continue;
    }
    //�����ڴ���뵱ǰ��UI��Ϣ
    Node_u* newNode = (Node_u*)malloc(sizeof(Node_u));
    if (newNode == NULL)
    {
      return UI_ERROR; // heap̫С�����벻���ڴ�
    }
    newNode->ui = dynamic_ptr;
    newNode->next = NULL;
    //�жϵ�ǰUI�Ƿ�ΪCHAR����
    if (dynamic_ptr->ui_config.ui_type != CHAR && dynamic_ptr->ui_config.operate_type != DELETE ) 
    {
      if (*graphic_link == NULL)//�������Ϊ�գ����½ڵ�����Ϊ�����ͷ�ڵ�
      {
        *graphic_link = newNode;
      } 
      else //�������Ϊ�գ����½ڵ���ӵ������ĩβ
      {
        graphic_link_cursor->next = newNode;
      }
      graphic_link_cursor = newNode;//���ָ���½ڵ�
    } 
    else if (dynamic_ptr->ui_config.operate_type != DELETE)//�����ǰUIΪCHAR����
    {
      if (*char_link == NULL) //�������Ϊ�գ����½ڵ�����Ϊ�����ͷ�ڵ�
      {
        *char_link = newNode; //���½ڵ�����Ϊ�����ͷ�ڵ�
      } 
      else //�������Ϊ�գ����½ڵ���ӵ������ĩβ
      {
        char_link_cursor->next = newNode;
      }
      char_link_cursor = newNode; //���ָ���½ڵ�
    }
    dynamic_ptr++;
  }

  // ����const_ui_info���飬������CHAR���͵�UI��ӵ���һ�������У��������͵�UI��ӵ��ڶ���������
  ui_info_t *const_ptr = const_ui_info;
  for (uint8_t i = 0; i < const_num; i++) 
  {
    if (memcmp(const_ptr, &zero_struct, sizeof(ui_info_t)) == 0)
    {
      const_ptr++;
      continue;
    }
    //�����ڴ���뵱ǰ��UI��Ϣ
    Node_u* newNode = (Node_u*)malloc(sizeof(Node_u));
    if (newNode == NULL)
    {
      return UI_ERROR;// heap̫С�����벻���ڴ�
    }
    newNode->ui = const_ptr;
    newNode->next = NULL;
    //�жϵ�ǰUI�Ƿ�ΪCHAR����
    if (const_ptr->ui_config.ui_type != CHAR && const_ptr->ui_config.operate_type != DELETE) 
    {
      if (*graphic_link == NULL)//�������Ϊ�գ����½ڵ�����Ϊ�����ͷ�ڵ�
      {
        *graphic_link = newNode;
      } 
      else //�������Ϊ�գ����½ڵ���ӵ������ĩβ
      {
        graphic_link_cursor->next = newNode;
      }
      graphic_link_cursor = newNode;
    } 
    else if(const_ptr->ui_config.operate_type != DELETE)//�����ǰUIΪCHAR����
    {
      if (*char_link == NULL) //�������Ϊ�գ����½ڵ�����Ϊ�����ͷ�ڵ�
      {
        *char_link = newNode;
      } 
      else //�������Ϊ�գ����½ڵ���ӵ������ĩβ
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
 * @brief �����������ȼ��ߵ�ui�ṹ��洢��һ�������У�
 *        �ڵ��ô˺���ǰӦ���ȵ���mergeSort�����������������
 *
 * @param dynamic_list_head ��̬UI�����ͷ�ڵ�
 * @param const_list_head ����UI�����ͷ�ڵ�
 * @param graphic_buffer �洢ui�ṹ�������
 * @return ui_status_e UI_ERROR������Ϊ��,û�г�ʼ������
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
    return UI_ERROR; // �ܵ�����֤��û�г�ʼ������
  }

  //��һ���ڵ�Ϊ�ַ��������ַ� PRIORITY_LOW���ַ����ڵ�һ��ʱ����
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
  
  // ָ�������ͷ�ڵ㲻Ϊ�� �� �����±�С�������С �� ��ǰ�ڵ�ķ���״̬Ϊδ����
  if (dynamic_list_cursor != NULL)
  {
    while (graphic_cnt < buffer_size && dynamic_list_cursor->ui->sent_state == MESSAGE_NOT_SENT) 
    {
      if (dynamic_list_cursor->ui->ui_config.ui_type != CHAR)
      {
        graphic_priority_buffer[graphic_cnt] = *(dynamic_list_cursor->ui);//����ǰ�ڵ��ui��Ϣ�洢��������
        dynamic_list_cursor->ui->sent_state = MESSAGE_SENT;
        graphic_cnt++;//�����±�����
      }
      else if (dynamic_list_cursor->ui->ui_config.priority == HIGH_PRIORITY)//�����ǰ�ڵ�Ϊ�ַ������ȼ�Ϊ��
      {
        if (graphic_cnt <= HIGH_CHAR_PRIORITY_LEVEL)
        {
          //��֮ǰ�����ͼ����Ϣ�ķ���״̬���δ����
          dynamic_list_cursor = dynamic_list_head;
          for (uint8_t i = 0; i < graphic_cnt && dynamic_list_cursor->next != NULL; i++)
          {
            dynamic_list_cursor->ui->sent_state = MESSAGE_NOT_SENT;
            dynamic_list_cursor = dynamic_list_cursor->next;
          }
          //��Ҫ���͵��ַ���Ϣ����buffer
          character_priority_buffer = dynamic_list_cursor->ui;
          dynamic_list_cursor->ui->sent_state = MESSAGE_SENT;
          *ui_send_mode = SEND_CHAR_MODE;
          return UI_OK;//�����ַ�
        }
      }
      else if (dynamic_list_cursor->ui->ui_config.priority == MID_PRIORITY)//�����ǰ�ڵ�Ϊ�ַ������ȼ�Ϊ��
      {
        if (graphic_cnt <= MID_CHAR_PRIORITY_LEVEL)//����ͼ��buffer�ĸ���С��5�ͷ����ַ�
        {
          //��֮ǰ�����ͼ����Ϣ�ķ���״̬���δ����
          dynamic_list_cursor = dynamic_list_head;
          for (uint8_t i = 0; i < graphic_cnt && dynamic_list_cursor->next != NULL; i++)
          {
            dynamic_list_cursor->ui->sent_state = MESSAGE_NOT_SENT;
            dynamic_list_cursor = dynamic_list_cursor->next;
          }
          //��Ҫ���͵��ַ���Ϣ����buffer
          character_priority_buffer = dynamic_list_cursor->ui;
          dynamic_list_cursor->ui->sent_state = MESSAGE_SENT;
          *ui_send_mode = SEND_CHAR_MODE;
          return UI_OK;//�����ַ�
        }
      }

      //�����һ���ڵ�Ϊ�գ��˳�ѭ��
      if(dynamic_list_cursor->next == NULL)
      {
        break;
      }
      dynamic_list_cursor = dynamic_list_cursor->next;//ָ����һ���ڵ�
    }
  }
// ʣ�²������벻��UI
  if (const_list_cursor != NULL)
  {
    while (graphic_cnt < buffer_size)
    {
      if (const_list_cursor->ui->ui_config.ui_type != CHAR)
      {
        graphic_priority_buffer[graphic_cnt] = *(const_list_cursor->ui);//����ǰ�ڵ��ui��Ϣ�洢��������
        graphic_priority_buffer[graphic_cnt].ui_config.operate_type = ADD;
        graphic_cnt++;//�����±�����
      }
      //�����һ���ڵ�Ϊ�գ��˳�ѭ��
      if(const_list_cursor->next == NULL)
      {
        const_list_cursor = const_list_head;
        break;
      }
      const_list_cursor = const_list_cursor->next;//ָ����һ���ڵ�
    }
  }
  *ui_send_mode = SEND_GRAPHIC_MODE;
  return UI_OK;//����ͼ��
}


/**
 * @brief �����ַ���Ϣ�����ͽṹ��
 * 
 * @param ui_info UI��Ϣ�ṹ��
 * @param add_operate_enable 1��ǿ��ADD 0������UI���õ�operate_type
 * @return ext_client_custom_character_t ���úõķ��ͽṹ��
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
  //��ȡUI������Ϣ
  char *name = ui_info.ui_config.name;
  uint8_t layer = ui_info.ui_config.layer;
  uint8_t color = ui_info.ui_config.color;
  uint16_t size = ui_info.ui_config.size;
  uint16_t length = strlen(ui_info.ui_config.text);
  uint16_t width = ui_info.ui_config.width;
  uint16_t start_x = ui_info.ui_config.start_x;
  uint16_t start_y = ui_info.ui_config.start_y;
  //������Ϣ���ṹ��
  graphic_data_struct_t char_buff;
	char_buff = draw_char(name,  //ͼ����
	                      operate_tpye,  //ͼ�β���
                        layer,  //ͼ������0~9
                        color,  //��ɫ
                        size,  //�����С
                        length,  //�ַ�����
                        width,  //�������
                        start_x,  //��� x ����
                        start_y);  //��� y ����

  //���÷��ͽṹ��
  ext_client_custom_character_t res;
  res.grapic_data_struct = char_buff;
  memcpy(&res.data,&ui_info.ui_config.text,sizeof(ui_info.ui_config.text));

  return res;
}

/**
 * @brief ����ͼ����Ϣ�����ͽṹ��
 * 
 * @param ui_info UI��Ϣ�ṹ��
 * @param add_operate_enable 1��ǿ��ADD 0������UI���õ�operate_type
 * @return ext_client_custom_graphic_seven_t ���úõķ��ͽṹ��
 */
ext_client_custom_graphic_seven_t Process_Graphic_To_Buffer(ui_info_t *ui_info, uint8_t ui_info_size, uint8_t add_operate_enable)
{
  ext_client_custom_graphic_seven_t res;
  ui_info_t *ui_ptr = ui_info;
  for(uint8_t i = 0; i < 7; i++)
  {
    //�ж��Ƿ��Խ��
    if (i >= ui_info_size)
    {
      return res;
    }
    //���ò�������
    operate_tpye_e operate_tpye;
    if (add_operate_enable == 0)
    {
      operate_tpye = ui_ptr->ui_config.operate_type;
    }
    else
    {
      operate_tpye = ADD;
    }
    //��ȡUI������Ϣ
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
    //�ж�UI����������Ϣ
    switch (ui_ptr->ui_config.ui_type)
    {
    case LINE:
      res.grapic_data_struct[i] = draw_line(name,  //ͼ����
                                            operate_tpye,  //ͼ�β���
                                            layer,  //ͼ������0~9
                                            color,  //��ɫ
                                            width,  //�������
                                            start_x,  //��� x ����
                                            start_y,  //��� y ����
                                            end_x,  //�յ� x ����
                                            end_y);  //�յ� y ����
      break;
    case CIRCLE:
      res.grapic_data_struct[i] = draw_circle(name,  //ͼ����
                                              operate_tpye,  //ͼ�β���
                                              layer,  //ͼ������0~9
                                              color,  //��ɫ
                                              width,  //�������
                                              start_x,  //Բ�� x ����
                                              start_y,  //Բ�� y ����
                                              radius);  //�뾶
      break;
    case RECTANGEL:
      res.grapic_data_struct[i] = draw_rectangle(name,  //ͼ����
                                                 operate_tpye,  //ͼ�β���
                                                 layer,  //ͼ������0~9
                                                 color,  //��ɫ
                                                 width,  //�������
                                                 start_x,  //���Ͻ� x ����
                                                 start_y,  //���Ͻ� y ����
                                                 end_x,  //���½� x ����
                                                 end_y);  //���½� y ����
      break;
    case ELLIPSE:
      res.grapic_data_struct[i] = draw_ellipse(name,  //ͼ����
                                               operate_tpye,  //ͼ�β���
                                               layer,  //ͼ������0~9
                                               color,  //��ɫ
                                               width,  //�������
                                               start_x,  //Բ�� x ����
                                               start_y,  //Բ�� y ����
                                               end_x,  //x ���᳤��
                                               end_y);  //y ���᳤��
      break;
    case ARC:
      res.grapic_data_struct[i] = draw_arc(name,  //ͼ����
                                           operate_tpye,  //ͼ�β���
                                           layer,  //ͼ������0~9
                                           color,  //��ɫ
                                           start_angel,  //��ʼ�Ƕ�
                                           end_angel,  //��ֹ�Ƕ�
                                           width,  //�������
                                           start_x,  //Բ�� x ����
                                           start_y,  //Բ�� y ����
                                           end_x,  //x ���᳤��
                                           end_y);  //y ���᳤��
      break;
    case FLOAT:
      res.grapic_data_struct[i] = draw_float(name,  //ͼ����
                                             operate_tpye,  //ͼ�β���
                                             layer,  //ͼ������0~9
                                             color,  //��ɫ
                                             size,  //�����С
                                             decimal,  //������
                                             width,  //�������
                                             start_x,  //��� x ����
                                             start_y, //��� y ����
                                             (int32_t) (float_num *1000));//���� 1000 ���� 32 λ��������int32_t  
      break;
    case INT:
      res.grapic_data_struct[i] = draw_int(name,  //ͼ����
                                           operate_tpye,  //ͼ�β���
                                           layer,  //ͼ������0~9
                                           color,  //��ɫ
                                           size,  //�����С
                                           width,  //�������
                                           start_x,  //��� x ����
                                           start_y,  //��� y ����
                                           int_num);  //����
      break;
    default:
      break;
    }
    ui_ptr ++;
  }
  return res;
}















/*UI���ܺ���**************************************************************************************************************/
Node_u *dynamic_list_head = NULL; // ��̬UI����ͷ
Node_u *const_list_head   = NULL; // ����UI����ͷ
Node_u *graphic_list_head = NULL; // ͼ��UI����ͷ
Node_u *char_list_head    = NULL; // �ַ�UI����ͷ

ui_info_t graphic_priority_buffer[7]; // ���ȼ���ߵ�7��ͼ��
ui_info_t character_priority_buffer;  // ���ȼ���ߵ��ַ�

ui_send_mode_e ui_send_mode; // ����ģʽ

/**
 * @brief ��ʼ��UI���� ���ⲿ���� һ��Ҫ��Ui_Send֮ǰ����
 * 
 * @param dynamic_ui_info 
 * @param dynamic_ui_num 
 * @param const_ui_info 
 * @param const_ui_num 
 */
void Init_Ui_List(ui_info_t *dynamic_ui_info, uint8_t dynamic_ui_num, ui_info_t *const_ui_info, uint8_t const_ui_num)
{
  // ��ʼ����̬UI����
  Init_Priority_LinkedList(&dynamic_list_head, dynamic_ui_info, dynamic_ui_num);
  // ��ʼ������UI����
  Init_Priority_LinkedList(&const_list_head, const_ui_info, const_ui_num);
  // ��ʼ������������dynamic_ui_info��const_ui_info���������в���CHAR���͵�UI�������һ�������������͵�UI�����һ������
  Init_Type_LinkedLists(&graphic_list_head, &char_list_head, dynamic_ui_info, const_ui_info, dynamic_ui_num, const_ui_num);
}

/**
 * @brief ��������UI
 * 
 */
ui_status_e Ui_Send_Normal()
{
  ext_client_custom_graphic_seven_t graphic_tx_buffer;   // ͼ���ͻ���
  ext_client_custom_character_t     character_tx_buffer; // �ַ����ͻ���
  //�Զ�̬UI�����������
  mergeSort(&dynamic_list_head);
  //�����ȼ���ߵ�UI��Ϣ�洢��������
  
  if (Store_High_Priority_UI(dynamic_list_head, const_list_head, graphic_priority_buffer, &character_priority_buffer, &ui_send_mode) == UI_ERROR)
  {
    return UI_ERROR; // û�г�ʼ������
  }
  //���ݷ���ģʽ���з���
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
 * @brief UIǿ�з���ADD
 * @note  ����ѡ�ֶ˵�½��ÿ��UI����Ҫ��һ��ADD��������Ҫǿ�Ʒ���һ��ADD
 *        
 * @return ui_status_e 0��error 1:�������� 2:û������
 */
ui_status_e Ui_Send_Add()
{
  static uint8_t is_send_char_finish_flag = false;
  static uint8_t is_send_graphic_finish_flag = false;

  static Node_u* graphic_list_cursor = NULL;
  static Node_u* char_list_cursor = NULL;

/*�ж�graphic_list��char_list_head��ĳ����*******************************/
  if (graphic_list_head == NULL)
  {
    is_send_graphic_finish_flag = true;//ĳ�S�͵������ˆ�
  }
  if (char_list_head == NULL)
  {
    is_send_char_finish_flag = true;//ĳ�S�͵������ˆ�
  }
/*�ж��ǵ�һ�ν�������ʼ�����******************************************/
  if (graphic_list_cursor == NULL && graphic_list_head != NULL)
  {
    graphic_list_cursor = graphic_list_head;
  }
  if (char_list_cursor == NULL && char_list_head != NULL)
  {
    char_list_cursor = char_list_head;
  }
/*��ʼ�����ͻ���******************************************/
  ext_client_custom_graphic_seven_t graphic_tx_buffer;   // ͼ���ͻ���
  ext_client_custom_character_t     character_tx_buffer; // �ַ����ͻ���
  ui_info_t graphic_info_buffer[7];                      // 7��������ͼ����Ϣ
/*���ȷ����ַ�******************************************/
  if (char_list_cursor != NULL && is_send_char_finish_flag == false)
  {
    if (char_list_cursor->next == NULL)//�����������β�����ͷ������һ��
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
/*����ͼ��******************************************/
  if (graphic_list_cursor != NULL && is_send_graphic_finish_flag == false)
  {
    //��������ȡ��7��ͼ����Ϣ
    for (uint8_t i = 0; i < 7 ; i++)
    {
      if (graphic_list_cursor->next == NULL)//�����������β�����ͷ�������
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
	/*�ж��Ƿ񶼷�����******************************************/
	if (is_send_char_finish_flag == true && is_send_graphic_finish_flag == true)//��������
  {
    //��λ���ȴ���һ�η���
    char_list_cursor = char_list_head;//�ص�ͷ�ڵ�
    graphic_list_cursor = graphic_list_head;//�ص�ͷ�ڵ�
    is_send_char_finish_flag = false;
    is_send_graphic_finish_flag = false;
    return UI_OK;//����1��֤����������
  }
  
  return UI_ERROR;//��Ӧ���ܵ��ᵽ
}

/**
 * @brief ����UI ���ⲿ����
 * 
 */
void Ui_Send()
{
  /*�ж��Ƿ��˷���ʱ��****************************/
  uint32_t currentTick = HAL_GetTick();
  static uint32_t lastTick = 0;
  if (currentTick - lastTick < SEND_INTERVAL)
  {
    return;
  }
  /*�յ���ʼ��ָ���л���־λ**********************/
  static uint8_t is_initing_ui = 0;
  if (Init_Ui_Condition())
  {
    if (is_initing_ui == 0)
    {
      is_initing_ui = 1;
    }
  }
  /*�ж��Ƿ����ڳ�ʼ��****************************/
  static uint8_t init_times = 0;
  if (is_initing_ui == 1)//���ڳ�ʼ��UI
  {
    if (Ui_Send_Add() == 1)
    {
      init_times++; // ��ʼ����һ�Σ�������һ
    }
    if (init_times >= PER_INIT_UI_TIMES)//��ʼ����PER_INIT_UI_TIMES��
    {
      is_initing_ui = 0;//��ʼ�����
      init_times = 0;
    }
  }
	else/*��������UI*/
	{		
    Ui_Send_Normal();
	}
	lastTick = HAL_GetTick();
}

/**
 * @brief ������UI��Ϣ����ô˺�����UI��Ϊ׼������״̬
 * 
 * @param ui_info 
 */
ui_status_e Enqueue_Ui_For_Sending(ui_info_t *ui_info)
{
  if (ui_info == NULL)
  {
    return UI_ERROR;
  }

  if (ui_info->sent_state == MESSAGE_SENT)//�����ȸ���ʱ�䣬δ��֮ǰһֱĳ���ָ��¾ͻ�һֱ�����ȥ
  {
    ui_info->updateTick = HAL_GetTick();
  }
  
  ui_info->sent_state = MESSAGE_NOT_SENT;

  return UI_OK;
}
