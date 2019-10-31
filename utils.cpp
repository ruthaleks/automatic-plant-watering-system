#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <regex>

#include "lib/expected.h"
#include "lib/print.hpp"

#include "params.hpp"
#include "potManager.hpp"
#include "tankManager.hpp"
#include "utils.hpp"

/**
    reads in and parses the parameter value on a given row 
    in the parameter file. 

    @param taget row and the path to the parameter file
    @return the value or an exception
*/
Exp_i32 parse_param( uint32_t target_row, const char* file_name)  noexcept
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
 *  converts int32 to a variable of type Exp_T 
 *  where T should be: uint32 or int32
 * 
    @param:  
    @return:
*/
template <typename T>
const util::Expected<T> check_type(int32_t value, T& ) noexcept
{
    if(value >= static_cast<int32_t>(std::numeric_limits<T>::min())){
            return static_cast<T>(value);
    } else {
            return std::domain_error("The value must be positive.\n");
    }
    
}
/**
 *  reads in a parameter and converts it to the type T
 *  
    @param: 
    @return: 
*/
template <typename T>
const util::Expected<T> read_param(Param param, T& type) noexcept
{
    util::Expected<int32_t> res{ 
        parse_param(static_cast<uint32_t> (param), "params.txt")};
    if( res.isValid() ){
        util::Expected<T> data{ check_type(res.get(), type)};
        if(data.isValid()){
            return data.get();
        }
        return data;
    }
    return static_cast<util::Expected<T>>(res); 
}

/*
 *  Sets the parameters of TankManager and PotManager objects and 
 *  displays error messages in case of failure. The progra exits if 
 *  critical parameters where not set.

    @param: 
    @return: 
*/

void set_params(TankManager& tank, PotManager& pot) noexcept
{
    bool ok{true};
    int32_t i32{}; 
    uint32_t u32{};

    Exp_i32 flow_rate{ read_param(Param::flow_rate, i32)};
    if (flow_rate.isValid()) {
        tank.set_flow_rate( flow_rate.get() );
    } else {
        print::wrn_msg("The flow rate cannot be set: ");
        std::cout << flow_rate.exceptInfo();
    }

    Exp_u32 water_amount{ read_param(Param::water_amount, u32) };
    if (water_amount.isValid()){
        tank.set_water_amount(water_amount.get());
    } else {
        print::wrn_msg("The water amount cannot be set: ");
        std::cout << water_amount.exceptInfo();
    }

    Exp_u32 min{read_param(Param::min_moist_reading, u32)};
    Exp_u32 max{read_param(Param::max_moist_reading, u32)};
    if (min.isValid() && max.isValid()){
        pot.set_sensor_minmax(min.get(), max.get());
    } else {
        ok = false;
        print::error_msg("The sensor range cannot be set: ");
        if(!min.isValid())
            std::cout << min.exceptInfo();
        if(!max.isValid())
            std::cout << max.exceptInfo();
    }

    Exp_u32 treashold{read_param(Param::moist_treashold, u32)};
    if(treashold.isValid()){
        pot.set_treashold(treashold.get());
    } else {
        ok=false;
        print::error_msg("The humidity threashold cannot be set: ");
        std::cout << treashold.exceptInfo();
    }

    Exp_u32 sampl_time{read_param(Param::sampling_time, u32)};
    if(sampl_time.isValid()){
        pot.set_sampling_time(sampl_time.get());
    } else {
        print::wrn_msg("The sampling time for the humidity sensor cannot be set :");
        std::cout << sampl_time.exceptInfo();
    }
    if (!ok){
        exit(EXIT_FAILURE);
    }
    
}
 