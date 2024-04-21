/**
  ******************************************************************************
  * @file           : math_support.c\h
  * @brief          : 
  * @note           : 2022-3-3 15:27:58
  ******************************************************************************
  */
	
#include "math_support.h"


/**
  * @brief  低通滤波
  * @param  
  * @retval 
  */
float lowpass(float X_new, float X_last, float K)
{
	return (X_last + (X_new - X_last) * K);
}

float lowpass_imu(float a, float last, float now)
{
	return ((1 - a) * last + a * now);
}
/**
  * @brief  求平均值
  * @param  
  * @retval 
  */
float ave(int16_t sum, float ave_last, float new_value)
{
	if(sum < 0)
	{
		return 0;
	}
	return ( (ave_last * sum + new_value) / (sum + 1) );
}

/**
  * @brief  字符串转数值（仅支持整数，支持负数）
  * @param  
  * @retval 
  */
int16_t str_to_num(uint8_t *str,uint16_t len)
{
	uint8_t minus_flag;
	uint16_t i;
	float result = 0;
	
	if(str[0] == '-')
	{
		minus_flag = 1;
		i = 1;
	}
	else
	{
		minus_flag = 0;
		i = 0;
	}
	
	for(;i<len;i++)
	{
		result += (str[i] - '0') * pow(10,len - i - 1);
	}
	
	if(minus_flag == 1)
	{
		result *= -1;
	}
	
	return result;
}

/**
  * @brief  数值转字符串（仅支持九位及九位以内整数，支持负数）
  * @param  
  * @retval 
  */
uint8_t num_to_str(int16_t num, uint8_t *str, uint16_t *len)
{
	uint8_t str_temp[10] = "0000000000";
	uint16_t str_index_temp = 0;
	uint16_t str_len_temp;
	int16_t num_temp = num;

	for(;num != 0;num /= 10)
	{
		str_temp[str_index_temp] = '0' + abs(num % 10);
		str_index_temp++;
	}

	if(str_index_temp > 9)
	{
		return 1;
	}

	/* 正负判断 */
	if(num_temp < 0)
	{
		str_temp[str_index_temp] = '-';
		str_index_temp++;
	}

	*len = str_index_temp;

	for(str_len_temp = str_index_temp; str_index_temp > 0; str_index_temp--)
	{
		str[str_len_temp - str_index_temp] = str_temp[str_index_temp-1];
	}

	return 0;
}

/**
  * @brief  数值转字符串（有确定长度）
  * @param  
  * @retval 
  */
void num_to_str_2(uint16_t num, uint8_t *str, uint16_t len)
{
	uint8_t str_temp[10] = "0000000000";
	uint16_t str_index_temp = 0;

	for(;num != 0;num /= 10)
	{
		str_temp[str_index_temp] = '0' + abs(num % 10);
		str_index_temp++;
	}
	
	int8_t pass = len - str_index_temp;
	if(pass < 0)
	{
		return;
	}
	
	for(int i = len - 1; i >= 0; i--)
	{
		if(i < pass)
		{
			str[i] = '0';
		}
		else 
		{
			str[i] = str_temp[len - 1 - i];
		}
	}
}

/**
  * @brief  数值转字符串（有确定长度）
  * @param  
  * @retval 
  */
void num_to_str_3(int16_t num, uint8_t *str, uint16_t len)
{
	uint8_t str_temp[10] = "0000000000";
	uint16_t str_index_temp = 0;
	int16_t num_temp = num;

	for(;num != 0;num /= 10)
	{
		str_temp[str_index_temp] = '0' + abs(num % 10);
		str_index_temp++;
	}
	
	/* 正负判断 */
	if(num_temp < 0)
	{
		str_temp[str_index_temp] = '-';
		str_index_temp++;
	}
	
	int8_t pass = len - str_index_temp;
	if(pass < 0)
	{
		return;
	}
	
	for(int i = len - 1; i >= 0; i--)
	{
		if(i < pass)
		{
			str[i] = ' ';
		}
		else 
		{
			str[i] = str_temp[len - 1 - i];
		}
	}
}
