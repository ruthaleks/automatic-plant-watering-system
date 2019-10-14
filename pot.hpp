#pragma once

class Pot
{
    uint32_t m_volume{};     // water volume added to the pot during a certain time period
    SensorType m_sensor_type{};    
    std::unique_ptr<Sensor> m_sensor_ptr{ new Sensor{ m_sensor_type } };

    uint32_t humidity() const;
    public:
        Pot( SensorType );            // constructor
        bool is_dry() const; // returns true if the spoil  in the pot is dry
        SensorType sensor() const; 
};