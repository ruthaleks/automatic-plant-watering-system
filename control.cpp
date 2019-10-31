#include <chrono>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iostream>
#include <memory>
#include <thread>

#include "lib/colors.hpp"
#include "lib/expected.h"

#include "actuatorController.hpp"
#include "control.hpp"
#include "devices.hpp"
#include "parameters.hpp"
#include "potManager.hpp"
#include "sensorMonitor.hpp"
#include "tankManager.hpp"
#include "utils.hpp"


int32_t control_routine(PotManager& pot, TankManager& tank)
{   
    std::cout << BOLD( "** Beginning control routine **\n");
    
    const uint32_t t = CONTROL_PERIOD; 
    bool err = false;
    while( !err )
    {
        util::Expected<uint32_t> current_humidity = pot.humidity();
        
        if (current_humidity.isValid())
        {
            write_to_file( current_humidity.get() );
            if (pot.is_dry( current_humidity.get() )){
            
            #ifdef DEBUG
            std::cout << "Soil is dry, need to add water \n";
            #endif

            tank.add_water();
            }

        } else {
            print::error_msg( current_humidity.exceptInfo() );
        }

        std::this_thread::sleep_for(std::chrono::minutes( t ));
        //err = true;
    }
    return 0;
}

template < typename T>
void write_to_file( T data ) 
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
    #ifdef DEBUG
    print::ok_msg( "Data written to file \n");
    #endif
}


