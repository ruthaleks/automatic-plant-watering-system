#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <thread>

#include "lib/expected.h"

#include "actuatorController.hpp"
#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "tankManager.hpp"

TankManager::TankManager( SensorType sensor_type, ActuatorType actuator_type ) :
m_sensor_ptr{ new SensorMonitor{ sensor_type } }, 
m_actuator_ptr{ new ActuatorController{ actuator_type } } {}

void TankManager::add_water() const
{
    if (m_actuator_ptr->type() == ActuatorType::NO_Actuator){
        // TODO: Should be moved out from add water, the pointer to the actuator should handle the case 
        // with no actuator 
        #ifdef DEBUG
        std::cout << "No actuator connected, no water added.. \n";
        #endif
    } else {
        #ifdef DEBUG
        std::cout << "Amount of water poured: " << m_water_amount << "ml\n";
        #endif

        float time{ ((float) m_water_amount / m_actuator_ptr->capacity()) * 1000 };
        m_actuator_ptr->set_velocity( 1 );

        #ifdef DEBUG
        std::cout << "Pour for " << (uint32_t) time << " ms \n"; 
        #endif

        std::this_thread::sleep_for(std::chrono::milliseconds( (uint32_t) time));
        m_actuator_ptr->set_velocity( 0 );     
    }
}
// TODO: Add a method is_empty() and make level() private
// TODO: Add a private variable threshold 

// Getters
ActuatorType TankManager::actuator() const { return m_actuator_ptr->type();}
float TankManager::flow_rate() const {return m_actuator_ptr->capacity();}

util::Expected<uint32_t> TankManager::level() const{ return m_sensor_ptr->value();}

SensorType TankManager::sensor() const { return m_sensor_ptr->type() ; }

// Setters 

void TankManager::set_flow_rate( int32_t value ) const
{   
    float cap = (float) value * (1000.0f/3600.0f); // convert from [ L/h ] to [ mL/s ]
    std::cout << "The flow rate is set to: " << cap << "mL/s\n";
    m_actuator_ptr->set_capacity( cap );
}

void TankManager::set_water_amount(int32_t value)
{
    std::cout << "The water amount is set to: " << value << "ml\n";
    m_water_amount = value;
}
