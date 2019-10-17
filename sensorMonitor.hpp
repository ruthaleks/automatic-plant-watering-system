#pragma once

#include "devices.hpp"

class SensorMonitor 
{
    SensorType m_type;
    int32_t (*read_sensor_value)(); // function poiter 

    public:
        SensorMonitor( SensorType );        
        int32_t value() const;
        SensorType type() const;
};