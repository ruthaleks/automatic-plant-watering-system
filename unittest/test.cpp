#define CATCH_CONFIG_MAIN


#include "catch.hpp"
#include "../lib/expected.h"

#include "../parseParams.hpp"
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

TEST_CASE("Test of parse_param function", "[read]"){

const char* file_name = "unittest/unittest_params.txt";
    
    SECTION("incorrect params.txt path") {
        std::string output{parse_param(2, "wrong/path/params.txt").exceptInfo()};
        std::string correct_output{"Could not open file\n"};
        REQUIRE( output.compare(correct_output) == 0);
    }
    REQUIRE(parse_param(2, file_name).get() == 1);
    
    SECTION("remove leading and trailing spaces"){
        REQUIRE(parse_param(3, file_name).get() == 100);
    }
    SECTION("remove trailing non alphabetic signs"){
        REQUIRE(parse_param(4, file_name).get() == 500);
    }
    SECTION("handle + and - signs"){
        REQUIRE(parse_param(5, file_name).get() == -465);
        REQUIRE(parse_param(6, file_name).get() == -545);
        REQUIRE(parse_param(7, file_name).get() == 545);
        REQUIRE(parse_param(8, file_name).get() == 348);
    }
    SECTION("hex values"){
        REQUIRE(parse_param(9, file_name).get() == 0x36);
        REQUIRE(parse_param(10, file_name).get() == 0xabf1f);
    }

    SECTION("invalid numbers"){
        std::string output1{parse_param(11, file_name).exceptInfo()};
        std::string output2{parse_param(12, file_name).exceptInfo()};
        std::string output3{parse_param(13, file_name).exceptInfo()};
        std::string correct_output1{"Not a valid number: \n"};
        std::string correct_output2{"Not a valid number: ahj100\n"};
        std::string correct_output3{"Not a valid number: +100a\n"};
        REQUIRE( output1.compare(correct_output1) == 0);
        REQUIRE( output2.compare(correct_output2) == 0);
        REQUIRE( output3.compare(correct_output3) == 0);
    }

    SECTION("out of range"){
        std::string output{parse_param(20, file_name).exceptInfo()};
        std::string correct_output{"Parameter not found\n"};
        REQUIRE( output.compare(correct_output) == 0);
    }




}


