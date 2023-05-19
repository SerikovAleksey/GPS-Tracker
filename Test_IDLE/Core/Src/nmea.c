#include "nmea.h"

uint8_t transmit_buf[5700] = {0};
uint8_t check_data = 0;
uint32_t ind_t = 6;
uint32_t ind_c = 0;

int check_valid_data(uint8_t *nmea_buffer)
{
	uint16_t k = 0;
	uint16_t nmea_indx = 0;
	uint8_t str_indx = 0;
	uint16_t len_str = strlen (string);
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
			if (k < 6) 
			{
				time[k] = nmea_buffer[nmea_indx++];
				k++;
			}
			else nmea_indx++;
		}
		  
		if (nmea_buffer[nmea_indx] == INVALID) 
		{
			data_valid = -1;
			return -1;
		}
		if (nmea_buffer[nmea_indx] == VALID) 
		{
			data_valid = 1;
			return 1;
		}
}
	return 0;
}

int nmea_handler(uint8_t *nmea_buffer, uint8_t type_data) 
{
	uint8_t str_indx = 0;
	uint16_t len_str = strlen (string);
	uint16_t nmea_indx = 0;
	uint8_t amount_comma = 0;
	uint8_t i = 0;
	uint16_t k = 0;
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
			if (k < 6) 
			{
				time[k] = nmea_buffer[nmea_indx++];
				k++;
			}
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
		while (data_valid == 1 && i < 23)
		{
			if (nmea_buffer[++nmea_indx] == ',') nmea_indx++;
			location[i++] = nmea_buffer[nmea_indx];
		}
		
		while (amount_comma < 3)
		{
			if (nmea_buffer[nmea_indx] == ',') amount_comma++;
			nmea_indx++;
		}
		while (k < 12)
		{
			time[k++] = nmea_buffer[nmea_indx++];
		}
		if (data_valid == 1) make_buf(type_data);
	}
	return data_valid; 
} // get_data_from_GPS 



void set_date()
{
	for (uint32_t i = 0; i < sizeof(time) / 2; i++)
	{
		transmit_buf[i] = time[i + sizeof(time) / 2];
	}
} // set_date


void set_time(uint8_t type_data)
{
	transmit_buf[ind_t + ind_c] = type_data;
	for (uint32_t i = 0; i < sizeof(time) / 2; i++)
	{
		transmit_buf[i + 1 + ind_t + ind_c] = time[i];
	}
	ind_t += 7;
} // set_time


void set_coordinates()
{
	transmit_buf[0 + ind_c + ind_t] = location[0];
	transmit_buf[1 + ind_c + ind_t] = location[1];
	transmit_buf[2 + ind_c + ind_t] = location[2];
	transmit_buf[3 + ind_c + ind_t] = location[3];
	transmit_buf[4 + ind_c + ind_t] = location[5];
	transmit_buf[5 + ind_c + ind_t] = location[6];
	transmit_buf[6 + ind_c + ind_t] = location[10];
	
	transmit_buf[7 + ind_c + ind_t] = location[11];
	transmit_buf[8 + ind_c + ind_t] = location[12];
	transmit_buf[9 + ind_c + ind_t] = location[13];
	transmit_buf[10 + ind_c + ind_t] = location[14];
	transmit_buf[11 + ind_c + ind_t] = location[15];
	transmit_buf[12 + ind_c + ind_t] = location[17];
	transmit_buf[13 + ind_c + ind_t] = location[18];
	transmit_buf[14 + ind_c + ind_t] = location[22];

	ind_c += 15;
} //set_coordinates


void make_buf(uint8_t type_data)
{
	if (ind_t == 0)
	{
		set_time(type_data);
		set_coordinates();
	}
	if (ind_t == 6) 
	{
		set_date();
		set_time(type_data);
		set_coordinates();
	}
	else
	{
		if (((transmit_buf[5 + ind_t + (ind_c - 15)] != location[6]) || (transmit_buf[13 + ind_t + (ind_c - 15)] != location[18])) && type_data == AVERAGE)
		{
		set_time(type_data);
		set_coordinates();
		}
		if (type_data == SPECIAL) 
		{
			set_time(type_data);
			set_coordinates();
		}
	}
} // make_buf


void transmit_data(uint8_t *buf, uint16_t len)
{
	uint16_t integer = len / 98;
	uint16_t floatt = len % 98;
	for(uint16_t i = 0; i < integer; i ++)
	{
		HAL_UART_Transmit(&huart2, &buf[98 * i], len, 100);
	}
	HAL_UART_Transmit(&huart2, &buf[98 * integer], floatt, 100);
} // transmit_data


BUF get_transmit_buf()
{
	BUF buf;
  buf.buf = transmit_buf;
	buf.size = ind_c + ind_t;
	return buf;
} // get_transmit_buf

void set_ind_t(uint32_t num)
{
	ind_t = num;
}
void set_ind_c(uint32_t num)
{
	ind_c = num;
}

