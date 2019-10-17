#pragma once

#include <cstdint>
#include <memory>

#include "devices.hpp"
#include "sensorMonitor.hpp"

class Pot
{
    uint32_t m_volume{};     // water volume added to the pot during a certain time period
    std::unique_ptr<SensorMonitor> m_sensor_ptr;

    uint32_t humidity() const;
    public:
        Pot( SensorType );            // constructor
        bool is_dry() const; // returns true if the spoil  in the pot is dry
        SensorType sensor() const; 
};