#pragma once
#include <cstdint>

#include "actuatorController.hpp"
#include "devices.hpp"
#include "sensorMonitor.hpp"

class TankManager 
{
    uint32_t m_water_level{}; // remaing water quantity in the tank 
    std::unique_ptr<SensorMonitor> m_sensor_ptr;
    std::unique_ptr<ActuatorController> m_actuator_ptr;

    public: 
        TankManager( SensorType, ActuatorType );        
        SensorType sensor() const;
        ActuatorType actuator() const; 
        uint32_t level() const;   
        void add_water( float ) const;
};