#pragma once    
#include <cstdint>

#include "lib/expected.h"

enum class Param { control_period = 2, 
                    moist_treashold };

util::Expected<int32_t> read_param( Param );
