#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "lib/expected.h"
#include "lib/print.hpp"


#include "parseParams.hpp"

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
        while (current_row != target_row && getline(file, line)){ current_row++; }
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

int32_t param(Param param ) noexcept
{
    util::Expected<int32_t> result{ parse_param(static_cast<uint32_t>(param)) };
    if (result.isValid()){
        int32_t data{static_cast<int32_t>(result.get())};
    }



}