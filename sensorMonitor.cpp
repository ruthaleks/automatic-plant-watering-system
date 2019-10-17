#include <cstdint>
#include <iostream>

#include "devices.hpp"
#include "sensorMonitor.hpp"

SensorMonitor::SensorMonitor( SensorType type) : m_type{ type }{
    read_sensor_value = init_read_func( type );
}

int32_t SensorMonitor::value() const 
{
    if (read_sensor_value != nullptr)
    {
        return read_sensor_value();
    } else {
        std::cout << "No sensor connected\n";
        return 0; 
    } 

}

SensorType SensorMonitor::type() const
{
    return m_type;
}

