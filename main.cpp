#include "main.hpp"
#include "errorCodes.hpp"
#include "unitTest.hpp"

#include <iostream>

/* Globals */ 
uint32 id_counter{ 1 };

Tank::Tank() : ID(id_counter)
{
    id_counter++;
}

int32 Tank::get_level()
{
    m_water_level = 1;
    std::cout << "Read the pressure sensor data..";
    return m_water_level; 
}

// send an email or power up a led 
int32 Tank::low_water_level() 
{
    std::cout << "Low water level in the tank";
    return 0;
}


Pot::Pot() : ID( id_counter )
{ 
    id_counter++;
}

int32 Pot::connect_to_tank( Tank *t_p_tank )
{   
    if ( t_p_tank != nullptr )
    {
        m_p_tank = t_p_tank;
        return NO_ERROR;
    }
    return NULL_POINTER_ERROR;
}
uint32 Pot::get_tank_id()
{
    if(m_p_tank != nullptr )
    {
        return m_p_tank->ID; 
    }
    return 0;
}

int32 Pot::get_humidity() 
{
    m_humidity = 1;
    std::cout << "Read data from humidity sensor..\n";   
    return m_humidity;      
}

int32 Pot::add_water()
{
    std::cout << "Adding water to the plant..\n";
    return 0;
}

#define UNIT_TEST
int32 main()
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

    return 0;
}