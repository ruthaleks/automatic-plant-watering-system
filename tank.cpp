#include <iostream>

#include "devices.hpp"
#include "tank.hpp"

Tank::Tank( SensorID load_sensor, ActuatorID pump) : 
    m_load_sensor{ load_sensor }, m_pump{ pump }{}

uint32_t Tank::level() const
{
    //m_water_level = get_sensor_value( m_load_sensor_id );
    std::cout << "Read the pressure sensor data..\n";
    return 1; 
}

SensorID Tank::sensor() const
{ 
    return m_load_sensor; 
} 

ActuatorID Tank::actuator() const
{ 
    return m_pump; 
}
