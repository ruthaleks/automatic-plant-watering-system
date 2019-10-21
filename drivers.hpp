#pragma once 

#include <cstdint>

void init_i2c( void );
void init_relay_switch( void );
int32_t i2c_read_sensor_value( void );
void relay_switch( int32_t );
