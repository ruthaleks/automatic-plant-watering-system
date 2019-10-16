/*
* This file is relplaces the file drivers.cpp when building on a 
* when building for a plattform that does not support the wiringPi 
* library.
*/
#include <cstdint>

#include "devices.hpp"

int32_t read_sensor_value( )
{
    return 10;    
}

