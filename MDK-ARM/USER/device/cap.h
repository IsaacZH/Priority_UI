#ifndef __CAP_H
#define __CAP_H

#include "main.h"

typedef struct 
{
    uint16_t chassis_power_buffer;  //���̹��ʻ��壬0~60J
    uint16_t chassis_power_limit;   //�����˵��̹����������ޣ�0~120W
    int16_t  output_power_limit;     //���ݷŵ繦�����ƣ�-120~300W
    uint16_t input_power_limit;     //���ݳ�繦�����ƣ�0~150W
    uint16_t chassis_volt;			//���������ѹ ��λ ���� **
	  uint16_t chassis_current;		//����������� ��λ ���� **
 
		union{
					uint16_t all;
					struct
					{
							uint16_t cap_switch : 1;    //���ݿ���
							uint16_t cap_record : 1;    //��¼���ܿ���
              uint16_t gamegoing : 1;     //����������Ϊ1������Ϊ0 ***						
					}bit;
			}cap_control;
		
}cap_send_data_t;

typedef struct
{
    float cap_Ucr;    //�������˵�ѹUcr��0~30V
    float cap_I;    //���ݵ���I��-20~20A
    union
    {
        uint16_t state;     //����״̬
        struct
        {
            uint16_t warning : 1;   //����
            uint16_t cap_U_over : 1;    //���ݹ�ѹ
            uint16_t cap_I_over : 1;    //���ݹ���
            uint16_t cap_U_low : 1;     //����Ƿѹ
            uint16_t bat_I_low : 1;     //����ϵͳǷѹ
            uint16_t can_receive_miss : 1;    //����δ���յ�CANͨ������
        }bit;
    }cap_state;
}cap_receive_data_t;



typedef enum {
	
	CAP_ONLINE,
	CAP_OFFLINE,

} cap_state_e;



typedef struct cap_info_struct {
	
	uint16_t	canId;
	
	cap_send_data_t     tx_data;
	cap_receive_data_t  rx_data;

	int16_t 	Buff0x2E[4];
	int16_t 	Buff0x2F[4];

	uint8_t   offline_cnt;
	uint8_t   offline_max_cnt;

} cap_info_t;


typedef struct cap_struct{

	cap_info_t 	info;

	void				(*modifyLimit)(struct cap_struct *self,int16_t out,int16_t in);	
	void				(*setdata)(struct cap_struct *self,uint16_t powerBuff,uint16_t powerLimit,uint16_t volt,uint16_t current);
	void				(*update)(struct cap_struct *self,uint32_t canId, uint8_t *rxBuf);
	void				(*heart_beat)(struct cap_struct *self);
	
	cap_state_e	 state;
	
}cap_t;

extern cap_t cap;

#endif

