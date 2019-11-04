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

struct I2CData i2cdata;
struct RelayData relaydata;


i16 swap_endianess( i16 data )
{
    u8 b_low = (data & 0xff);
    u8 b_high = ((data & 0xff00) >> 8); 
    return ((b_low << 8) | b_high); 
}


void init_i2c()
{   

    bool err{false};

    Exp_i32 dev_addr{read_param<i32>(Param::i2c_device_address)};
    if(!dev_addr.isValid()){
        err = true;
        print::error_msg("The I2C device address cannot be set: ");
        std::cout << dev_addr.exceptInfo();
    }

    Exp_i32 base{read_param<i32>(Param::i2c_base)};
    if (!base.isValid()){
        err = true;
        print::error_msg("The I2C base cannot be set: ");
        std::cout << base.exceptInfo();
    }

    Exp_i32 offset{read_param<i32>(Param::i2c_channel_offset)};
    if (!offset.isValid()){
        err = true;
        print::error_msg("The I2C channel offset cannot be set:  ");
        std::cout << offset.exceptInfo();
    }

    if(err){ // abort operation in case of an error 
        exit(EXIT_FAILURE);
    }
    
    // setup of Wiring Pi
    i32 fd = wiringPiI2CSetup( dev_addr.get() );
    if (fd < 0){
        print::error_msg("WiringPi I2C Setup returned an error.\n");
        exit(EXIT_FAILURE);
    }

    i2cdata.fd = fd; 
    i2cdata.dev_addr = dev_addr.get();
    i2cdata.channel_offset = offset.get();
    i2cdata.base = base.get();    
}

void init_relay_switch()
{

    Exp_u32 pin{read_param<u32>(Param::pump_gpio_pin)};
    if(!pin.isValid()){
        print::error_msg("The GPIO pin for the pump cannot be set: ");
        std::cout << pin.exceptInfo();
        exit(EXIT_FAILURE);
    }

    relaydata.pin = pin.get();

    wiringPiSetup();
    pinMode(relay.pin, OUTPUT);        
}

Exp_u32 i2c_read_sensor_value( void )
{    
    wiringPiI2CWriteReg8( i2cdata.fd, i2cdata.base, i2cdara.channel_offset );
    delay(10); 
    i32 raw_data{ wiringPiI2CReadReg16( i2cdata.fd, 0x00 ) }; // it does not matter what address we read from

    if (raw_data < 0)
        return std::invalid_argument( "WiringPi ReadReg16 returned an error.\n"); 

    // swap from little to big endian 
    i32 data { swap_endianess( raw_data ) };

    if (data < 0) 
        return std::invalid_argument("Negative sensor value after endianess swap.\n");
    
    return static_cast<u32>(data);    
}

void relay_switch( i32 on )
{
    if (on > 0){
        digitalWrite(relaydata.pin, HIGH);
    } else {
        digitalWrite(relaydata.pin, LOW);
    }
}
