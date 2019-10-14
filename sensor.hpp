#pragma once

class Sensor 
{
    uint32_t m_value{};
    SensorType m_type;

    public:
        Sensor( SensorType );
        uint32_t value() const;
        SensorType type() const;
};