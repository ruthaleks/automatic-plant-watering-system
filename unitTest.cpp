#include "main.hpp"
#include "errorCodes.hpp"
#include "unitTest.hpp"

#include <iostream>

bool test_connect_to_tank()
{
    bool passed{ true };

    std::cout << "Testing Pot::connect_to_tank()\n";
    // Test 1: Connect a tank to a pot
    Pot pot{};
    Tank tank{};

    int32 ecode{ pot.connect_to_tank( &tank ) };
    if ( ecode != NO_ERROR)
    {
        std::cout << "Test 1: Failed to connect. Error code: " 
        << ecode << '\n';
        passed = false;
    } else {
        std::cout << "Test 1: Passed.\n"; 
    }

    // Test2: Send in a nullptr 
    Pot pot2{};
    ecode = pot2.connect_to_tank( nullptr );
    if (ecode == NULL_POINTER_ERROR )
    {
        std::cout << "Test 2: Passed. \n";
    } else if(ecode == NO_ERROR) {
        std::cout << "Test 2: Failed. No error detected.\n";
        passed = false;
    } else {
        std::cout << "Test 2: Failed. Unknown error code. Error code: " <<
        ecode << '\n';
        passed = false;
    }

    std::cout << "Testing Pot::get_tank_id()\n";
    // Test3: Test to obtain the tank ID number
    uint32 id{ pot.get_tank_id() };
    if (id == tank.ID)
    {
        std::cout << "Test 3: Passed.\n";
    } else {
        std::cout << "Test 3: Failed. ID number do not match " 
        << "correct ID " << tank.ID << " obtained ID: " << id << '\n';
        passed = false;
    }
    return passed;
}


void test(){
    std::cout << "** Start of unit tests **\n";
    test_connect_to_tank();
} 
