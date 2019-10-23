#pragma once
#include <cstdint>

#include "lib/expected.h"

#include "actuatorController.hpp"
#include "devices.hpp"
#include "sensorMonitor.hpp"

class TankManager 
{
    uint32_t m_water_level{}; // remaing water quantity in the tank
    uint32_t m_water_amount{ 100 }; // [ ml ] water amount poured during 'add_water'
    std::unique_ptr<SensorMonitor> m_sensor_ptr{ nullptr };
    std::unique_ptr<ActuatorController> m_actuator_ptr{ nullptr };

    public: 
        TankManager( SensorType, ActuatorType );        
        void add_water() const;
        
        ActuatorType actuator() const; 
        float flow_rate() const;
        util::Expected<uint32_t> level() const;   
        SensorType sensor() const;
        
        void set_flow_rate( int32_t ) const;
        void set_water_amount( int32_t  );
};