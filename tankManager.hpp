#pragma once
#include <cstdint>

#include "actuatorController.hpp"
#include "devices.hpp"
#include "sensorMonitor.hpp"

class TankManager 
{
    uint32_t m_water_level{}; // remaing water quantity in the tank
    uint32_t m_water_amount{ 100 }; // [ ml ] water amount poured during 'add_water'
    std::unique_ptr<SensorMonitor> m_sensor_ptr;
    std::unique_ptr<ActuatorController> m_actuator_ptr;

    public: 
        TankManager( SensorType, ActuatorType );        
        SensorType sensor() const;
        ActuatorType actuator() const; 
        uint32_t level() const;   
        void add_water() const;
        void set_flow_rate( int32_t ) const;
        void set_water_amount( int32_t  );
};