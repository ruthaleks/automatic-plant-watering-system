#include <cstdint>
#include <iostream>

#include "lib/expected.h"

#include "actuatorController.hpp"
#include "devices.hpp"

ActuatorController::ActuatorController( ActuatorType type) : m_type{ type }
{ 
    control_actuator = init_control_func( type );
}

void ActuatorController::ctrl_actuator( int32_t vel ) const 
// pass the input value to the control funtion  
{ 
    control_actuator( vel );
}

// getters
float ActuatorController::capacity() const { return m_capacity; }
ActuatorType ActuatorController::type() const { return m_type; }

// setters
util::Expected<void> ActuatorController::set_capacity( float value )
{
    if ( m_type == ActuatorType::NO_Actuator)
        return std::domain_error("Cannot set the the capacity for selected actuator type\n");

    m_capacity = value;
    return {};
}