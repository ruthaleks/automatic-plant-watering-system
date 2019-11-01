#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <numeric>
#include <thread>
#include <vector>

#include "lib/expected.h"


#include "devices.hpp"
#include "potManager.hpp"
#include "sensorMonitor.hpp"
#include "utils.hpp"


PotManager::PotManager( SensorType sensor_type) :
 m_sensor_ptr{ new SensorMonitor{sensor_type} }{}

bool PotManager::is_dry( uint32_t hum ) const
// checks the sensor reading if the soil is dry and return true, else false 
{  
    if (!m_minmax_is_set ) {
         print::error_msg("Allowed sensor value range is not set.\n");
         return false;
    }
    if( !m_threashold ) {
        print::error_msg("A sensor threashold value is not set.\n");
        return false;
    }
   
    if ( (hum >= m_min) && (hum <= m_max) && (hum < m_threashold) ) {
        return true;  
    }
    return false; // soil is dry or error 
}

util::Expected<uint32_t> PotManager::humidity() const 
// The sensor readings from a specified time period (m_sample_period * m_samples) are collected
// and an average value is calculated  
{   
    std::vector<uint32_t> sensor_data{};
    #ifdef DEBUG
    std::cout << "Read data from humidity sensor..\n";  
    #endif 
    for (uint32_t n = 0; n < m_sampling_time; n++){
        util::Expected<uint32_t> value = m_sensor_ptr->value();
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
    print::ok_msg( "Current average humidity: " );
    std::cout << average << '\n';
    #endif
    return (uint32_t) average;
}

// getters
uint32_t PotManager::max() const noexcept {return m_max; }
uint32_t PotManager::min() const noexcept {return m_min; }
uint32_t PotManager::sampling_time() const noexcept { return m_sampling_time; }
SensorType PotManager::sensor() const { return m_sensor_ptr->type(); }
uint32_t PotManager::threashold() const{ return m_threashold; }

//setters
void PotManager::set_sensor_minmax(uint32_t min, uint32_t max)
{
    if (min <= max){
        m_min = min;
        m_max = max;
    } else {
        m_min = max;
        m_max = min; 
    }
    print::ok_msg("Allowed sensor range set to: ");
    std::cout << m_min << " - " << m_max << '\n';
    m_minmax_is_set = true;
}

void PotManager::set_sampling_time( uint32_t time )
{
    if( m_sensor_ptr->type() == SensorType::NO_Sensor){
        print::wrn_msg( "Cannot set the sampling time for the selected sensor type\n");
    } else if (time == 0) {
        print::error_msg("Cannot set the sampling time to zero.");
        std::cout << "The sample time is kept at: "<< m_sampling_time << "s\n";
    } else {
        m_sampling_time = time; 
        print::ok_msg( "The sampling time is set to: ");
        std::cout << m_sampling_time << "s\n"; 
    }
}

void PotManager::set_treashold( uint32_t value)
{
    if (!m_minmax_is_set){
        print::error_msg("Enter the allowed sensor value range before setting the threashold.\n");
    } else {
        if( value <= m_max && value >= m_min) {
            m_threashold = value;
            print::ok_msg( "The humidity threashold is set to: ");
            std::cout << m_threashold << '\n';
        } else {
            print::error_msg( "The selected threashold value is not within the range of the allowed sensor values: ");
            std::cout << m_min << " - " << m_max << '\n'; 
        }
    }
}