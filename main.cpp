#include <memory>
#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "sensor.hpp"
#include "actuator.hpp"
#include "tank.hpp"
#include "pot.hpp"
#include "control.hpp"

int32_t main()
{
    std::cout << "** Start of main **\n";
    Tank tank{ SensorType::SIM_LoadSensor, ActuatorType::SIM_Switch }; 
    std::cout << "Created a new water tank\n";    
    Pot pot{ SensorType::I2C_Sensor };
    std::cout << "Created a new pot \n";


   control_routine(pot, tank);



    return 0;
}
