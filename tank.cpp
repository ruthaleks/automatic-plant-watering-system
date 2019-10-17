#include <memory>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <thread>

#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "actuatorController.hpp"
#include "tank.hpp"

Tank::Tank( SensorType sensor_type, ActuatorType actuator_type ) : 
m_sensor_type{ sensor_type }, m_actuator_type{ actuator_type }{}

// TODO: Add a method is_empty() and make level() private
// TODO: Add a private variable threshold 

uint32_t Tank::level() const
{   
    // TODO: Add a guard in case no sensor
    std::cout << "Read the pressure sensor data..\n";
    return m_sensor_ptr->value(); 
}

SensorType Tank::sensor() const
{
    return m_sensor_type;
}

ActuatorType Tank::actuator() const
{
    return m_actuator_type;
}

void Tank::add_water(float amout_in_millilitre) const
{
    // TODO: Add a guard in case no actuator
    std::cout << "Asked amount: " << amout_in_millilitre << " millilitres\n";
    float time{ amout_in_millilitre / m_actuator_ptr->rate_per_second() };
    m_actuator_ptr->on();
    std::cout << "Pour for " << (uint32_t) time << " second(s) \n"; 
    std::this_thread::sleep_for(std::chrono::seconds((uint32_t)time));
    m_actuator_ptr->off(); 
    
}
