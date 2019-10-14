#pragma once

class Actuator 
{
    ActuatorType m_type;

    public:
        Actuator( ActuatorType );
        void on() const;
        void off() const;
        ActuatorType type() const;
};