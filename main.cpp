#include "main.hpp"

#include <iostream>

Tank::Tank(const int t_id) : ID(t_id){}

int Tank::get_level()
{
    m_water_level = 1;
    std::cout << "Read the pressure sensor data..";
    return m_water_level; 
}

// send an email or power up a led 
int Tank::low_water_level() 
{
    std::cout << "Low water level in the tank";
    return 0;
}


Pot::Pot(const int t_id) : ID( t_id ){}

int Pot::get_humidity() 
{
    m_humidity = 1;
    std::cout << "Read data from humidity sensor..\n";   
    return m_humidity;      
}

int Pot::add_water()
{
    std::cout << "Adding water to the plant..\n";
    return 0;
}


int main()
{
    std::cout << "Start of main..\n";
    
    Tank tank{100};
    std::cout << "Created a new water tank with ID: " << tank.ID << '\n';
    
    Pot pot{1};
    std::cout << "Created a new flower pot with ID: " << pot.ID << '\n';


    return 0;
}