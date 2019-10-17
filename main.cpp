#include <memory>
#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "actuatorController.hpp"
#include "tankManager.hpp"
#include "potManager.hpp"
#include "control.hpp"

int32_t main()
{
    std::cout << "** Start of main **\n";
    TankManager tank{ SensorType::SIM_LoadSensor, ActuatorType::SIM_Switch }; 
    std::cout << "Created a new water tank\n";    
    PotManager pot{ SensorType::I2C_Sensor };
    std::cout << "Created a new pot \n";


   control_routine(pot, tank);



    return 0;
}
