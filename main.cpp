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
#include "utils.hpp"


int32_t main() 
{
    std::cout << BOLD("** Program starts **\n");
    TankManager tank{ SensorType::NO_Sensor, ActuatorType::RELAY_Switch }; 
    print::ok_msg("New tank manager initialized.\n");

    PotManager pot{ SensorType::I2C_Sensor };
    print::ok_msg("New pot manager initialized.\n");    

    set_params(tank, pot);

    control_routine(pot, tank);

    return 0;
}
