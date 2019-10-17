#pragma once

#include "devices.hpp"

class Sensor 
{
    SensorType m_type;
    uint32_t m_threashold_value{ 5 }; // default value
    int32_t (*read_sensor_value)(); // function poiter 

    public:
        Sensor( SensorType );        
        int32_t value() const;
        SensorType type() const;
        uint32_t threashold() const;
};