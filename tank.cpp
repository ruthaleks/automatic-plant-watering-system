#include <memory>
#include <iostream>

#include "devices.hpp"
#include "sensor.hpp"
#include "actuator.hpp"
#include "tank.hpp"

Tank::Tank( SensorType sensor_type, ActuatorType actuator_type ) : 
m_sensor_type{ sensor_type }, m_actuator_type{ actuator_type }{}

uint32_t Tank::level() const
{
    std::cout << "Read the pressure sensor data..\n";
    return m_sensor_ptr->value(); 
}

