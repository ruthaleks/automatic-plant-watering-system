#pragma once 

// make sure that the parameters are listed in the same order as in params.txt
// the numbers correspond to the line number
enum class Param { control_period = 2,
                    water_amount,
                    flow_rate, 
                    moist_treashold,
                    max_moist_reading,
                    min_moist_reading,
                    sampling_time,
                    i2c_device_address,
                    i2c_base,
                    i2c_channel_offset,
                    pump_gpio_pin };
