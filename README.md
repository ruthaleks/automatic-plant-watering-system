# Automatic plant watering system 
The purpose of this project is to gain more pratical experience and knowledge within embedded programming using C++.

## Project description 
The whole system is controlled by a Raspberry Pi and designed for indoor use. The humidity of the soil in the pot will be monitored with a moisture sensor. A water pump will be connected to a water tank which will be used to control the water supply to the pot.

The water level in the tank will be monitored with a pressure sensor that will be placed below the tank. When the level in the water tank is low a red led will start blinking indicating low water level. 

## Functionality 
* Water the plant with small quantity of water around 50ml when it is dry and ignore the readings from the humidity sensor for some time to let the plant absorb the liquid before adding more water to the pot. 
* Depending on the plant you might want to tune the threshold for dry and wet soil. Some plants prefer to dry out before watering next time.   
* If the watering system is placed in the bedroom the pump might disturb during night time. The watering should therefore be executed only day time.


## Security 
In order to avoid flooding it is importaint to implement cetrain security functions.

* Set a maximum quantity water per day and cut the power to the pump if the maximum level is reached. 

## Pin connections

**Relay module (control of water pump)**

* Controlled through GPIO18 (pin 12) which is connected *S* on the relay
* Connect *+* to 3V3 (pin 1)
* Connect *-* to GND (pin 9)

**LED**

* Controlled through GPIO4 (pin 7) which is connected to *+* (longer leg) of the led
* Make sure to include a 330ohm resistor in the circuit to limit the current flow
* Connect *-* to GND (pin 6)


## Manuals
Relay module: [*User guide*](https://www.electrokit.com/uploads/productfile/41015/41015704_-_5V_Relay_Module.pdf)

Soil sensor: [*User guide*](https://www.electrokit.com/uploads/productfile/41016/adafruit-stemma-soil-sensor-i2c-capacitive-moisture-sensor.pdf)

HX711 ADC: [*User guide*](https://www.electrokit.com/uploads/productfile/41016/hx711_english.pdf), [*Example*](https://www.instructables.com/id/Arduino-Scale-With-5kg-Load-Cell-and-HX711-Amplifi/), [*Schematics*](https://www.electrokit.com/uploads/productfile/41016/HX711.jpg), [*Library for Adruino*](https://github.com/bogde/HX711)

## Hardware 
* Adafruit STEMMA Soil Sensor - I2C Capacitive Moisture Sensor
* JST 4PH to female header cable 
* DC 3-6V Mini submersible water pump
* SRD-05VDC-SL-C Relay module
* Load-cell 10kg 
* HX711 ADC for weigh scales 

# Concepts 
* Function pointers
* Smart pointers 
* Scoped and unscoped enums 
* Uniform initialization
* rvalue-, lvalue- and universial referenses 
* std::vector and arrays
* Immutable variables and methods
* Lambda expressions
* Templates

# TODO
* Structure source code in subfolders
