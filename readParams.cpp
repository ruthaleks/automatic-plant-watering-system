#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>

#include "lib/expected.h"
#include "lib/print.hpp"


#include "readParams.hpp"


util::Expected<int32_t> read_param( Param param ) 
{
    int32_t target_row = static_cast<int32_t> (param);
    std::string line;
    std::ifstream file("params.txt");
    if(file.is_open()){
        int32_t current_row{0};
        while (current_row != target_row && getline(file, line)){ current_row++; }
        if ( current_row == target_row){
            //remove leading spaces and trailing chars 
            std::regex r_leading_spaces("^[\\s]*");
            std::regex r_trailing_chars("[\\s|\\W].*$");
            line = std::regex_replace(line, r_leading_spaces , "");
            line = std::regex_replace(line, r_trailing_chars, "");

            // check that the line contains only numbers
            std::regex r_numbers("[+|-]?\\d+");
            if ( std::regex_match(line, r_numbers) ) 
            {   
                int32_t param_value{ std::stoi( line )};
                return param_value;

            } else {
                print::error_msg("Not a valid number: ");
                std::cout << line << '\n';
                return std::invalid_argument("");
            }

        } else {
            print::error_msg("Parameter not found.\n");
            return std::invalid_argument("");
        }
    }
    print::error_msg("Could not open file\n");
    return std::invalid_argument("");

}
//template<typename T>
//void set_param(Param param, void (*func)(T) )
//{


//}