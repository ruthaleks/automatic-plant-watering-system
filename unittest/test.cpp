#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../lib/expected.h"

#include "../potManager.hpp"
#include "../tankManager.hpp"

TEST_CASE("Tank manager, sensor and actutor types", "[tank]"){
    
    SECTION("SIM") {
        TankManager tank{ SensorType::SIM_LoadSensor, ActuatorType::SIM_Switch};
        REQUIRE( tank.sensor() == SensorType::SIM_LoadSensor );
        REQUIRE( tank.actuator() == ActuatorType::SIM_Switch );
    }
    SECTION("NO") {
        TankManager tank{ SensorType::NO_Sensor, ActuatorType::NO_Actuator};
        REQUIRE( tank.sensor() == SensorType::NO_Sensor );
        REQUIRE( tank.actuator() == ActuatorType::NO_Actuator );
    }
    SECTION("REAL") { // change later to real 
        TankManager tank{ SensorType::I2C_Sensor, ActuatorType::RELAY_Switch };
        REQUIRE( tank.sensor() == SensorType::I2C_Sensor );
        REQUIRE( tank.actuator() == ActuatorType::RELAY_Switch );
    }
}


TEST_CASE( "Test tank manager methods", "[tank]" ) {

    SECTION("Simulated sensor and actuator"){
        TankManager tank{ SensorType::SIM_MoistSensor, ActuatorType::SIM_Switch};
        // ----------------------------------------//
        // check default values 
        REQUIRE( tank.flow_rate() == 0.0 );
        REQUIRE( tank.water_amount() == 0 ); 
        REQUIRE( tank.add_water() == 0);
        // ----------------------------------------//
        // special cases
        tank.set_flow_rate( 10 );
        REQUIRE( tank.add_water() == 0 ); // water amount is still 0
        // ----------------------------------------//
        // the input is in L/h and the output should be in ml/s
        float c = 1000.0f / 3600.0f;
        tank.set_flow_rate( 50 );
        REQUIRE( tank.flow_rate() == 50.0f * c );

        tank.set_flow_rate(100);
        REQUIRE( tank.flow_rate() == 100.0f * c );

        tank.set_flow_rate( 0 );
        REQUIRE( tank.flow_rate() == 0.0 );

        tank.set_flow_rate( -10 );
        REQUIRE( tank.flow_rate() == -10.0 * c); 
        // ----------------------------------------//
        // the input should be equal to the output
        tank.set_water_amount( 100 );
        REQUIRE( tank.water_amount() == 100 );

        tank.set_water_amount( 0 );
        REQUIRE( tank.water_amount() == 0);
        // ---------------------------- ------------//
        // ml / (ml/s) = s 
        tank.set_water_amount( 100 );
        tank.set_flow_rate( 80 );
        REQUIRE( tank.add_water() == (uint32_t) (100.0f / (80.0f * c) * 1000.0f) );

        tank.set_water_amount( 13 );
        tank.set_flow_rate( 99 );
        REQUIRE( tank.add_water() == (uint32_t) (13.0f / (99.0f * c) * 1000.0f) );
        
        tank.set_water_amount( 13 );
        tank.set_flow_rate( -80 );
        REQUIRE( tank.add_water() == (uint32_t) (13.0f / (80.0f * c) * 1000.0f) ); // should return a positive value
        // ---------------------------- ------------//
        // TODO .level()
    }

    SECTION("No sensor and actuator"){
        TankManager tank{ SensorType::NO_Sensor, ActuatorType::NO_Actuator};
        REQUIRE( tank.sensor() == SensorType::NO_Sensor );
        REQUIRE( tank.actuator() == ActuatorType::NO_Actuator );
        
        // ----------------------------------------//
        // the default value is set to 0.0, should not be able to overwrite this value 
        // with sensor type NO_Actuator 
        tank.set_flow_rate( 50 );
        REQUIRE( tank.flow_rate() == 0.0f );

        tank.set_flow_rate(100);
        REQUIRE( tank.flow_rate() == 0.0f );
        // ----------------------------------------//
        // the default is set to 0 and should ot be overwritten when a NO_Actuator is selected
        tank.set_water_amount( 100 );
        REQUIRE( tank.water_amount() == 0 );

        tank.set_water_amount( 1 );
        REQUIRE( tank.water_amount() == 0);
        // ---------------------------- ------------//
        // Should not add any water with the selected actuator type 
        REQUIRE( tank.add_water() == 0 );
        REQUIRE( tank.add_water() == 0 );
        // ---------------------------- ------------//
        // TODO .level()
    }
}

