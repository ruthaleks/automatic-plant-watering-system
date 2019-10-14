#pragma once
// Change to scoped enums
enum SensorType { ADA_MoistSensor,
                  SIM_MoistSensor,
                  SIM_LoadSensor };

enum ActuatorType { SIM_Pump };



uint32_t get_sensor_value( SensorType );       // return data
int32_t set_actuator( ActuatorType, int32_t ); // return status
