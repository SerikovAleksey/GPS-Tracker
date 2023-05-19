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


extern UART_HandleTypeDef huart2; // UART

//---------FUNCTIONS---------//

// Function to get data from GPS
int nmea_handler(uint8_t *nmea_buffer, uint8_t type_data);

// Function to check validation of received data
int check_valid_data(uint8_t *buf);

// Function to transmit data 
void transmit_data(uint8_t *buf, uint16_t len);

// Function to save time
void set_time(uint8_t type_data);

// Function to save date
void set_date();

// Function to save coordinates
void set_coordinates();

// Function to make transmited buffer
void make_buf(uint8_t type_data);

// Function to get buffer and size
BUF get_transmit_buf();

// Functions to set pointer 
void set_ind_t(uint32_t num);
void set_ind_c(uint32_t num);

#endif // _NMEA_H_