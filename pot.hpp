#pragma once

class Pot
{
    int32_t m_humidity{};   // current humidity of the soil
    uint32_t m_volume{};     // water volume added to the pot during a certain time period
    SensorType m_moist_sensor{};

    public:
        Pot( SensorType );            // constructor
        int32_t humidity() const; 
        SensorType sensor() const;
};