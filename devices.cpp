#include <cstdint>

#include "devices.hpp"

#ifdef PI
#include "drivers.hpp"
#endif


int32_t sim_read_sensor_value( )
{
    return 10;    
}


auto init_read_func( SensorType sensor) -> int32_t (*)(void) 
{    
    int32_t (*read) ();

    switch (sensor)
    {
    case SensorType::I2C_Sensor:
    #ifdef PI
        read = &i2c_read_sensor_value;
    #else
        read = &sim_read_sensor_value;
    #endif
        break;
    case SensorType::SIM_MoistSensor:
    case SensorType::SIM_LoadSensor:
        read= &sim_read_sensor_value;
        break;
    default:
        read = nullptr;
        break;

    }

    return read;
}


