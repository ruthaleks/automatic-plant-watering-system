#include <memory>
#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "pot.hpp"


Pot::Pot( SensorType sensor_type) : m_sensor_ptr{ new SensorMonitor{sensor_type} }{}

uint32_t Pot::humidity() const 
{
    std::cout << "Read data from humidity sensor..\n";
    uint32_t v = m_sensor_ptr->value(); 
    std::cout << "Current humidity: " << v << '\n';
    return v;
}

bool Pot::is_dry() const
{   
    if (humidity() < m_sensor_ptr->threashold() ) {  
        return true; // soil is dry
    } 
        return false;
}

SensorType Pot::sensor() const
{
    return m_sensor_ptr->type();
}


