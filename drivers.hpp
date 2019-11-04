#pragma once 

#include "utils.hpp"

struct I2CData{
    const i32 fd;
    const i32 dev_addr;
    const i32 base;
    const i32 channel_offset;
};

struct RelayData{
    const u32 pin;    
};

void init_i2c( void );
void init_relay_switch( void );
Exp_u32 i2c_read_sensor_value( void );
void relay_switch( i32 );
