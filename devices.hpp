#pragma once

enum class SensorType { ADA_MoistSensor,
                        SIM_MoistSensor,
                        SIM_LoadSensor,
                        NO_Sensor };

enum class ActuatorType { SIM_Pump,
                          NO_Actuator };

int32_t read_sensor_value( );


