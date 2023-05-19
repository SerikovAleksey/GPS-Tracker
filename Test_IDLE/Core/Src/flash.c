#include "flash.h"

uint32_t add = 0;
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
	add = Address;
	HAL_FLASH_Unlock();
	for(uint16_t i = 0; i < len ; i++)
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
	return 1;
}

uint16_t *FLASH_Read(uint32_t Address, uint16_t *buf, uint16_t len)
{
	
	uint32_t add = (uint32_t)Address;
	for(uint16_t l = 0; l < len; l++)
  {
		buf[l] = *((uint32_t*)add);
		add += 2;
  } 
	return buf;
}


uint16_t *buf_u8_to_u16(uint8_t *buf, uint16_t len_buf)
{
	uint16_t u16_size = 0;
	if ((len_buf / 2) % 2 != 0)	
	{
		u16_size = len_buf / 2 + 1;
	}
	else u16_size = len_buf / 2;
		
	uint16_t i_0 = 0;
	uint16_t i_1 = 1;
	buf_u16[0] = u16_size;
	
	for (uint16_t i = 1; i < u16_size + 1; i++)
	{
		buf_u16[i] = (buf[i_1] << 8) | buf[i_0];
		i_0 += 2;
		i_1 += 2;
	}
	return buf_u16;
}

uint8_t *buf_u16_to_u8(uint16_t *buf, uint16_t len_buf)
{
	for (uint16_t i = 1; i < len_buf + 1; i++)
	{
		buf_u8[2*(i - 1) + 1] = (uint8_t)(buf[i] >> 8);
		buf_u8[2*(i - 1)] = (uint8_t)buf[i];
	}
	return buf_u8;
}


uint8_t Save_Data (uint16_t *buf, uint16_t amount_halfwords)
{

	
	if(amount_halfwords == 1)
	{
		if (!FLASH_Erase(ADDR_AMOUNT_PAGES)) return 0;
		if (!FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ADDR_AMOUNT_PAGES, &(buf[0]), amount_halfwords)) return 0;
	}else
	{
		if (!FLASH_Erase(address_list_now)) return 0;
		if (!FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address_list_now, &(buf[0]), amount_halfwords)) return 0;
		address_list_now -= ((uint32_t)(0x0000400));
	}
	return 1;
}


uint16_t *Read_Data(uint32_t Add_page, uint16_t len)
{
	FLASH_Read(Add_page, &buf_u16[0], len);
	return buf_u16;
}



