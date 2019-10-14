class Tank 
{
    uint32_t m_water_level{}; // remaing water quantity in the tank 
    SensorID m_load_sensor{};
    ActuatorID m_pump{};

    public: 
        Tank( SensorID, ActuatorID );        // constructor
        uint32_t level() const;  // remove get 
        SensorID sensor() const;
        ActuatorID actuator() const; 

};