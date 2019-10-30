#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "lib/expected.h"
#include "lib/print.hpp"


#include "parseParams.hpp"
#include "potManager.hpp"
#include "tankManager.hpp"

/**
    reads in and parses the parameter value on a given row 
    in the parameter file. 

    @param taget row and the path to the parameter file
    @return the value or an exception
*/
util::Expected<int32_t> parse_param( uint32_t target_row, const char* file_name="params.txt" )  noexcept
{
    std::string line;
    std::ifstream file(file_name);
    if(file.is_open()){
        uint32_t current_row{0};
        while (current_row != target_row && getline(file, line))
        { 
            current_row++; 
        }
        file.close();
        if ( current_row == target_row){
            //remove leading spaces and trailing chars 
            std::regex r_leading_spaces("^[\\s]*");
            std::regex r_trailing_chars("[\\s|/].*$");
            line = std::regex_replace(line, r_leading_spaces , "");
            line = std::regex_replace(line, r_trailing_chars, "");

            // check that the line contains only numbers
            std::regex r_numbers("[-|+]?\\d+");
            std::regex r_hex_numbers("0x[0-9|A-F|a-f]+");
            if ( std::regex_match(line, r_numbers) ) 
            {   
                int32_t param_value{ std::stoi( line )};
                return param_value;

            } else if (std::regex_match(line, r_hex_numbers)) {
                int32_t param_value{ std::stoi( line, 0, 16)};
                return param_value;                

            } else {
                std::ostringstream errmsg;
                errmsg << "Not a valid number: "<< line << '\n';
                return std::invalid_argument( errmsg.str() );
            }

        } else {
            return std::invalid_argument("Parameter not found\n");
        }
    }
    return std::invalid_argument("Could not open file\n");

}
/**
 *  sets the parameters of TankManager and PotManager objects

    @param reference to a TankManager and PotManager objects
    @return void
*/
void set_params(TankManager& tank, PotManager& pot) noexcept
{
    bool ok{true};
    // TODO Handle all sensor types 
    // Handle negative inputs 
    util::Expected<int32_t> param{
         parse_param(static_cast<uint32_t>(Param::flow_rate))};
    if (param.isValid()){
        tank.set_flow_rate(param.get());
    } else {
        print::wrn_msg("Could not set the flow rate\n");
        print::wrn_msg(param.exceptInfo());
    }

    param = parse_param(static_cast<uint32_t>(Param::water_amount));
    if (param.isValid()){
        tank.set_water_amount(static_cast<uint32_t>(param.get()));
    } else {
        print::wrn_msg("Could not set the water amount\n");
        print::wrn_msg(param.exceptInfo());
    }

    param = parse_param(static_cast<uint32_t>(Param::min_moist_reading));
    util::Expected<int32_t> param2{
        parse_param(static_cast<uint32_t>(Param::max_moist_reading))};
    if (param.isValid() && param2.isValid()){
        pot.set_sensor_minmax(static_cast<uint32_t>(param.get()), 
        static_cast<uint32_t>(param2.get()));
    } else {
        print::error_msg("Could not set the sensor range\n");
        ok = false;
        if(!param.isValid())
            print::error_msg(param.exceptInfo());
        if(!param2.isValid())
            print::error_msg(param2.exceptInfo());
    }

    param = parse_param(static_cast<uint32_t>(Param::moist_treashold));
    if(param.isValid()){
        pot.set_treashold(static_cast<uint32_t>(param.get()));
    } else {
        print::error_msg("Could not set the humidity threashold\n");
        print::error_msg(param.exceptInfo());
        ok=false;
    }

    param = parse_param(static_cast<uint32_t>(Param::sampling_time));
    if(param.isValid()){
        pot.set_sampling_time(static_cast<uint32_t>(param.get()));
    } else {
        print::error_msg("Could not set the sampling time for the humidity sensor\n");
        print::error_msg(param.exceptInfo());
    }
    if (!ok){
        exit(EXIT_FAILURE);
    }
}