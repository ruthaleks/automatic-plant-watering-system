#include <cstdint>
#include <iostream>

#include "actuatorController.hpp"
#include "devices.hpp"

ActuatorController::ActuatorController( ActuatorType type) : m_type{ type }{}

void ActuatorController::on() const 
{
    std::cout << "Pump on..\n";
}

void ActuatorController::off() const
{
    std::cout << "Pump off..\n";
}

ActuatorType ActuatorController::type() const
{
    return m_type;
}

float ActuatorController::rate_per_second() const
{
    return m_rate_per_second;
}
