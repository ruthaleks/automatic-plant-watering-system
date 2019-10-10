class Tank 
{
    int m_water_level; // remaing water quantity in the tank 

    public: 
        const int ID;       // tank ID 
        Tank( const int );        // constructor
        int get_level(); 
        int low_water_level();

};

class Pot
{
    int m_humidity;   // current humidity of the soil
    int m_volume;     // water volume added to the pot during a certain time period

    public:
        const int ID;       // pot ID
        Pot( const int );         // constructor
        int get_humidity(); 
        int add_water();    
};