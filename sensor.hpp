#pragma once

class Sensor 
{
    int32_t m_value{};
    SensorType m_type;

    public:
        Sensor( SensorType );
        int32_t value() const;
        SensorType type() const;
};