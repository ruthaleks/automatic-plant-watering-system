#pragma once

#include <cstdint>

#include "lib/expected.h"

#include "devices.hpp"

class ActuatorController
{
    ActuatorType m_type;
    float m_capacity{ 0.0 }; 
    void (*control_actuator) ( int32_t ); 

    public:
        ActuatorController( ActuatorType );
        void ctrl_actuator( int32_t ) const;
        
        float capacity() const;
        ActuatorType type() const;

        util::Expected<void> set_capacity( float );
};