#pragma once

#include <cstdint>

#include "lib/expected.h"

enum class SensorType { I2C_Sensor,
                        SIM_MoistSensor,
                        SIM_LoadSensor,
                        NO_Sensor };

enum class ActuatorType { SIM_Switch,
                          RELAY_Switch,
                          NO_Actuator };

auto init_read_func( SensorType ) -> util::Expected<int32_t> (*) (void);
auto init_control_func( ActuatorType ) -> void (*) (int32_t);


