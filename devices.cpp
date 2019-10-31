#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>

#include "lib/colors.hpp"
#include "lib/expected.h"

#include "devices.hpp"
#include "utils.hpp"

#ifdef PI
#include "drivers.hpp"
#endif


util::Expected<uint32_t> sim_read_sensor_value()
{
    std::string s;
    std::ifstream file("sim_input.txt");
    if( file.is_open() ){
        std::getline(file, s);
        file.close();
        s = std::regex_replace(s, std::regex("^ +| +$|( ) +"), "$1"); 
        if( std::regex_match(s, std::regex("[(-|+)|][0-9]+") ))
        { 
            int32_t data{std::stoi( s )};
            if (data < 0){
                return std::invalid_argument("Simulated sensor returned an error.\n" );
            }
            return ( uint32_t ) data;   
        }
    } 
    return std::invalid_argument("Can not open input file.\n");    
}

void sim_swich(int32_t on)
{
    if(on > 0)
    {
        std::cout << "Simumlated pump on..\n";
    } else {
        std::cout << "Simumlated pump off..\n";
    }
}

auto init_control_func( ActuatorType actuator) -> void (*)(int32_t)
{
    void (*control) (int32_t);
    
    switch (actuator)
    {
    case ActuatorType::SIM_Switch:
        control = &sim_swich;
        break;
    case ActuatorType::RELAY_Switch:
    #ifdef PI
        init_relay_switch();
        control = &relay_switch;
    #else
        print::wrn_msg("Using simulated switch function.\n");
        control = &sim_swich;
    #endif
    break;
    case ActuatorType::NO_Actuator:
    default:
        control = nullptr;
        break;
    }
    return control;
}

auto init_read_func( SensorType sensor) -> util::Expected<uint32_t> (*)(void) 
{    
    util::Expected<uint32_t> (*read) ();

    switch (sensor)
    {
    case SensorType::I2C_Sensor:
    #ifdef PI
        init_i2c();
        read = &i2c_read_sensor_value;
    #else
        print::wrn_msg("Using simulated sensor read function.\n");
        read = &sim_read_sensor_value;
    #endif
        break;
    case SensorType::SIM_MoistSensor:
    case SensorType::SIM_LoadSensor:
        read= &sim_read_sensor_value;
        break;
    case SensorType::NO_Sensor:
    default:
        read = nullptr;
        break;
    }
    return read;
}


