#include "Temperature.h"

/**
*
*   @author: Long and Nilas
*   @date: 20/1-20
*   @brief: A class for reading temperature and turn on/off led if too hot or/and cold.
*/


/// Constructor, contain 3 pin parameters for tempereature sensor, led for too hot, led for too cold.
Temperature::Temperature(PinName pinTempSensor, PinName pinLedForHotTemp,PinName pinLedForColdTemp){
    _tempSensor = pinTempSensor;
    _ledForHotTemp = pinLedForHotTemp;
    _ledForColdTemp = pinLedForColdTemp;
}

/// Destructor for the destruction of the class object.
Temperature::~Temperature(){
}

/// Read temperature from the temperature sensor and return it.
int Temperature::readTemperature(Type type){
    AnalogIn tempSensor (_tempSensor);
    DigitalOut ledHot (_ledForHotTemp);
    DigitalOut ledCold (_ledForColdTemp);
    a = tempSensor.read_u16();
    switch(type){
        case C:
            /// Calculate the resistance of the thermistor from analog votage read.
            resistance = (float) 10000.0 * ((65536.0 / a) - 1.0);

             /// Convert the resistance to temperature using Steinhart's Hart equation. 
            _temperature=(1/((log(resistance/10000.0)/beta) + (1.0/298.15)))-273.15; 

            /// over home temp >= 24
            ledHot = (int)_temperature >= 24 ? 1 : 0;

            /// under home temp <= 21
            ledCold = (int)_temperature <= 21 ? 1 : 0;

            break;
        case F:
            break;
    }

    return  (int)_temperature;
}


