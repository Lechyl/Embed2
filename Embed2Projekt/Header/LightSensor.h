#ifndef LIGHTSENSOR_TOKEN
#define LIGHTSENSOR_TOKEN

#include "mbed.h"

class LightSensor{
    private:
        PinName _lightSensor;
        float lightValue;
    public:
        bool isItDay;
        float threshold;
        LightSensor(PinName pin);
        float readLight();


};

#endif