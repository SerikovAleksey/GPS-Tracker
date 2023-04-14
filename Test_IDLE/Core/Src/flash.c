#include "flash.h"



uint32_t FLASH_Erase(uint32_t Address)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = Address;
	EraseInitStruct.NbPages = 1;
	
	uint32_t ErorPage = 0;
	
	HAL_FLASH_Unlock();
	
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &ErorPage) != HAL_OK)
	{
		return HAL_FLASH_GetError();
	}
	
	HAL_FLASH_Lock();
	return 1;
}


uint32_t FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint16_t *Data, uint16_t len)
{
	uint32_t add = Address;
	HAL_FLASH_Unlock();
	for(uint16_t i = 0; i < len; i++)
	{
			if(HAL_FLASH_Program(TypeProgram, add, Data[i]) != HAL_OK)
			{
				return HAL_FLASH_GetError();
			}
			else
			{
				add += 2;
			}
	}
	HAL_FLASH_Lock();	
	free(Data);
	return 1;
}

uint16_t *FLASH_Read(uint32_t Address, uint16_t *buf, uint16_t len)
{
	uint32_t add = Address;
	if (add == ADDR_FLASH_PAGE_127) add += 4;
	for(uint16_t i = 0; i < len; i++)
  {
		{
		buf[i] = *((uint32_t*)add);
		add += 2;
		}
  } 
	return buf;
}


uint16_t *buf_u8_to_u16(uint8_t *buf, uint16_t len_buf)
{
	uint16_t size = 0;
	if ((len_buf / 2) % 2 != 0)	
	{
		size = len_buf / 2 + 1;
	}
	else size = len_buf / 2;
	uint16_t *buf_u16 = malloc(sizeof(uint16_t) * size);
	uint8_t i_0 = 0;
	uint8_t i_1 = 1;
	for (uint16_t i = 0; i < len_buf / 2; i++)
	{
		buf_u16[i] = (buf[i_1] << 8) | buf[i_0];
		i_0 += 2;
		i_1 += 2;
	}
	if (len_buf / 2 != size) buf_u16[size - 1] = buf[len_buf - 1];

	//free(buf_u16);
	return buf_u16;
}

uint8_t *buf_u16_to_u8(uint16_t *buf, uint16_t len_buf)
{
	uint8_t *buf_u8 = malloc(sizeof(uint8_t) * len_buf * 2);
	for (uint16_t i = 0; i < len_buf; i++)
	{
		buf_u8[2*i + 1] = (uint8_t)(buf[i] >> 8);
		buf_u8[2*i] = (uint8_t)buf[i];
	}
	return buf_u8;
}


uint8_t Save_Data (uint16_t *buf, uint16_t amount_halfwords)
{
	uint16_t* new_buf = malloc(sizeof(uint16_t) * (amount_halfwords + 2));
		
	uint16_t amount_lists = 1 + (amount_halfwords + 2) / 512;
	uint16_t remainder_halfwords = (amount_halfwords + 2) % 512;
	uint32_t address_list_now = ADDR_FLASH_PAGE_127;
	
	new_buf[0] = (amount_lists + '0');
	new_buf[1] = remainder_halfwords + '0';
	for (uint16_t i = 2; i <= amount_halfwords + 1; i++)
	{
		new_buf[i] = buf[i - 2];
	}
	
	for (uint8_t i = 0; i < amount_lists - 1; i++)
	{
		if (!FLASH_Erase(address_list_now)) return 0;
		if (!FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address_list_now, &(new_buf[i * 1024]), 1024)) return 0; 
		address_list_now -= 400 * (i + 1);
	}
	if (!FLASH_Erase(address_list_now)) return 0;
	if (!FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address_list_now, &(new_buf[amount_halfwords + 2 - remainder_halfwords]), remainder_halfwords)) return 0; 
	
	free(buf);
	return 1;
}


uint16_t *Read_Data(uint16_t *buf)
{
	amount_lists = *((uint32_t*)(ADDR_FLASH_PAGE_127)) - '0';
	len1 = *((uint32_t*)(ADDR_FLASH_PAGE_127 + 2))- '0';
	for (uint16_t i = 0; i < amount_lists; i++)
	{
		if (i == amount_lists - 1) FLASH_Read(ADDR_FLASH_PAGE_127 - 400 * i, &buf[512 * i], len1 - 2);
		else FLASH_Read(ADDR_FLASH_PAGE_127 - 400 * i, &buf[512 * i], 512);
	}
	//free(buf);
	return buf;
}


