#pragma once

#include <cstdint>
#include <memory>

#include "devices.hpp"
#include "sensorMonitor.hpp"

class PotManager
{
    uint32_t m_volume{};     // water volume added to the pot during a certain time period
    uint32_t m_threashold{ 600 };
    uint32_t m_sample_period{ 1 };  // [ s ]
    uint32_t m_sample_number{ 3 }; 
    std::unique_ptr<SensorMonitor> m_sensor_ptr;

    void write_to_file( float ) const; 
    public:
        PotManager( SensorType );            // constructor
        uint32_t humidity() const;
        bool is_dry() const; // returns true if the spoil  in the pot is dry
        SensorType sensor() const;
        void set_treashold( uint32_t );
};