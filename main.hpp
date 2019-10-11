#ifndef MAIN_HPP
#define MAIN_HPP


class Tank 
{
    int32_t m_water_level{}; // remaing water quantity in the tank 

    public: 
        const uint32_t ID;               // tank ID 
        Tank();        // constructor
        int32_t get_level(); 
        int32_t low_water_level();

};

class Pot
{
    int32_t m_humidity{};   // current humidity of the soil
    uint32_t m_volume{};     // water volume added to the pot during a certain time period
    Tank *m_p_tank{ nullptr };     // poiter to a water tank

    public:
        const uint32_t ID;             // pot ID
        Pot();        // constructor
        int32_t connect_to_tank(Tank *);
        uint32_t get_tank_id();
        int32_t get_humidity(); 
        int32_t add_water();    
};

#endif
