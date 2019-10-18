#include <memory>
#include <iostream>
#include <cstdint>

#include "devices.hpp"
#include "sensorMonitor.hpp"
#include "actuatorController.hpp"
#include "tankManager.hpp"
#include "parameters.hpp"
#include "potManager.hpp"
#include "control.hpp"

int32_t main() 
{
    std::cout << "** Start of main **\n";
    TankManager tank{ SensorType::SIM_LoadSensor, ActuatorType::NO_Actuator }; 
    std::cout << "Created a new water tank\n";    
    
    tank.set_flow_rate( FLOW_RATE );
    tank.set_water_amount( WATER_AMOUNT );

    PotManager pot{ SensorType::I2C_Sensor };
    std::cout << "Created a new pot \n";    

    pot.set_treashold( MOIST_TRESHOLD );


    control_routine(pot, tank);



    return 0;
}
