#pragma once

#include "devices.hpp"

class ActuatorController
{
    ActuatorType m_type;
    float m_rate_per_second{ 10 }; // default value [mm/s]

    public:
        ActuatorController( ActuatorType );
        void on() const;
        void off() const;
        ActuatorType type() const;
        float rate_per_second() const;
};