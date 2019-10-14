#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "pot.hpp"


Pot::Pot( SensorID moist_sensor) : m_moist_sensor{ moist_sensor }{}

int32_t Pot::humidity() const 
{
    std::cout << "Read data from humidity sensor..\n";   
    //m_humidity = get_sensor_value( m_moist_sensorid );
    return 1;
}

SensorID Pot::sensor() const
{ 
    return m_moist_sensor; 
}

