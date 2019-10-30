#pragma once    
#include <cstdint>

#include "lib/expected.h"

enum class Param { control_period = 2, 
                    moist_treashold };


void set_param( Param );
