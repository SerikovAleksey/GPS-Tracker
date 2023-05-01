#ifndef _NMEA_H_
#define _NMEA_H_

//---------INCLUDES---------//
#include "stm32f1xx_hal.h"
#include <string.h>
//#include <stdlib.h>

//---------DEFINES---------//
#define VALID 'A' // data from GPS valid
#define INVALID 'V' // data from GPS invalid
#define AVERAGE 'A' // average point (it says that current point deffers from the previuos)
#define SPECIAL 'S' // special point (it says that button "safe point" was pushed)

//---------VARIABLES---------//
static char string[3] = {"RMC"}; // need to find necessary string with current location, time and date
static char time[12] = { 0 }; // buf for time
static char location[30] = { 0 }; // buf for location
static int data_valid = 0; // says that location can be read

typedef struct {
	uint8_t *buf;
	uint16_t size;
}BUF; // struct to save buffer and its size


static uint32_t ind_t = 6;
static uint32_t ind_c = 0;


extern UART_HandleTypeDef huart2; // UART

//---------FUNCTIONS---------//

// Function to get data from GPS
int get_data_from_GPS(uint8_t *nmea_buffer, uint8_t type_data);

int check_valid_data(uint8_t *buf);

// Function to transmit data 
void transmit_data(uint8_t *buf, uint16_t len);

void set_time(uint8_t type_data);

void set_date();

void set_coordinates();

void make_buf(uint8_t type_data);

BUF get_transmit_buf();

#endif // _NMEA_H_