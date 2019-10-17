#pragma once

#include <cstdint>

#include "devices.hpp"

class ActuatorController
{
    ActuatorType m_type;
    float m_capacity{ 10.0 }; // e.g [ ml/s ]
    void (*control_actuator) ( int32_t ); // function pointer

    public:
        ActuatorController( ActuatorType );
        void set_velocity( int32_t ) const;
        ActuatorType type() const;
        float capacity() const;
        void set_capacity( float );
};