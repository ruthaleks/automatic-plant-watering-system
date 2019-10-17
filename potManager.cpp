#include <cstdint>
#include <iostream>
#include <memory>

#include "devices.hpp"
#include "potManager.hpp"
#include "sensorMonitor.hpp"


PotManager::PotManager( SensorType sensor_type) : m_sensor_ptr{ new SensorMonitor{sensor_type} }{}

uint32_t PotManager::humidity() const 
{
    std::cout << "Read data from humidity sensor..\n";
    uint32_t v = m_sensor_ptr->value(); 
    std::cout << "Current humidity: " << v << '\n';
    return v;
}

bool PotManager::is_dry() const
{  
    if (m_sensor_ptr->type() == SensorType::NO_Sensor){
        return false;
    }
    
    if (humidity() < m_threashold ) {  
        return true; // soil is dry
    } 
    return false;
}

SensorType PotManager::sensor() const
{
    return m_sensor_ptr->type();
}

void PotManager::set_treashold( uint32_t value)
{
    m_threashold = value;
    std::cout << "The humidity threashold is set to: " << m_threashold << '\n';
}

