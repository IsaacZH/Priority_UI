/* Includes ------------------------------------------------------------------*/
#include "drv_flash.h"

#include "string.h"
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/**
  * @brief  ��ȡflash����
  * @param  addr  flash�б���ȡ���ݵ���ʼ��ַ
  * @param  buf	  �洢���ݵ���ʼ��ַ
  * @param  len		��ȡ���ݳ���,���ֽ�Ϊ��λ
  */
void Flash_ReadData(uint32_t addr, uint32_t *buf, uint16_t len)
{
	memcpy(buf, (void*)addr, len);
}

/**
  * @brief  ������д��flash,���ֽ�Ϊ��λ
  * @param  addr  flash��д�����ݵ���ʼ��ַ
  * @param  data  ��д�����ݵ���ʼ��ַ
  * @param  num		д����������
  */
void Flash_WriteByteData(uint32_t addr,uint8_t *data,uint16_t num)
{
	HAL_FLASH_Unlock();
	for(uint16_t i=0;i<num;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr+i, data[i]);
	}
	HAL_FLASH_Lock();
}

/**
  * @brief  ������д��flash,�԰���Ϊ��λ
  * @param  addr  flash��д�����ݵ���ʼ��ַ
  * @param  data  ��д�����ݵ���ʼ��ַ
  * @param  num		д����������
  */
void Flash_WriteHalfWordData(uint32_t addr,uint16_t *data,uint16_t num)
{
	HAL_FLASH_Unlock();
	for(uint16_t i=0;i<num;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr+2*i, data[i]);
	}
	HAL_FLASH_Lock();
}

/**
  * @brief  ������д��flash,����Ϊ��λ
  * @param  addr  flash��д�����ݵ���ʼ��ַ
  * @param  data  ��д�����ݵ���ʼ��ַ
  * @param  num		д����������
  */
void Flash_WriteWordData(uint32_t addr,uint32_t *data,uint16_t num)
{
	HAL_FLASH_Unlock();
	for(uint16_t i=0;i<num;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr+4*i, data[i]);
	}
	HAL_FLASH_Lock();
}

/**
  * @brief  ������д��flash,��˫��Ϊ��λ
  * @param  addr  flash��д�����ݵ���ʼ��ַ
  * @param  data  ��д�����ݵ���ʼ��ַ
  * @param  num		д����������
  */
void Flash_WriteDoubleWordData(uint32_t addr,uint64_t *data,uint16_t num)
{
	HAL_FLASH_Unlock();
	for(uint16_t i=0;i<num;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr+8*i, data[i]);
	}
	HAL_FLASH_Lock();
}

/**
  * @brief  ��������(������д��flash��ԭ���������ݵ�����ǰ��Ҫ��������)
  * @param  SectorNum  ��Ҫ������Ŀ������,ȡֵ��ΧΪ0��11(ע�ⲻҪռ���Ѿ�������ռ���˵�����)
  * @retval uint32_t	sectorError
	*					�������flash���������˴����������������ҳ��Ŵ洢��SectorError��
  */
uint32_t Flash_EraseSector(uint32_t SectorNum)
{
	FLASH_EraseInitTypeDef FLASH_Erase;
	uint32_t sectorError = 0;
	
	HAL_FLASH_Unlock();
	FLASH_Erase.TypeErase = FLASH_TYPEERASE_SECTORS;
	FLASH_Erase.Banks = FLASH_BANK_1;
	FLASH_Erase.Sector = SectorNum;
	FLASH_Erase.NbSectors = 1;
	FLASH_Erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	HAL_FLASHEx_Erase(&FLASH_Erase, &sectorError);
	HAL_FLASH_Lock();
	
	return sectorError;
}

/**
  * @brief  ��������11
  */
uint32_t Flash_EraseSector11(void)
{
	uint32_t sectorError;
	
	sectorError = Flash_EraseSector(11);
	
	return sectorError;
}

