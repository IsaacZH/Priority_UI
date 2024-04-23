# Priority_UI
  - [ʵ�ֵĹ���](#ʵ�ֵĹ���)
  - [ʵ�ֵķ���](#ʵ�ֵķ���)
  - [��ֲ����](#��ֲ����)
  - [](#)

## ʵ�ֵĹ���
- ͨ�����ȼ������㷨������ÿһ����Ҫ���͵�UI���ݡ��û�ֻ��Ҫ��ʼ��UI����Ϣ������UI�����ȼ���������UI�����ݣ�Priority_UI���Զ�����UI�ķ���˳��
## ʵ�ֵķ���
- ��ʼ������
  - ��ÿ��UI��Ϣ�ṹ��ĵ�ַ�����ĸ������У���̬UI��������UI����ͼ��UI�����ַ�UI����
- ���ȼ������㷨��
  - ���е��������ȼ��в�ͬ��Ȩ�أ�����UI��Ӧ�����ȼ�Ȩ�ؼ��ϸ�UI��������ʱ�䣬�õ���UI�����ȼ�ֵ��
  - ���ȱȽ�UI����״̬��û���͹���UI���ȼ��ȷ��͹���UI�ߣ�����״̬��ͬʱ���ٱȽ����ȼ�ֵ��
  - �����Ϳ���ʵ�ָ����ȼ���UI���ȷ��ͣ��������ȼ���UI̫�����������ȼ�UI����ʱ�������ȼ���UIҲ���Ա����ͳ�ȥ�����ҵ��ڸ���UIʱ�����������͹���UIʱ��֤������Ҫ���µ�UI���Ѿ����͹��ˡ�
  - ÿ�θ���UIǰ���ù鲢����Զ�̬UI����������򣬱�֤�����ȼ�����ǰ�档ʹ�ù鲢�����ԭ���ǹ鲢�����ʱ�临�ӶȺ�ΪO(nlogn)��
- ���÷��ͻ��棺
  
  ���ڲ���ͬʱ����ͼ�κ��ַ����UI������Ҫ�жϵ�ǰ�����Ƿ�ͼ��UI�����ַ�UI��
  - �����̬UI����ĵ�һλ���ַ���UI�򱾴η����ַ�UI��
  - �����̬UI�����ǰXλ�������ȼ����ַ���UI���򱾴η����ַ�UI����X��Ҫ�û����ã�
  - �����̬UI�����ǰ7λ�и����ȼ����ַ���UI���򱾴η����ַ�UI��
  - ����ʱ����ͼ��UI��
  
  �жϺ÷������ͺ󣬽���Ӧ���ַ�UI�����ȼ���ߵ�7��ͼ��UI���뷢�ͻ��档������Ͳ���7������Ӳ���UI�������ü���������

- ����UI��

  ����ǰҪ�ж���εķ���ģʽ���ǳ�ʼ��UI���Ǹ���UI���������û�����ĳ�ʼ��UI�������͸���UI��
  - ��ʼ��UI�������ַ�UI�����ͼ��UI�����ȷ��ַ��ٷ�ͼ�Σ�������UI����һ��ADD
  - ����UI���Զ�̬UI��������������÷��ͻ��壬���͡�
- ����UI��Ϣ��

  ���Ķ�Ӧ�ṹ������ݣ�Ȼ����ø���UI�������������ڵķ���״̬�͸��µ�Tick�� 
## ��ֲ����
  - ��Ҫ��ֲ���ļ���
    - <font color=DeepSkyBlue>ui_protocol.c</font> ----- UI�Ĳ���ϵͳЭ���ļ�
    - <font color= Violet>ui_protocol.h</font>  
    - <font color=DeepSkyBlue>priority_ui.c</font> ------ ���ȼ�UI��ʵ���ļ�
    - <font color= Violet>priority_ui.h</font>
    - <font color=DeepSkyBlue>ui.c</font> --------------- [ʾ��Ӧ�ô���] ����UI��Ϣ������UI��Ϣ
    - <font color= Violet>ui.h</font>
  - ���� <font color=DeepSkyBlue>ui_protocol.c</font>
    - �Ͳ���ϵͳͨ�ŵĴ���
  
      ```C
      #define UI_huart huart4
      ``` 
    - �жϺ���������id
      
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
  - ���� <font color=DeepSkyBlue>priority_ui.c</font> 
    - ���е����ȼ���Ȩ��ֵ
    
      ```C
      #define HIGH_PRIORITY_WEIGHT 1000 // �����ȼ�Ȩ��
      #define MID_PRIORITY_WEIGHT  500  // �����ȼ�Ȩ��
      #define LOW_PRIORITY_WEIGHT  0    // �����ȼ�Ȩ��
      ```
    $\qquad$�ڴ�ʾ�������£������ȼ�UI������500ms�����ȼ�ֵ�ͻ���ڸ��ȼ�UI�����ȼ�ֵ�������ȼ�ͬ��

    - �ַ���ռͼ�ε���λ
 
      ```C
      #define HIGH_CHAR_PRIORITY_LEVEL 7  // �����ȼ��ַ���ͼ��UI�ĵȼ�
      #define MID_CHAR_PRIORITY_LEVEL  5  // �����ȼ��ַ���ͼ��UI�ĵȼ�
      ```
    $\qquad$�ڴ�ʾ�������£�����̬UI�����ǰ7λ�и����ȼ����ַ�UIʱ�����η����ַ�UI������̬UI�����ǰ5λ�������ȼ����ַ�UIʱ�����η����ַ�UI������ʱ����ͼ��UI��

    - ���ͼ��ʱ��(MS)

      ```C
      #define SEND_INTERVAL  100 // 100ms��һ��
      ```

    - ÿ�γ�ʼ���Ĵ���

      ```C
      #define PER_INIT_UI_TIMES    1   // ÿ�γ�ʼ����UI����
      ```

    - �����ʼ��UI�������ĺ�������ÿ�η���ǰ����ô˺���������ú�������true���������UI����<font color=CornflowerBlue>PER_INIT_UI_TIMES</font>��ADD����������true����������UI��
  
      ```C
      bool Init_Ui_Condition()
      {
        if (/*��ʼ��UI������*/)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      ```

  - ���� <font color=DeepSkyBlue>ui.c</font>
    - ����һ����̬ui�ṹ���һ������ui�ṹ�����ó�ʼUI��Ϣ
  - ```C
    ui_info_t dynamic_ui_info [] = 
    {
    [0] = {
    /*******��������*********/
    .ui_config.priority = MID_PRIORITY, // UI���ȼ�(����̬UI��Ҫ����)
    .ui_config.ui_type = LINE,         // UI��������
    .ui_config.name = "g1",              // ͼ������
    /*******�ɱ�����*********/
    .ui_config.operate_type = MODIFY,    // ��������
    .ui_config.layer = 1,                // ͼ������0~9
    .ui_config.color = GREEN,            // ��ɫ
    .ui_config.width = 3,                // �������
    .ui_config.start_x = 0               // ��� x ����
    .ui_config.start_y = Client_mid_position_y + 0,              // ��� y ����
    .ui_config.end_x = Client_mid_position_x - 176,                // �յ� x ����
    .ui_config.end_y = Client_mid_position_y + 305,                // �յ� y ����
    },
    
    ...
    };
    ```
 


## 
