#pragma once 

#include <cstdint>

int32_t init_i2c( void );
void init_relay_switch( void );
int32_t i2c_read_sensor_value( int32_t );
void relay_switch( int32_t );
