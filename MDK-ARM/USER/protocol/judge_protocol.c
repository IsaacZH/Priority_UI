/**
 * @file        judge_protocol.c
 * @author      RobotPilots@2022
 * @Version     V1.0
 * @date        3-November-2021
 * @brief       judge_protocol
 */

#include "judge_protocol.h"
#include "drv_uart.h"
#include "drv_can.h"
#include "string.h"
#include "usart.h"
#include "crc.h"

/**
 * @brief �ж��Լ���ʲô��ɫ->���±�����ID->�����Լ���ID
 * 
 */
void Determine_ID(void)
{
	if(judge.game_robot_status.robot_id < 10)//�������˵�ID���췽
	{
    judge.ids.teammate_hero      = 1;
    judge.ids.teammate_engineer  = 2;
    judge.ids.teammate_infantry3 = 3;
    judge.ids.teammate_infantry4 = 4;
    judge.ids.teammate_infantry5 = 5;
    judge.ids.teammate_plane     = 6;
    judge.ids.teammate_sentry    = 7;

    judge.ids.client_hero      = 0x0101;
    judge.ids.client_engineer  = 0x0102;
    judge.ids.client_infantry3 = 0x0103;
    judge.ids.client_infantry4 = 0x0104;
    judge.ids.client_infantry5 = 0x0105;
    judge.ids.client_plane     = 0x0106;

    if     (judge.game_robot_status.robot_id == hero_red)//����ˢ�·����ڱ����и�����ɫ
			judge.self_client = judge.ids.client_hero;
		else if(judge.game_robot_status.robot_id == engineer_red)
			judge.self_client = judge.ids.client_engineer;
		else if(judge.game_robot_status.robot_id == infantry3_red)
			judge.self_client = judge.ids.client_infantry3;
		else if(judge.game_robot_status.robot_id == infantry4_red)
			judge.self_client = judge.ids.client_infantry4;
		else if(judge.game_robot_status.robot_id == infantry5_red)
			judge.self_client = judge.ids.client_infantry5;
		else if(judge.game_robot_status.robot_id == plane_red)
			judge.self_client = judge.ids.client_plane;
	}
	else //����
	{
    judge.ids.teammate_hero      = 101;
    judge.ids.teammate_engineer  = 102;
    judge.ids.teammate_infantry3 = 103;
    judge.ids.teammate_infantry4 = 104;
    judge.ids.teammate_infantry5 = 105;
    judge.ids.teammate_plane     = 106;
    judge.ids.teammate_sentry    = 107;

    judge.ids.client_hero      = 0x0165;
    judge.ids.client_engineer  = 0x0166;
    judge.ids.client_infantry3 = 0x0167;
    judge.ids.client_infantry4 = 0x0168;
    judge.ids.client_infantry5 = 0x0169;
    judge.ids.client_plane     = 0x016A;

    if     (judge.game_robot_status.robot_id == hero_blue)
			judge.self_client = judge.ids.client_hero;
		else if(judge.game_robot_status.robot_id == engineer_blue)
			judge.self_client = judge.ids.client_engineer;
		else if(judge.game_robot_status.robot_id == infantry3_blue)
			judge.self_client = judge.ids.client_infantry3;
		else if(judge.game_robot_status.robot_id == infantry4_blue)
			judge.self_client = judge.ids.client_infantry4;
		else if(judge.game_robot_status.robot_id == infantry5_blue)
			judge.self_client = judge.ids.client_infantry5;
		else if(judge.game_robot_status.robot_id == plane_blue)
			judge.self_client = judge.ids.client_plane;
	}
}

judge_t judge = {
	.judge_offline_max_cnt = 30,//ʧ���������ֵ
};
uint16_t frame_length;
void judge_update(judge_t *judge,uint8_t *rxBuf)
{
	if(Verify_CRC8_Check_Sum(rxBuf, LEN_FRAME_HEAD) == true)//֡ͷCRCУ��
	{
		memcpy(&judge->fream_header, rxBuf, LEN_FRAME_HEAD);//��ȡ֡ͷ��Ϣ
		frame_length = LEN_FRAME_HEAD + LEN_CMD_ID + judge->fream_header.data_length + LEN_FRAME_TAIL;//����֡��
		if(judge->fream_header.sof == JUDGE_FRAME_HEADER)//SOFΪ0xA5
		{
			if(Verify_CRC16_Check_Sum(rxBuf, frame_length) == true) //֡βCRCУ��
			{
				uint32_t cmd_id = rxBuf[5] | (rxBuf[6]<<8);//��ȡ����ID
				judge->judge_offline_cnt = 0;//���ʧ������		
				switch(cmd_id)
				{
					case ID_game_state:					
						memcpy(&judge->game_status,rxBuf+7, judge->fream_header.data_length);					
					break;
					case ID_game_result:
						memcpy(&judge->game_result,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_game_robot_HP:
						memcpy(&judge->game_robot_HP,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_supply_projectile_action:
						memcpy(&judge->supply_projectile_action,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_referee_warning:
						memcpy(&judge->referee_warning,rxBuf+7, judge->fream_header.data_length);
					break;

					case ID_game_robot_status:
						memcpy(&judge->game_robot_status,rxBuf+7, judge->fream_header.data_length);		
					break;
					case ID_power_heat_data:
						memcpy(&judge->power_heat_data,rxBuf+7, judge->fream_header.data_length);
						
					break;
					case ID_game_robot_pos:
						memcpy(&judge->game_robot_pos,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_buff_musk:
						memcpy(&judge->buff,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_aerial_robot_energy:
						memcpy(&judge->aerial_robot_energy,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_robot_hurt:
						memcpy(&judge->robot_hurt,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_shoot_data:
						memcpy(&judge->shoot_data,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_bullet_remaining:
						memcpy(&judge->bullet_remaining,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_rfid_status:
						memcpy(&judge->rfid_status,rxBuf+7, judge->fream_header.data_length);
					break;
					case ID_dart_client_cmd:
						memcpy(&judge->dart_client_cmd,rxBuf+7, judge->fream_header.data_length);
					break;


					default:
					break;
				}
			}
		}
		if(rxBuf[frame_length] == JUDGE_FRAME_HEADER)//���ֶ�֡�ٴζ�ȡ
			judge_update(judge,&rxBuf[frame_length]);
	}
}

//������ϵͳʧ��
void check_judge_offline(judge_t *judge)
{
	judge->judge_offline_cnt++;
	if(judge->judge_offline_cnt > judge->judge_offline_max_cnt)
	{
		judge->judge_offline_cnt = judge->judge_offline_max_cnt;
		judge->judge_work_state = DEV_OFFLINE;
	}
	else if(judge->judge_work_state == DEV_OFFLINE)
		judge->judge_work_state = DEV_ONLINE;
	
}	

