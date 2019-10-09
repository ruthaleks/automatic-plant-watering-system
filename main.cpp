#include <iostream>

class Tank 
{
private:
    int water_level; // remaing water quantity in the tank 

public:
    int id;          // tank ID

    Tank(int id)
    {
        id = id;
    }

    int get_level()
    {
        water_level = 1;
        std::cout << "Read the pressure sensor data..";
        return water_level; 
    }

    int low_water_level()
    /* send an email or power up a led */
    {
        std::cout << "Low water level in the tank";
        return 0;
    }
};


class Pot 
{
private:
    int humidity;       // current humidity 
    int volume;         // tracking the water volume added to the pot during a day            

public:
    int id;               // identification number
//    Tank water_tank;      // water tank that is connected to each pot 

    Pot(int id)
    {
        id = id;
    }

    int get_humidity() 
    {
        humidity = 1;
        std::cout << "Read data from humidity sensor..\n";   
        return humidity;      
    }

    int add_water()
    {
        std::cout << "Adding water to the plant..\n";
        return 0;
    }
};


int main()
{
    std::cout << "Start of main..\n";
    
    Tank tank{100};
    std::cout << "Created a new water tank with ID: " << tank.id << '\n';
    
    Pot pot{1};
    std::cout << "Created a new flower pot with ID: " << pot.id << '\n';


    return 0;
}