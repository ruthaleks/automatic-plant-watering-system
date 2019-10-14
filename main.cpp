#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "tank.hpp"
#include "pot.hpp"
#include "control.hpp"

int32_t main()
{
    std::cout << "** Start of main **\n";
    Tank tank{ SIM_LoadSensor, SIM_Pump }; 
    std::cout << "Created a new water tank\n";    
    Pot pot{ SIM_MoistSensor };
    std::cout << "Created a new pot \n";


//    control_routine(pot, tank);



    return 0;
}
