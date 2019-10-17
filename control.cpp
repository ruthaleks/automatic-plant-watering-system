#include <memory>
#include <cstdint>
#include <iostream>

#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "actuatorController.hpp"
#include "potManager.hpp"
#include "tankManager.hpp"


int32_t control_routine(PotManager& pot, TankManager& tank)
{   
    std::cout << "Start of control routine\n";
    
    std::cout << "Check if the soil is dry \n"; 
    if (pot.is_dry()){
        std::cout << "Soil is dry, need to add water \n";
        tank.add_water( 10.0f );
    }


    std::cout << "Check the water tank level.\n";
    uint32_t current_level = tank.level();
    std::cout << "Current water level: " << current_level << '\n';

    return 0;
}


