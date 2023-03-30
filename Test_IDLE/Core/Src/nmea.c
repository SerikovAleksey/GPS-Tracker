#include "nmea.h"
char string[3] = {"RMC"};
char time[100] = { 0 };
char location[100] = { 0 };
int data_valid = 0;

TIME Time;
LOCATION Location;

int RMC_check_valid_data(char *nmea_buffer) 
{
	uint16_t nmea_indx = 0;
	uint8_t str_indx = 0;
	uint16_t len_str = strlen (string);
	uint16_t k = 0;
	uint8_t amount_comma = 0;
	uint8_t i = 0;

	
	
	while (nmea_buffer[nmea_indx] != string[str_indx])
	{
		nmea_indx++;
	}
	
	while (len_str > str_indx && nmea_buffer[nmea_indx++] == string[str_indx])
	{
		str_indx++;
	}
	
	if (len_str == str_indx)
	{
		while (nmea_buffer[nmea_indx] != VALID && nmea_buffer[nmea_indx] != INVALID)
		{
			if (nmea_buffer[nmea_indx] == ',' && k < 6) nmea_indx++;
			if (k < 6) time[k++] = nmea_buffer[nmea_indx++];
			else nmea_indx++;
		}
		 
		if (nmea_buffer[nmea_indx] == INVALID) 
		{
			data_valid = -1;
		}
		if (nmea_buffer[nmea_indx] == VALID) 
		{
			data_valid = 1;
		}
		while (data_valid == 1 && nmea_buffer[++nmea_indx] != 'E' && i < 30)
		{
			if (nmea_buffer[nmea_indx] == ',') nmea_indx++;
			location[i++] = nmea_buffer[nmea_indx];
		}
		/*while (k < 12)
		{
			time[k++] = nmea_buffer[nmea_indx++];
			//if (nmea_buffer[nmea_indx] == ',') amount_comma++;
			//nmea_indx++;
		}
		//while (k < 12)
		{
			//time[k++] = nmea_buffer[nmea_indx++];
		}*/
	}
	return data_valid;
}

TIME get_time(void)
{
	Time.hour = (time[0] - '0') * 10 + (time[1] - '0');
	Time.min = (time[2] - '0') * 10 + (time[3] - '0');
	Time.sec = (time[4] - '0') * 10 + (time[5] - '0');
	return Time;
}

LOCATION get_location(void)
{
	if (data_valid == 1){
	Location.lat_deg = (location[0] - '0') * 10 + (location[1] - '0');
	Location.lat_min_int = (location[2] - '0') * 10 + (location[3] - '0'); 
	Location.lat_min_frac = (location[5] - '0') * 10000 + (location[6] - '0') * 1000 + (location[7] - '0') * 100 + (location[8] - '0') * 10 + (location[9] - '0');
	Location.uLat = location[10];
	
	Location.lon_deg = (location[11] - '0') * 100 + (location[12] - '0') * 10 + (location[13] - '0');
	Location.lon_min_int = (location[14] - '0') * 10 + (location[15] - '0'); 
	Location.lon_min_frac = (location[17] - '0') * 10000 + (location[18] - '0') * 1000 + (location[19] - '0') * 100 + (location[20] - '0') * 10 + (location[21] - '0');
	Location.uLon = location[22];
	}
	return Location;
}
