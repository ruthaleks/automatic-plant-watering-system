#pragma once
// Change to scoped enums
enum SensorID { ADA_MoistSensor,
                SIM_MoistSensor,
                SIM_LoadSensor };

enum ActuatorID { SIM_Pump };



uint32_t get_sensor_value( SensorID );       // return data
int32_t set_actuator( ActuatorID, int32_t ); // return status
