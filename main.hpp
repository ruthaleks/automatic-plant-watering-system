#pragma once

class Tank 
{
    uint32_t m_water_level{}; // remaing water quantity in the tank 
    SensorID m_load_sensor_id{};
    ActuatorID m_pump_id{};

    public: 
        const uint32_t ID;            // tank ID 
        Tank( SensorID, ActuatorID );        // constructor
        uint32_t get_level();  // remove get
        int32_t low_water_level();
        SensorID get_sensor();
        ActuatorID get_actuator(); 

};

class Pot
{
    int32_t m_humidity{};   // current humidity of the soil
    uint32_t m_volume{};     // water volume added to the pot during a certain time period
    Tank *m_p_tank{ nullptr };     // poiter to a water tank
    SensorID m_moist_sensor_id{};

    public:
        const uint32_t ID;             // pot ID
        Pot( SensorID );        // constructor
        int32_t connect_to_tank(Tank *);
        uint32_t get_tank_id();
        int32_t get_humidity(); 
        int32_t add_water();
        SensorID get_sensor();
};

