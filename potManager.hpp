#pragma once

#include <cstdint>
#include <memory>

#include "lib/expected.h"

#include "devices.hpp"
#include "sensorMonitor.hpp"

class PotManager
{
    uint32_t m_sampling_time{ 1 }; // [s]
    std::unique_ptr<SensorMonitor> m_sensor_ptr{};
    uint32_t m_threashold{ 600 };
    uint32_t m_volume{};     // keep track of how much water was added Not implemmente yet!

    public:
        PotManager( SensorType );            
        bool is_dry( util::Expected<uint32_t> ) const; 
        util::Expected<uint32_t> humidity() const;

        uint32_t sampling_time() const noexcept;
        SensorType sensor() const;
        uint32_t threashold() const;
        
        void set_sampling_time( uint32_t );
        void set_treashold( uint32_t );
};
