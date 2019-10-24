#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <numeric>
#include <thread>
#include <vector>

#include "lib/colors.hpp"
#include "lib/expected.h"

#include "devices.hpp"
#include "potManager.hpp"
#include "sensorMonitor.hpp"


PotManager::PotManager( SensorType sensor_type) :
 m_sensor_ptr{ new SensorMonitor{sensor_type} }{}

bool PotManager::is_dry( util::Expected<uint32_t> hum ) const
// checks the sensor reading if the soil is dry and return true, else false 
{  
    if ( hum.isValid() ){
        if ( hum.get() < m_threashold ) {
            return true;  
        }
    }
    return false; // soil is dry or sensor error 
}

util::Expected<uint32_t> PotManager::humidity() const 
// The sensor readings from a specified time period (m_sample_period * m_samples) are collected
// and an average value is calculated  
{   
    std::vector<int32_t> sensor_data{};
    #ifdef DEBUG
    std::cout << "Read data from humidity sensor..\n";  
    #endif 
    for (uint32_t n = 0; n < m_sampling_time; n++){
        util::Expected<int32_t> value = m_sensor_ptr->value();
        if (value.isValid()){
            sensor_data.push_back( value.get() );
            std::this_thread::sleep_for(std::chrono::seconds( 1 )); // sample with 1Hz
        } else {
            return value; // return error
        }
    }   
    // calculate the average 
    float average{ (float) std::accumulate(sensor_data.begin(), 
        sensor_data.end(), 0.0) / sensor_data.size() }; 
    #ifdef DEBUG
    std::cout << "Current average humidity: " << average << '\n';
    #endif
    return (uint32_t) average;
}

// getters
uint32_t PotManager::sampling_time() const noexcept { return m_sampling_time; }
SensorType PotManager::sensor() const { return m_sensor_ptr->type(); }
uint32_t PotManager::threashold() const{ return m_threashold; }

//setters
void PotManager::set_sampling_time( uint32_t time )
{
    if( m_sensor_ptr->type() == SensorType::NO_Sensor){
        std::cout << "#WRN Cannot set the sampling time for the selected sensor type\n";
    } else if (time == 0) {
        std::cout << BOLD(FRED("#ERR Cannot set the sampling time to zero.")) <<" The sample time is kept at: "<< m_sampling_time << "s\n";
    } else {
        m_sampling_time = time; 
        std::cout << "The sampling time is set to: " << m_sampling_time << "s\n"; 
    }
}

void PotManager::set_treashold( uint32_t value)
{
    m_threashold = value;
    std::cout << "The humidity threashold is set to: " << m_threashold << '\n';
}