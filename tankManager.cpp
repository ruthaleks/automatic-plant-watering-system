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
#include "utils.hpp"

TankManager::TankManager( SensorType sensor_type, ActuatorType actuator_type ) :
m_sensor_ptr{ new SensorMonitor{ sensor_type } }, 
m_actuator_ptr{ new ActuatorController{ actuator_type } } {}

uint32_t TankManager::add_water() const
// turns on the pump for a time (return value) in ms 
{
    if( m_actuator_ptr->type() == ActuatorType::NO_Actuator)
    {
        #ifdef DEBUG 
        print::wrn_msg( "Cannot add water with the selected actuator type\n");
        #endif
        return 0;
    }
    
    #ifdef DEBUG
    std::cout << "Amount of water poured: " << m_water_amount << "ml\n";
    #endif

    float time{ ((float) m_water_amount / m_actuator_ptr->capacity()) };
    uint32_t millisec = (uint32_t) ( time * 1000.0f );
    
    #ifdef DEBUG
    std::cout << "Pour for " << millisec << " ms \n"; 
    #endif

    m_actuator_ptr->ctrl_actuator( 1 );
    std::this_thread::sleep_for( std::chrono::milliseconds( millisec) );
    m_actuator_ptr->ctrl_actuator( 0 );     

    return millisec; 
}

// Getters
ActuatorType TankManager::actuator() const { return m_actuator_ptr->type();}
float TankManager::flow_rate() const {return m_actuator_ptr->capacity();}
util::Expected<uint32_t> TankManager::level() const{ return m_sensor_ptr->value();}
SensorType TankManager::sensor() const { return m_sensor_ptr->type() ; }
uint32_t TankManager::water_amount() const { return m_water_amount; }

// Setters 
void TankManager::set_flow_rate( int32_t value ) const
// converts the input flow from L/h to ml/s and sets the capacity of the actuator
{   
    float cap = (float) value * (1000.0f/3600.0f); 
    util::Expected<void> res{ m_actuator_ptr->set_capacity( cap ) };
    if (!res.isValid()){
        print::wrn_msg( res.exceptInfo() );
    } else {
        print::ok_msg( "The flow rate is set to: ");
        std::cout << cap << "mL/s\n";
    }
}

void TankManager::set_water_amount(uint32_t value)
// when the plant is dry a water amount (specified by the input) is poured in to the plant
{
    if ( m_actuator_ptr->type() == ActuatorType::NO_Actuator ){
        print::wrn_msg( "Cannot set the water amount for selected actuator type\n" );
    } else {
        print::ok_msg( "The water amount is set to: ");
        std::cout << value << "ml\n";
        m_water_amount = value;
    }
}
