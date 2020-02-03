#ifndef LIGHTSENSOR_TOKEN
#define LIGHTSENSOR_TOKEN

#include "mbed.h"

class LightSensor{
    private:
        PinName _lightSensor;

    public:
        bool isItDay;
        float threshold;
        LightSensor(PinName pin);
        float readLight();


};

#endif