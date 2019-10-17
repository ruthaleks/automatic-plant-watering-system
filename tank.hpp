#pragma once
#include <cstdint>

#include "actuatorController.hpp"
#include "devices.hpp"
#include "sensorMonitor.hpp"

class Tank 
{
    uint32_t m_water_level{}; // remaing water quantity in the tank 
    SensorType m_sensor_type{};
    ActuatorType m_actuator_type{};
    std::unique_ptr<SensorMonitor> m_sensor_ptr{ new SensorMonitor{ m_sensor_type } };
    std::unique_ptr<ActuatorController> m_actuator_ptr{ new ActuatorController{ m_actuator_type } };

    public: 
        Tank( SensorType, ActuatorType );        // constructor
        uint32_t level() const;   
        SensorType sensor() const;
        ActuatorType actuator() const;
        void add_water( float ) const;
};