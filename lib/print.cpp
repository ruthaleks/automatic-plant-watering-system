#include <iostream>

#include "colors.hpp"

namespace print{

void error_msg(const char* msg) {
    std::cout << BOLD(FRED("ERR ")) << msg ;
}

void wrn_msg(const char* msg) {
    std::cout << BOLD(FYEL("WRN ")) << msg ;
}

void ok_msg(const char* msg) {
    std::cout << BOLD(FGRN("OK ")) << msg ;
}

}