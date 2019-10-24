/*
* This file is only included when building for Raspberry Pi. 
* The wiringPi library support only 32-bit Raspbian and 
* no other platform. 
*/
#include <cstdint>
#include <errno.h>
#include <iostream>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "lib/expected.h"

#include "parameters.hpp"
#include "devices.hpp"

static int32_t fd;

int16_t swap_endianess( int16_t data )
{
    uint8_t b_low = (data & 0xff);
    uint8_t b_high = ((data & 0xff00) >> 8); 
    return ((b_low << 8) | b_high); 
}

void init_i2c()
{
    fd =  wiringPiI2CSetup( I2C_DEVICE_ADDRESS );
}

void init_relay_switch()
{
    wiringPiSetup();
    pinMode( PIN, OUTPUT );
}

util::Expected<uint32_t> i2c_read_sensor_value( void )
{
    wiringPiI2CWriteReg8( fd, I2C_BASE, I2C_CHANNEL_OFFSET );
    delay(10);
    int32_t raw_data{ wiringPiI2CReadReg16( fd, 0x00 ) };

    // if raw_data is negative number then an error has happend
    if (raw_data < 0)
    {  
        std::string errmsg{ "WiringPi returned an error with errno = "};
        errmsg.append( std::to_string( errno ) );
        return std::invalid_argument( errmsg ); 
    }

    int32_t data = swap_endianess( raw_data );
   
    if (data < 0) {
        return std::invalid_argument("Negative sensor value after endianess swap.")
    }
    return ( uint32_t ) data;    
}

void relay_switch( int32_t on )
{
    if (on > 0){
        digitalWrite(PIN, HIGH);
    } else {
        digitalWrite(PIN, LOW);
    }
}
