#include <cstdint>
#include <iostream>
#include <memory>

#include "lib/colors.hpp"
#include "lib/print.hpp"

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
    TankManager tank{ SensorType::NO_Sensor, ActuatorType::RELAY_Switch }; 
    print::ok_msg("New tank manager initialized.\n");
    
    tank.set_flow_rate( FLOW_RATE );
    tank.set_water_amount( WATER_AMOUNT );

    PotManager pot{ SensorType::I2C_Sensor };
    print::ok_msg("New pot manager initialized.\n");    

    pot.set_sensor_minmax( MIN_MOIST_READING, MAX_MOIST_READING );
    pot.set_treashold( MOIST_TRESHOLD );
    pot.set_sampling_time( 3 );


    control_routine(pot, tank);

    return 0;
}
