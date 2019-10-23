#include <chrono>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iostream>
#include <memory>
#include <thread>

#include "lib/expected.h"

#include "actuatorController.hpp"
#include "devices.hpp"
#include "parameters.hpp"
#include "potManager.hpp"
#include "sensorMonitor.hpp"
#include "tankManager.hpp"


#define NO_ERROR 0
// TODO: Fix error handling
int32_t control_routine(PotManager& pot, TankManager& tank)
{   
    std::cout << " ***Start of control routine ***\n";
    
    int32_t err = NO_ERROR;
    while( !err )
    {
    #ifdef DEBUG
        std::cout << "Check if the soil is dry \n"; 
    #endif
        util::Expected<int32_t> current_humidity = pot.humidity();
        if (pot.is_dry( current_humidity )){
            #ifdef DEBUG
            std::cout << "Soil is dry, need to add water \n";
            #endif
            tank.add_water();
        }
        int32_t t = CONTROL_PERIOD * 60;
        #ifdef DEBUG
        std::cout << "Wait for " << t << "s\n";
        #endif
        err = 1;
        //std::this_thread::sleep_for(std::chrono::seconds( t ));
    }
    return 0;
}

void write_to_file( float data ) 
{
    #ifdef DEBUG
    std::cout << "Writing data to file\n";
    #endif
    // Get the time stamp in the correct format
    auto time =  std::chrono::system_clock::to_time_t( 
        std::chrono::system_clock::now());
    auto time_stamp = std::ctime( &time );
    char *t = std::strtok(time_stamp, "\n");
    
    std::ofstream file;
    file.open( "data.txt", std::fstream::app );
    file << t << " Humidity: " << data << '\n';
    file.close();
}


