#pragma once

#include <cstdint>

#include "devices.hpp"

class ActuatorController
{
    ActuatorType m_type;
    float m_rate_per_second{ 10 }; // default value [mm/s]
    void (*control_actuator) ( int32_t ); // function pointer

    public:
        ActuatorController( ActuatorType );
        void set_velocity( int32_t ) const;
        ActuatorType type() const;
        float rate_per_second() const;
};