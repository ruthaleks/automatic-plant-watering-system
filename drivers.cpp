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

#include "devices.hpp"
#include "drivers.hpp"
#include "parameters.hpp"
#include "utils.hpp"


i16 swap_endianess( i16 data )
{
    u8 b_low = (data & 0xff);
    u8 b_high = ((data & 0xff00) >> 8); 
    return ((b_low << 8) | b_high); 
}

void init_i2c()
{  
    static I2C i2c{}; 
    bool ok{true};

    Exp_i32 dev_addr{read_param<i32>(Param::i2c_device_address)};
    if(dev_addr.isValid()){
        i2c.dev_addr = dev_addr.get();
    } else {
        ok = false;
        print::error_msg("The I2C device address cannot be set: ");
        std::cout << dev_addr.exceptInfo();
    }

    Exp_i32 base{read_param<i32>(Param::i2c_base)};
    if (base.isValid()){
        i2c.base = base.get();
    } else {
        ok = false;
        print::error_msg("The I2C base cannot be set: ");
        std::cout << base.exceptInfo();
    }
    Exp_i32 offset{read_param<i32>(Param::i2c_channel_offset)};
        
    } else {
        ok = false;
        print::error_msg("Failed  ");
        if(!min.isValid())
            std::cout << min.exceptInfo();
        if(!max.isValid())
            std::cout << max.exceptInfo();
    }
    
    fd = wiringPiI2CSetup( dev_addr.get() );
        i32 res = wiringPiI2CWriteReg8( fd, I2C_BASE, I2C_CHANNEL_OFFSET );
    
}

void init_relay_switch()
{
    static Relay relay{};

    Exp_i32 pin{read_param<i32>(Param::pump_gpio_pin)};
    if(pin.isValid()){
        relay.pin = pin.get();
    } else {
        print::error_msg("The gpio pin for the pump cannot be set: ");
        std::cout << pin.exceptInfo();
        exit(EXIT_FAILURE);
    }

    wiringPiSetup();
    pinMode(relay.pin, OUTPUT);
        
}

Exp_u32 i2c_read_sensor_value( void )
{
    Exp_i32 base{read_param<i32>(Param::i2c_base)};
    Exp_i32 offset{read_param<i32>(Param::i2c_channel_offset)};

    if (base.isValid() && offset.isValid()){
        i32 res = wiringPiI2CWriteReg8( fd, I2C_BASE, I2C_CHANNEL_OFFSET );
    } else {
        print::error_msg("Failed  ");
        if(!min.isValid())
            std::cout << min.exceptInfo();
        if(!max.isValid())
            std::cout << max.exceptInfo();
    }

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
        return std::invalid_argument("Negative sensor value after endianess swap.");
    }
    return ( uint32_t ) data;    
}

void relay_switch( i32 on )
{
    if (on > 0){
        digitalWrite(relay.pin, HIGH);
    } else {
        digitalWrite(relay.pin, LOW);
    }
}
