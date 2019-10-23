#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "../tankManager.hpp"

TEST_CASE( "Test tankManager class", "[tank]" ) {
    SECTION("Simulated sensors and actuators"){
        TankManager tank{ SensorType::SIM_MoistSensor, ActuatorType::SIM_Switch};
        REQUIRE( tank.sensor() == SensorType::SIM_MoistSensor );
        REQUIRE( tank.actuator() == ActuatorType::SIM_Switch );

        // the input is in L/h and the output should be in ml/s
        float c = 1000.0f / 3600.0f;
        tank.set_flow_rate( 50 );
        REQUIRE( tank.flow_rate() == 50.0f * c );

        tank.set_flow_rate(100);
        REQUIRE( tank.flow_rate() == 100.0f * c );


    }

}