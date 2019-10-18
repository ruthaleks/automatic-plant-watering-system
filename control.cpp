#include <chrono>
#include <cstdint>
#include <memory>
#include <iostream>
#include <thread>

#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "actuatorController.hpp"
#include "parameters.hpp"
#include "potManager.hpp"
#include "tankManager.hpp"


#define NO_ERROR 0
// TODO: Fix error handling
int32_t control_routine(PotManager& pot, TankManager& tank)
{   
    std::cout << " ***Start of control routine ***\n";
    
    int32_t err = NO_ERROR;
    while( !err )
    {
        std::cout << "Check if the soil is dry \n"; 
        if (pot.is_dry()){
            std::cout << "Soil is dry, need to add water \n";
            tank.add_water();
        }
        int32_t t = CONTROL_PERIOD * 60;
        std::cout << "Wait for " << t << "s\n";
        std::this_thread::sleep_for(std::chrono::seconds( t ));
    }
    return 0;
}


