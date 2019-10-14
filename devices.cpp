#include <cstdint>
#include <iostream>

#include "devices.hpp"
#include "errorCodes.hpp"

// consider adding class for sensor and actuator 

uint32_t get_sensor_value( SensorType sensor )
{
    switch ( sensor )
    {
    case SIM_MoistSensor:
        return 10;
        break;
    case SIM_LoadSensor:
        return 10;
        break;
    default:
        std::cout << "Unknown Sensor ID";
        return 0;
        break;
    }
}

int32_t set_actuator( ActuatorType actuator, int32_t value )
{
    switch (actuator)
    {
    case SIM_Pump:
        if ( value == 0 ){
            std::cout << "Pump off.. \n";
            return NO_ERROR;
        } else if ( value == 1 ){
            std::cout << "Pump on.. \n";
            return NO_ERROR;
        } else {
            std::cout << " Unvalid value.. \n";
            return VALUE_NOT_VALID;
        }
        break;
    
    default:
        std::cout << "Unknown ActuatorID";
        return UNKNOWN_ID;
        break;
    }
}
