# Priority_UI

- [实现的功能](#实现的功能)
- [实现的方法](#实现的方法)
  - [初始化链表](#初始化链表)
  - [优先级排序算法](#优先级排序算法)
  - [配置发送缓存](#配置发送缓存)
  - [发送UI](#发送UI)
  - [更新UI信息](#更新UI信息)
- [移植方法](#移植方法)
  - [配置 ui_protocol.c](#配置-ui_protocolc)
  - [配置 priority_ui.c](#配置-priority_uic)
  - [配置 ui.c](#配置-uic)
  - [确保Heap大小足够存放所有UI信息](#确保heap大小足够存放所有ui信息)

## 实现的功能
- 通过优先级调度算法，管理每一个包要发送的UI内容。用户只需要初始化UI的信息，定义UI的优先级，并更行UI的内容，Priority_UI会自动调度UI的发送顺序。
## 实现的方法
- 初始化链表：
  - 把每个UI信息结构体的地址存入四个链表中：动态UI链表、不变UI链表、图形UI链表、字符UI链表
  ***
- 优先级排序算法：
  - 高中低三种优先级有不同的权重，将该UI对应的优先级权重加上该UI被阻塞的时间，得到该UI的优先级值。
  - 优先比较UI发送状态，没发送过的UI优先级比发送过的UI高，发送状态相同时，再比较优先级值。
  - 这样就可以实现高优先级的UI优先发送，当高优先级的UI太多阻塞低优先级UI过久时，低优先级的UI也可以被发送出去。而且当在更新UI时，遍历到发送过的UI时就证明所有要更新的UI都已经发送过了。
  - 每次更新UI前都用归并排序对动态UI链表进行排序，保证高优先级的在前面。使用归并排序的原因是归并排序的时间复杂度恒为O(nlogn)。
  ***
- 配置发送缓存：
  
  由于不能同时发送图形和字符类的UI，所以要判断当前发送是发图形UI还是字符UI。
  - 如果动态UI链表的第一位是字符类UI则本次发送字符UI。
  - 如果动态UI链表的前X位有中优先级的字符类UI，则本次发送字符UI。（X需要用户配置）
  - 如果动态UI链表的前7位有高优先级的字符类UI，则本次发送字符UI。
  - 其他时候发送图形UI。
  
  判断好发送类型后，将对应的字符UI或优先级最高的7个图新UI存入发送缓存。如果发送不满7个，会从不变UI链表中拿几个填满。
  ***
- 发送UI：

  发送前要判断这次的发送模式，是初始化UI还是更新UI，不满足用户定义的初始化UI条件则发送更新UI。
  - 初始化UI：遍历字符UI链表和图形UI链表，先发字符再发图形，把所有UI发送一次ADD
  - 更新UI：对动态UI链表进行排序，配置发送缓冲，发送。
  ***
- 更新UI信息：

  更改对应结构体的内容，然后调用更新UI函数来更新现在的发送状态和更新的Tick。 
## 移植方法
  - 需要移植的文件：
    - <font color=DeepSkyBlue>ui_protocol.c</font> ----- UI的裁判系统协议文件
    - <font color= Violet>ui_protocol.h</font>  
    - <font color=DeepSkyBlue>priority_ui.c</font> ------ 优先级UI的实现文件
    - <font color= Violet>priority_ui.h</font>
    - <font color=DeepSkyBlue>ui.c</font> --------------- [示例应用代码] 定义UI信息，更新UI信息
    - <font color= Violet>ui.h</font>
    ***
  - 配置 <font color=DeepSkyBlue>ui_protocol.c</font>
    - 和裁判系统通信的串口
  
      ```C
      #define UI_huart huart4
      ``` 
    - 判断红蓝发配置id
      
      ```C
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
      ``` 
    ***
  - **配置 <font color=DeepSkyBlue>priority_ui.c</font>** 
    1. 高中低优先级的权重值
    
      ```C
      #define HIGH_PRIORITY_WEIGHT 1000 // 高优先级权重
      #define MID_PRIORITY_WEIGHT  500  // 中优先级权重
      #define LOW_PRIORITY_WEIGHT  0    // 低优先级权重
      ```
    $\qquad$在此示例配置下，中优先级UI被阻塞500ms后优先级值就会高于高先级UI的优先级值，低优先级同理。

    2. 字符抢占图形的排位
 
      ```C
      #define HIGH_CHAR_PRIORITY_LEVEL 7  // 高优先级字符抢图形UI的等级
      #define MID_CHAR_PRIORITY_LEVEL  5  // 中优先级字符抢图形UI的等级
      ```
    $\qquad$在此示例配置下，当动态UI链表的前7位有高优先级的字符UI时，本次发送字符UI，当动态UI链表的前5位有中优先级的字符UI时，本次发送字符UI。其他时候发送图形UI。

    3. 发送间隔时间(MS)

      ```C
      #define SEND_INTERVAL  100 // 100ms发一次
      ```

    4. 每次初始化的次数

      ```C
      #define PER_INIT_UI_TIMES    1   // 每次初始化的UI次数
      ```

    5. 定义初始化UI的条件的函数，在每次发送前会调用此函数，如果该函数返回true，则把所有UI发送<font color=CornflowerBlue>PER_INIT_UI_TIMES</font>次ADD，函数返回true则正常更新UI。
  
      ```C
      bool Init_Ui_Condition()
      {
        if (/*初始化UI的条件*/)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      ```
    ***
  - **配置 <font color=DeepSkyBlue>ui.c</font>**
  1. 定义一个动态ui结构体和一个不变ui结构体配置初始UI信息
      - operate_type（操作类型）配置提示：
        - 对于不变UI，可以不配置operate_type
        - 对于一直要显示的动态UI：operate_type = MODIFY
        - 对于会进行删除操作的动态UI：operate_type = DELETE,这样才初始化UI时，才不会给这类UI发ADD，需要用户通过后续更新UI时发送ADD

      ```C
      //存储动态UI信息
       ui_info_t dynamic_ui_info [] = 
       {
       [0] = {
       /*******不变配置*********/
       .ui_config.priority = MID_PRIORITY, // UI优先级(仅动态UI需要配置)
       .ui_config.ui_type = LINE,         // UI内容类型
       .ui_config.name = "g1",              // 图形名称
       /*******可变配置*********/
       .ui_config.operate_type = MODIFY,    // 操作类型
       .ui_config.layer = 1,                // 图层数，0~9
       .ui_config.color = GREEN,            // 颜色
       .ui_config.width = 3,                // 线条宽度
       .ui_config.start_x = 0               // 起点 x 坐标
       .ui_config.start_y = Client_mid_position_y + 0,              // 起点 y   坐标
       .ui_config.end_x = Client_mid_position_x - 176,                // 终点   x 坐标
       .ui_config.end_y = Client_mid_position_y + 305,                // 终点   y 坐标
       },
       [1] = {
         ...
       },
        .......
       };

        //存储不变UI信息
       ui_info_t const_ui_info [] = 
       {
         ....
       };
      ```

2. 初始化链表，可以在main.c中调用这个函数
  
      ```C
      void My_Ui_Init(void)
      {
      Init_Ui_List(dynamic_ui_info, sizeof(dynamic_ui_info)/sizeof       (ui_info_t),  const_ui_info, sizeof(const_ui_info)/sizeof(ui_info_t));
      }
      ```

3. 更新UI数据，将UI设为准备发送
  
      ```C
      Enqueue_Ui_For_Sending(&dynamic_ui_info[/*所更新的UI*/]); 
      ```
    ***
- **确保Heap大小足够存放所有UI信息**
    
    - 链表一个节点的大小为8字节，四个链表的大小一共为：[8* 2* (动态UI个数+不变UI个数)] 字节
    - Heap的大小至少为上面所需大小的两倍，空间不够时申请内存就会失败，初始化链表函数会返回UI_ERROR  
    - 在CubeMX->Project Manger->Minimum Heap Size 中调整Heap大小
  