TEST_CASE("Pot manager, sensor types", "[pot]"){
    
    SECTION("SIM") {
        PotManager pot{ SensorType::SIM_MoistSensor };
        REQUIRE( pot.sensor() == SensorType::SIM_MoistSensor );
    }
    SECTION("NO") {
        PotManager pot{ SensorType::NO_Sensor };
        REQUIRE( pot.sensor() == SensorType::NO_Sensor );
    }
    SECTION("REAL") {
        PotManager pot{ SensorType::I2C_Sensor };
        REQUIRE( pot.sensor() == SensorType::I2C_Sensor );
    }
}

TEST_CASE(" Test pot manager class", "[pot]")
{
    SECTION("Simulated sensor")
    {
        PotManager pot{ SensorType::SIM_MoistSensor };

        // ---------------------------- ------------//
        // default value check 
        REQUIRE( pot.threashold() == 0 );
        REQUIRE( pot.is_dry( 1 ) == false );
        REQUIRE( pot.sampling_time() == 1);
        REQUIRE( pot.max() == 0);
        REQUIRE( pot.min() == 0);

        //-------------------------------------------//
        // safety check, 
        pot.set_treashold( 10 );
        REQUIRE( pot.threashold() == 0 );
        REQUIRE( pot.is_dry( 1 ) == false );
    
        //-------------------------------------------//
        // set min max range
        pot.set_sensor_minmax(200, 2000);
        REQUIRE( pot.max() == 2000 );
        REQUIRE( pot.min() == 200 );
        REQUIRE( pot.is_dry( 300 ) == false);
        REQUIRE( pot.is_dry( 100 ) == false);
         
        pot.set_sensor_minmax(1000, 100); // reversed min max
        REQUIRE( pot.max() == 1000 );
        REQUIRE( pot.min() == 100 ); 
        REQUIRE( pot.is_dry( 800 ) == false);
        REQUIRE( pot.is_dry( 100 ) == false);
        
        //-------------------------------------------//
        // test of threashold
        pot.set_sensor_minmax(800, 500);
        pot.set_treashold( 600 );
        REQUIRE( pot.threashold() == 600 );

        pot.set_treashold( 100 ); // below min value
        REQUIRE( pot.threashold() == 600 );

        pot.set_treashold( 500 );
        REQUIRE( pot.threashold() == 500 );

        // ---------------------------- ------------//
        // the default sampling time is set to 1
    
        pot.set_sampling_time( 10 );
        REQUIRE(pot.sampling_time() == 10);
        pot.set_sampling_time( 0 ); // can not set to 0
        REQUIRE(pot.sampling_time() == 10);

        pot.set_sampling_time( 54 );
        REQUIRE(pot.sampling_time() == 54 );
        // ---------------------------- ------------//
        // test is dry
        pot.set_sensor_minmax(800, 500);
        pot.set_treashold( 700 );
        pot.set_sampling_time( 3 ); // choose a short period 
        
        REQUIRE( pot.is_dry( 499 ) == false ); // below min
        REQUIRE( pot.is_dry( 501 ) == true ); // above min
        REQUIRE( pot.is_dry( 500 ) == true  ); // below threashold
        REQUIRE( pot.is_dry( 700 ) == false ); // on threashold
        REQUIRE( pot.is_dry( 1000) == false ); // above max 
    }

}


