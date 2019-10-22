#include <cstdint>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "actuatorController.hpp"
#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "tankManager.hpp"

TankManager::TankManager( SensorType sensor_type, ActuatorType actuator_type ) :
m_sensor_ptr{ new SensorMonitor{ sensor_type } }, 
m_actuator_ptr{ new ActuatorController{ actuator_type } } {}

// TODO: Add a method is_empty() and make level() private
// TODO: Add a private variable threshold 

uint32_t TankManager::level() const
{   
    std::cout << "Read the pressure sensor data..\n";
    //return m_sensor_ptr->value();
    return 0; 
}

SensorType TankManager::sensor() const
{
    return m_sensor_ptr->type() ;
}

ActuatorType TankManager::actuator() const
{
    return m_actuator_ptr->type();
}

void TankManager::set_flow_rate( int32_t value ) const
{   
    float cap = (float) value * 0.27; // convert from [ L/h ] to [ mL/s ]
    std::cout << "The flow rate is set to: " << cap << "mL/s\n";
    m_actuator_ptr->set_capacity( cap );
}

void TankManager::add_water() const
{
    if (m_actuator_ptr->type() == ActuatorType::NO_Actuator){
        #ifdef DEBUG
        std::cout << "No actuator connected, no water added.. \n";
        #endif
    } else {
        std::cout << "Amount of water poured: " << m_water_amount << "ml\n";
        float time{ ((float) m_water_amount / m_actuator_ptr->capacity()) * 1000 };
        m_actuator_ptr->set_velocity( 1 );
        std::cout << "Pour for " << (uint32_t) time << " ms \n"; 
        std::this_thread::sleep_for(std::chrono::milliseconds( (uint32_t) time));
        m_actuator_ptr->set_velocity( 0 );     
    }
}

void TankManager::set_water_amount(int32_t value)
{
    std::cout << "The water amount is set to: " << value << "ml\n";
    m_water_amount = value;
}