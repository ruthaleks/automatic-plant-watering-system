#include <chrono>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <thread>
#include <vector>


#include "devices.hpp"
#include "potManager.hpp"
#include "sensorMonitor.hpp"


PotManager::PotManager( SensorType sensor_type) : m_sensor_ptr{ new SensorMonitor{sensor_type} }{}

uint32_t PotManager::humidity() const 
{   
    // The sensor readings from a specified time period are collected
    // and analysed  
    std::vector<int32_t> sensor_data{};
    std::cout << "Read data from humidity sensor..\n";    
    for (uint32_t n = 0; n < m_sample_number; n++){
        sensor_data.push_back(m_sensor_ptr->value());
        std::this_thread::sleep_for(std::chrono::seconds( m_sample_period ));
    }
    // calculate the average 
    float average = (float) std::accumulate(sensor_data.begin(), 
        sensor_data.end(), 0.0) / sensor_data.size(); 

    std::cout << "Current average humidity: " << average << '\n';
    write_to_file( average );
    return (uint32_t) average;
}

bool PotManager::is_dry() const
{  
    if (m_sensor_ptr->type() == SensorType::NO_Sensor){
        return false;
    }
    
    if (humidity() < m_threashold ) {  
        return true; // soil is dry
    } 
    return false;
}

SensorType PotManager::sensor() const
{
    return m_sensor_ptr->type();
}

void PotManager::set_treashold( uint32_t value)
{
    m_threashold = value;
    std::cout << "The humidity threashold is set to: " << m_threashold << '\n';
}
void PotManager::write_to_file( float data ) const
{
    std::cout << "Writing data to file\n";
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