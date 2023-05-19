#ifndef _FLASH_
#define _FLASH_

//---------INCLUDES---------//
#include "stm32f1xx_hal.h"
#include <stdlib.h>

//---------DEFINES---------//
#define ADDR_FLASH_PAGE_126   ((uint32_t)0x0801F800) /* Base @ of Page 126, 1 Kbytes */
#define ADDR_AMOUNT_PAGES     ((uint32_t)0x0801FC00)
#define ADDR_REMAINEDR_SIZE   ((uint32_t)0x0801FC02)

//---------VARIABLES---------//
static uint16_t amount_lists = 1; //Shows how many pages are written
static uint32_t address_list_now = ADDR_FLASH_PAGE_126; //Shows the last page of recording
static uint16_t buf_u16[1800]; 
static uint8_t buf_u8[3600];

//---------FUNCTIONS---------//
// Function to erase flash-memory page
uint32_t FLASH_Erase(uint32_t Address);

// Function to write in flash-memory page
uint32_t FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint16_t *Data, uint16_t len);

// Function to read feom flash-memory page
uint16_t *FLASH_Read (uint32_t Address, uint16_t *buf, uint16_t len);

// Function to make uint16_t buf from uint8_t
uint16_t *buf_u8_to_u16(uint8_t *buf, uint16_t len_buf);

// Function to make uint8_t buf from uint16_t
uint8_t *buf_u16_to_u8(uint16_t *buf, uint16_t len_buf);

// Function to save data in flash-memory
uint8_t Save_Data (uint16_t buf[], uint16_t amount_halfwords);

// Function to read data from flash-memory
uint16_t *Read_Data(uint32_t Add_page, uint16_t len);

#endif //_FLASH_