#pragma once

class Actuator 
{
    ActuatorType m_type;
    float m_rate_per_second{ 10 }; // default value [mm/s]

    public:
        Actuator( ActuatorType );
        void on() const;
        void off() const;
        ActuatorType type() const;
        float rate_per_second() const;
};