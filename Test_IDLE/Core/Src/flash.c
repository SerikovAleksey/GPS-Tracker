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
	//uint16_t size = len;
	uint32_t add = (uint32_t)Address;
	//if ((uint32_t)Address == (uint32_t)ADDR_FLASH_PAGE_126)
	{
		//add += (uint32_t)4;
		//size = len - 2;
	}
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
	//if (len_buf / 2 != size) buf_u16[size - 1] = buf[len_buf - 1];

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


//uint8_t Save_Data (uint16_t *buf, uint16_t amount_halfwords, uint16_t *new_buf)
uint8_t Save_Data (uint16_t *buf, uint16_t amount_halfwords)
{
	//uint16_t amount_lists = 1 + (amount_halfwords + 2) / 512;
	//uint16_t remainder_halfwords = (amount_halfwords + 2) % 512;
	
	//new_buf[0] = (amount_lists + '0');
	//new_buf[1] = remainder_halfwords + '0';
	//for (uint16_t i = 2; i < amount_halfwords + 2; i++)
	{
		//new_buf[i] = buf[i - 2];
	}
	
	if(amount_halfwords == 1)
	{
		if (!FLASH_Erase(ADDR_AMOUNT_PAGES)) return 0;
		if (!FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, ADDR_AMOUNT_PAGES, &(buf[0]), amount_halfwords)) return 0;
	}else
	//for (uint8_t i = 0; i < amount_lists - 1; i++)
	{
		if (!FLASH_Erase(address_list_now)) return 0;
		//if (!FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address_list_now, &(new_buf[i * 512]), 512)) return 0; 
		if (!FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address_list_now, &(buf[0]), amount_halfwords)) return 0;
		address_list_now -= ((uint32_t)(0x0000400));
	}
	
	//if (!FLASH_Erase(address_list_now)) return 0;
	//if (!FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address_list_now, &(new_buf[amount_halfwords + 2 - remainder_halfwords]), remainder_halfwords)) return 0; 
	
	return 1;
}


uint16_t *Read_Data(uint32_t Add_page, uint16_t len)
{
	//amount_lists = *((uint32_t*)(ADDR_AMOUNT_PAGES)) - '0';
	//uint16_t len1 = *((uint32_t*)(ADDR_REMAINEDR_SIZE))- '0';
	//uint16_t size = 512;
	//for (uint16_t i = 0; i < amount_lists; i++)
	{
		FLASH_Read(Add_page, &buf_u16[0], len);
		/*if (i == 0) FLASH_Read( ADDR_FLASH_PAGE_127 , &buf[0], 510);
		if (i == 1 && amount_lists == 2) FLASH_Read( ADDR_FLASH_PAGE_127 - ((uint32_t)(0x0000400)), &buf[510], len1);
		if (i == 1 && amount_lists != 2) FLASH_Read( ADDR_FLASH_PAGE_127 - ((uint32_t)(0x0000400)), &buf[510], 512);
		if (i > 1)
		{
			if (i == amount_lists - 1) FLASH_Read( ADDR_FLASH_PAGE_127 - ((uint32_t)(0x0000400 * (uint32_t)i)), &buf[510 + 512 * (i - 1)], len1);
			else FLASH_Read( ADDR_FLASH_PAGE_127 - ((uint32_t)(0x0000400 * (uint32_t)i)), &buf[510 + 512 * (i - 1)], 512);
		}*/
	}
	//free(buf);
	return buf_u16;
}



