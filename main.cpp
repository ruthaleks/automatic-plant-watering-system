#include <iostream>
#include <cstdint>

#include "main.hpp"
#include "errorCodes.hpp"
#include "unitTest.hpp"

/* Defines */
#define UNIT_TEST

/* Globals */ 
uint32_t id_counter{ 1 };

/* Class definitions */
Tank::Tank() : ID(id_counter){ id_counter++; }

int32_t Tank::get_level()
{
    m_water_level = 1;
    std::cout << "Read the pressure sensor data..";
    return m_water_level; 
}

// send an email or power up a led 
int32_t Tank::low_water_level() 
{
    std::cout << "Low water level in the tank";
    return 0;
}


Pot::Pot() : ID( id_counter ){ id_counter++; }

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
    m_humidity = 1;
    std::cout << "Read data from humidity sensor..\n";   
    return m_humidity;      
}

int32_t Pot::add_water()
{
    std::cout << "Adding water to the plant..\n";
    return 0;
}

#define WET_SOIL_THRESHOLD_VALUE 10 // a value that is >= than threshold is wet
#define DRY_SOIL_THRESHOLD_VALUE 5  // a value that is <= than threshold is dry

uint32_t check_if_sensor_value_is_valid( uint32_t value )
{
    return value;
}

int32_t control_routine(Pot pot)
{   
    std::cout << "Start of control routine\n";
    
    std::cout << "Check the soil humidity\n"; 
    uint32_t current_humidity = pot.get_humidity();
    std::cout << "Current humidity: " 
    << current_humidity << '\n';

    check_if_sensor_value_is_valid( current_humidity );
    
/*
    if (current_humidity <= DRY_SOIL_THRESHOLD_VALUE ){
        std::cout << "The soil is dry.\n";
        pot.add_water()
    } else if (current_humidity >){}
*/
    return 0;
}


int32_t main()
{
#ifdef UNIT_TEST
    test();
#endif 
    std::cout << "** Start of main **\n";
    Tank tank{}; 
    std::cout << "Created a new water tank with ID: " << tank.ID << '\n';    
    Pot pot{};
    std::cout << "Created a new flower pot with ID: " << pot.ID << '\n';

    if (pot.connect_to_tank( &tank ) == NO_ERROR)
    {    
        std::cout << "Connected pot with ID: " << pot.ID 
        << " with tank ID: " << pot.get_tank_id() << '\n';
    } else {
        std::cout << "Failed to connect the pot\n";
    }

    control_routine(pot);



    return 0;
}