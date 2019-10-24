#pragma once 

#include <cstdint>

#include "lib/expected.h"

void init_i2c( void );
void init_relay_switch( void );
util::Expected<uint32_t> i2c_read_sensor_value( void );
void relay_switch( int32_t );
