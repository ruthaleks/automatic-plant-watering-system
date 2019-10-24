#pragma once

#include <cstdint>

#include "tankManager.hpp"
#include "potManager.hpp"

int32_t control_routine( PotManager &, TankManager &);
template <typename T>
void write_to_file( T );