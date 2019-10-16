#include <cstdint>
#include <iostream>

#include "devices.hpp"
#include "sensor.hpp"

Sensor::Sensor( SensorType type) : m_type{ type }{}

int32_t Sensor::value() const 
{
    return read_sensor_value( );
}

SensorType Sensor::type() const
{
    return m_type;
}

uint32_t Sensor::threashold() const
{
    return m_threashold_value;
}
