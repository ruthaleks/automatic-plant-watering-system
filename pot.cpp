#include <memory>
#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "sensor.hpp"
#include "pot.hpp"


Pot::Pot( SensorType sensor_type) : m_sensor_type{ sensor_type }{}

uint32_t Pot::humidity() const 
{
    std::cout << "Read data from humidity sensor..\n";   
    return m_sensor_ptr->value();
}


