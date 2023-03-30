#ifndef _NMEA_H_
#define _NMEA_H_

#include "stm32f1xx_hal.h"
#include <string.h>
#include<stdlib.h>


#define VALID 'A'
#define INVALID 'V'

typedef struct {
	int hour;
	int min;
	int sec;
}TIME;

typedef struct {
	int lat_deg;
	int lat_min_int;
	int lat_min_frac;
	char uLat;
	int lon_deg;
	int lon_min_int;
	int lon_min_frac;
	char uLon;
}LOCATION;

int RMC_check_valid_data(char *nmea_buffer);

TIME get_time(void);

LOCATION get_location(void);


#endif // _NMEA_H_