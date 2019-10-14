class Tank 
{
    uint32_t m_water_level{}; // remaing water quantity in the tank 
    SensorType m_sensor_type{};
    ActuatorType m_actuator_type{};
    std::unique_ptr<Sensor> m_sensor_ptr{ new Sensor{ m_sensor_type } };
    std::unique_ptr<Actuator> m_actuator_ptr{ new Actuator{ m_actuator_type } };

    public: 
        Tank( SensorType, ActuatorType );        // constructor
        uint32_t level() const;   

};