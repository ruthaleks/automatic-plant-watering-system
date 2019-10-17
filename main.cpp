#include <memory>
#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "actuator.hpp"
#include "tank.hpp"
#include "pot.hpp"
#include "control.hpp"

int32_t main()
{
    std::cout << "** Start of main **\n";
    Tank tank{ SensorType::SIM_LoadSensor, ActuatorType::SIM_Switch }; 
    std::cout << "Created a new water tank\n";    
    Pot pot{ SensorType::SIM_MoistSensor };
    std::cout << "Created a new pot \n";


   control_routine(pot, tank);



    return 0;
}
