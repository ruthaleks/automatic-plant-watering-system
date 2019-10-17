/*
* This file is only included when building for Raspberry Pi. 
* The wiringPi library support only 32-bit Raspbian and 
* no other platform. 
*/
#include <cstdint>
#include <iostream>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "parameters.hpp"
#include "devices.hpp"


int16_t swap_endianess( int16_t data )
{
    uint8_t b_low = (data & 0xff);
    uint8_t b_high = ((data & 0xff00) >> 8); 
    return ((b_low << 8) | b_high); 
}


int32_t i2c_read_sensor_value()
{
    wiringPiSetup();
    int32_t fd = wiringPiI2CSetup( DEVICE_ADDRESS );

    wiringPiI2CWriteReg8( fd, BASE, CHANNEL_OFFSET );
    delay(10);
    int16_t raw_data = wiringPiI2CReadReg16( fd, 0x00 ); 

    return swap_endianess( raw_data );    
}

void relay_switch( int32_t on )
{
    wiringPiSetup();
    pinMode(PIN, OUTPUT);
    if (on > 0){
        digitalWrite(PIN, HIGH);
    } else {
        digitalWrite(PIN, LOW);
    }
}
