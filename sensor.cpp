#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "sensor.hpp"

Sensor::Sensor( SensorType type) : m_type{ type }{}

int32_t Sensor::value() const 
{
    return 1;
}

SensorType Sensor::type() const
{
    return m_type;
}