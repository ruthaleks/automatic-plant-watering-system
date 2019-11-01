#pragma once 

#include "utils.hpp"

struct I2C {
    i32 fd{};
    i32 dev_addr{};
    i32 base{};
    i32 channel_offset{};
};

struct Relay {
    i32 pin{};    
};

void init_i2c( void );
void init_relay_switch( void );
Exp_u32 i2c_read_sensor_value( void );
void relay_switch( i32 );
