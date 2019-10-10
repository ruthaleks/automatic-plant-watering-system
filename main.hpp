#ifndef MAIN_HPP
#define MAIN_HPP

typedef unsigned int uint32;
typedef int int32;


class Tank 
{
    int32 m_water_level{}; // remaing water quantity in the tank 

    public: 
        const uint32 ID;               // tank ID 
        Tank();        // constructor
        int32 get_level(); 
        int32 low_water_level();

};

class Pot
{
    int32 m_humidity{};   // current humidity of the soil
    uint32 m_volume{};     // water volume added to the pot during a certain time period
    Tank *m_p_tank{ nullptr };     // poiter to a water tank

    public:
        const uint32 ID;             // pot ID
        Pot();        // constructor
        int32 connect_to_tank(Tank *);
        uint32 get_tank_id();
        int32 get_humidity(); 
        int32 add_water();    
};

#endif
