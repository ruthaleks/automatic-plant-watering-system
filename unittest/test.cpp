#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "../potManager.hpp"
#include "../tankManager.hpp"

TEST_CASE( "Test tankManager class", "[tank]" ) {

    SECTION("Simulated sensor and actuator"){
        TankManager tank{ SensorType::SIM_MoistSensor, ActuatorType::SIM_Switch};
        REQUIRE( tank.sensor() == SensorType::SIM_MoistSensor );
        REQUIRE( tank.actuator() == ActuatorType::SIM_Switch );
        
        // ----------------------------------------//
        // the input is in L/h and the output should be in ml/s
        float c = 1000.0f / 3600.0f;
        tank.set_flow_rate( 50 );
        REQUIRE( tank.flow_rate() == 50.0f * c );

        tank.set_flow_rate(100);
        REQUIRE( tank.flow_rate() == 100.0f * c );
        // ----------------------------------------//
        // the input should be equal to the output
        tank.set_water_amount( 100 );
        REQUIRE( tank.water_amount() == 100 );

        tank.set_water_amount( 1 );
        REQUIRE( tank.water_amount() == 1);
        // ---------------------------- ------------//
        // ml / (ml/s) = s 
        tank.set_water_amount( 100 );
        tank.set_flow_rate( 80 );
        REQUIRE( tank.add_water() == (uint32_t) (100.0f / (80.0f * c) * 1000.0f) );

        tank.set_water_amount( 13 );
        tank.set_flow_rate( 99 );
        REQUIRE( tank.add_water() == (uint32_t) (13.0f / (99.0f * c) * 1000.0f) );
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

TEST_CASE(" Test pot manager class", "[pot]")
{
    SECTION("Simulated sensor")
    {
        PotManager pot{ SensorType::SIM_MoistSensor };
        REQUIRE( pot.sensor() == SensorType::SIM_MoistSensor );

        // ---------------------------- ------------//
        // 
        pot.set_treashold( 1000 );
        REQUIRE( pot.threashold() == 1000 );

        pot.set_treashold( 10 );
        REQUIRE( pot.threashold() == 10 );
        // ---------------------------- ------------//
        // the default sampling time is set to 1
        REQUIRE( pot.sampling_time() == 1);

        pot.set_sampling_time( 10 );
        REQUIRE(pot.sampling_time() == 10);
        pot.set_sampling_time( 0 ); // can not set to 0
        REQUIRE(pot.sampling_time() == 10);

        pot.set_sampling_time( 54 );
        REQUIRE(pot.sampling_time() == 54 );


    }

}


