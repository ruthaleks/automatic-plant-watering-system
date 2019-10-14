#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "actuator.hpp"

Actuator::Actuator( ActuatorType type) : m_type{ type }{}

void Actuator::on() const 
{
    std::cout << "Pump on..\n";
}

void Actuator::off() const
{
    std::cout << "Pump off..\n";
}

ActuatorType Actuator::type() const
{
    return m_type;
}