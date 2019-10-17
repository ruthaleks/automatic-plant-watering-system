#include <cstdint>
#include <iostream>

#include "devices.hpp"
#include "sensor.hpp"

Sensor::Sensor( SensorType type) : m_type{ type }{
    read_sensor_value = init_read_func( type );
}

int32_t Sensor::value() const 
{
    if (read_sensor_value != nullptr)
    {
        return read_sensor_value();
    } else {
        std::cout << "No sensor connected\n";
        return 0; 
    } 

}

SensorType Sensor::type() const
{
    return m_type;
}

uint32_t Sensor::threashold() const
{
    return m_threashold_value;
}
