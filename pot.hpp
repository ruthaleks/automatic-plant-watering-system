#pragma once

class Pot
{
    int32_t m_humidity{};   // current humidity of the soil
    uint32_t m_volume{};     // water volume added to the pot during a certain time period
    SensorType m_sensor_type{};    
    std::unique_ptr<Sensor> m_sensor_ptr{ new Sensor{ m_sensor_type } };


    public:
        Pot( SensorType );            // constructor
        uint32_t humidity() const;
        SensorType sensor() const; 
};