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
    uint32_t m_threashold{ 0 };
    uint32_t m_max{ 0 }; // max allowed sensor value  
    uint32_t m_min{ 0 }; // min allowed sensor value 
    bool m_minmax_is_set{ false }; // is set true when min and max are set
    uint32_t m_volume{};     // keep track of how much water was added Not implemmente yet!

    public:
        PotManager( SensorType );            
        bool is_dry( uint32_t ) const; 
        util::Expected<uint32_t> humidity() const;

        uint32_t max() const noexcept;
        uint32_t min() const noexcept;
        uint32_t sampling_time() const noexcept;
        SensorType sensor() const;
        uint32_t threashold() const;
        
        void set_sensor_minmax( uint32_t min, uint32_t max );
        void set_sampling_time( uint32_t );
        void set_treashold( uint32_t );
};
