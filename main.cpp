#include <cstdint>
#include <iostream>
#include <memory>

#include "lib/colors.hpp"

#include "actuatorController.hpp"
#include "control.hpp"
#include "devices.hpp"
#include "parameters.hpp"
#include "potManager.hpp"
#include "sensorMonitor.hpp"
#include "tankManager.hpp"

int32_t main() 
{
    std::cout << BOLD("** Program starts **\n");
    TankManager tank{ SensorType::SIM_LoadSensor, ActuatorType::NO_Actuator }; 
    std::cout << FGRN("New tank manager initialized.\n");    
    
    tank.set_flow_rate( FLOW_RATE );
    tank.set_water_amount( WATER_AMOUNT );

    PotManager pot{ SensorType::I2C_Sensor };
    std::cout << FGRN("New pot manager initialized. \n");    

    pot.set_treashold( MOIST_TRESHOLD );
    pot.set_sampling_time( 3 );


    control_routine(pot, tank);



    return 0;
}
