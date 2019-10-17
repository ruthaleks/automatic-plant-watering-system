#pragma once

#include <cstdint>

enum class SensorType { I2C_Sensor,
                        SIM_MoistSensor,
                        SIM_LoadSensor,
                        NO_Sensor };

enum class ActuatorType { SIM_Switch,
                          RELAY_Switch,
                          NO_Actuator };

auto init_read_func( SensorType ) -> int32_t (*) (void);


