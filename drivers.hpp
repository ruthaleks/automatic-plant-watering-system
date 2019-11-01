#pragma once 

#include "utils.hpp"


void init_i2c( void );
void init_relay_switch( void );
Exp_u32 i2c_read_sensor_value( void );
void relay_switch( i32 );
