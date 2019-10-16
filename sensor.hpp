#pragma once

#include "devices.hpp"

class Sensor 
{
    SensorType m_type;
    uint32_t m_threashold_value{ 5 }; // default value

    public:
        Sensor( SensorType );        
        int32_t value() const;
        SensorType type() const;
        uint32_t threashold() const;
};