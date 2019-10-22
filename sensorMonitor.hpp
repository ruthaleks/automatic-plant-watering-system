#pragma once

#include "lib/expected.h"

#include "devices.hpp"

class SensorMonitor 
{
    SensorType m_type;
    util::Expected<int32_t> (*read_sensor_value)(); // function poiter 

    public:
        SensorMonitor( SensorType );        
        util::Expected<int32_t> value() const;
        SensorType type() const;
};