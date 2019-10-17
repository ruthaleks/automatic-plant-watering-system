#pragma once 

#define CONTROL_PERIOD     1        // [min]   

/* TANK MANAGER */
#define WATER_AMOUNT       100     // [ ml ]

/* POT MANAGER */
#define MOIST_TRESHOLD     500

/* ADAFRUIT STEMMA I2C SOIL SENSOR  */
#define I2C_DEVICE_ADDRESS 0x36
#define I2C_BASE           0x0F
#define I2C_CHANNEL_OFFSET 0x10
#define MAX_MOIST_READING  2000
#define MIN_MOIST_READING  200

/* DC WATER PUMP */
#define FLOW_RATE           80   // Flow rate [ L/h ] 
#define PIN                 1    // GPIO18, Physical pin 12




