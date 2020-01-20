#include "Temperature.h"

int Temperature::readTemperature(Type type, AnalogIn pin){
    a = pin.read_u16();
    switch(type){
        case C:
            /* Calculate the resistance of the thermistor from analog votage read. */
            resistance = (float) 10000.0 * ((65536.0 / a) - 1.0);

             /* Convert the resistance to temperature using Steinhart's Hart equation */
                _temperature=(1/((log(resistance/10000.0)/beta) + (1.0/298.15)))-273.15; 

            break;
        case F:
            break;
    }

    return  (int)_temperature;
};
