#include <cstdint>
#include <iostream>

#include "lib/expected.h"

#include "devices.hpp"
#include "sensorMonitor.hpp"


SensorMonitor::SensorMonitor( SensorType type) : m_type{ type }{
    read_sensor_value = init_read_func( type );
}

util::Expected<int32_t> SensorMonitor::value() const 
{
    if (read_sensor_value != nullptr)
    {
        return read_sensor_value();
    } 
    return std::invalid_argument("No sensor connected.\n");
}

SensorType SensorMonitor::type() const
{
    return m_type;
}

