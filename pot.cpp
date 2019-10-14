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

bool Pot::is_dry() const
{   
    if (m_sensor_type != SensorType::NO_Sensor){
        if (humidity() < m_sensor_ptr->threashold() ) {  
            return true; // soil is dry
        } else {
            return false;
        }
    } else {
        std::cout << "No humidity sensor connected \n";
        return false;
    }
}

SensorType Pot::sensor() const
{
    return m_sensor_type;
}


