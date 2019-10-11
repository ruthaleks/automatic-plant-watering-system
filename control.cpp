#include <cstdint>
#include <iostream>

#include "devices.hpp"
#include "main.hpp"

uint32_t check_if_sensor_value_is_valid( uint32_t value )
{
    return value;
}


int32_t control_routine(Pot pot, Tank tank)
{   
    std::cout << "Start of control routine\n";
    
    std::cout << "Check the soil humidity\n"; 
    uint32_t current_humidity = pot.get_humidity();
    std::cout << "Current humidity: " 
    << current_humidity << '\n';

    check_if_sensor_value_is_valid( current_humidity );

    pot.add_water();

// check water tank levels in all the tanks
    std::cout << "Check the water tank level.\n";
    uint32_t current_level = tank.get_level();
    std::cout << "Current water level: " << current_level << '\n';

    return 0;
}


