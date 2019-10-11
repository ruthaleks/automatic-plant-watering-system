#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "main.hpp"
#include "control.hpp"
#include "errorCodes.hpp"
#include "unitTest.hpp"


/* Defines */
#define UNIT_TEST

/* Globals */ 
uint32_t id_counter{ 1 };

/* Class definitions */
Tank::Tank( SensorID load_sensor, ActuatorID pump) : 
    m_load_sensor_id{ load_sensor }, m_pump_id{ pump }, ID{ id_counter } 
    { 
        id_counter++; 
    }

uint32_t Tank::get_level()
{
    m_water_level = get_sensor_value( m_load_sensor_id );
    std::cout << "Read the pressure sensor data..\n";
    return m_water_level; 
}

// send an email or power up a led 
int32_t Tank::low_water_level() 
{
    std::cout << "Low water level in the tank";
    return 0;
}

SensorID Tank::get_sensor(){ return m_load_sensor_id; } 
ActuatorID Tank::get_actuator(){ return m_pump_id; }

Pot::Pot( SensorID moist_sensor) :  
    m_moist_sensor_id{ moist_sensor}, ID{ id_counter }
    { 
        id_counter++; 
    }

int32_t Pot::connect_to_tank( Tank *t_p_tank )
{   
    if ( t_p_tank != nullptr )
    {
        m_p_tank = t_p_tank;
        return NO_ERROR;
    }
    return NULL_POINTER_ERROR;
}

uint32_t Pot::get_tank_id()
{
    if(m_p_tank != nullptr )
    {
        return m_p_tank->ID; 
    }
    return 0;
}

int32_t Pot::get_humidity() 
{
    std::cout << "Read data from humidity sensor..\n";   
    m_humidity = get_sensor_value( m_moist_sensor_id );
    return m_humidity;      
}

int32_t Pot::add_water()
{
    std::cout << "Adding water to the plant..\n";
    set_actuator( m_p_tank->get_actuator(), 1 );
    set_actuator( m_p_tank->get_actuator(), 0 );
    return 0;
}

SensorID Pot::get_sensor(){ return m_moist_sensor_id; }

int32_t main()
{
#ifdef UNIT_TEST
    test();
#endif 
    std::cout << "** Start of main **\n";
    Tank tank{ SIM_LoadSensor, SIM_Pump }; 
    std::cout << "Created a new water tank with ID: " << tank.ID << '\n';    
    Pot pot{ SIM_MoistSensor };
    std::cout << "Created a new flower pot with ID: " << pot.ID << '\n';

    if (pot.connect_to_tank( &tank ) == NO_ERROR)
    {    
        std::cout << "Connected pot with ID: " << pot.ID 
        << " with tank ID: " << pot.get_tank_id() << '\n';
    } else {
        std::cout << "Failed to connect the pot\n";
    }

    control_routine(pot, tank);



    return 0;
}