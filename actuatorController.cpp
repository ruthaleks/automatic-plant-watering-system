#include <cstdint>
#include <iostream>

#include "actuatorController.hpp"
#include "devices.hpp"

ActuatorController::ActuatorController( ActuatorType type) : m_type{ type }
{
    control_actuator = init_control_func( type );
}

void ActuatorController::set_velocity( int32_t vel ) const
{
    control_actuator( vel );
}

ActuatorType ActuatorController::type() const
{
    return m_type;
}

float ActuatorController::capacity() const
{
    return m_capacity;
}

void ActuatorController::set_capacity( float value )
{
    m_capacity = value;
}