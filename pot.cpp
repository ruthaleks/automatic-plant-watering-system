#include <cstdint>
#include <iostream>
#include <memory>

#include "devices.hpp"
#include "pot.hpp"
#include "sensorMonitor.hpp"


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
    if (m_sensor_ptr->type() == SensorType::NO_Sensor){
        return false;
    }
    
    if (humidity() < m_threashold ) {  
        return true; // soil is dry
    } 
    return false;
}

SensorType Pot::sensor() const
{
    return m_sensor_ptr->type();
}

void Pot::set_treashold( uint32_t value)
{
    m_threashold = value;
}

