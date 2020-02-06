#include "LightSensor.h"

/**
*
*   @author: Long and Nilas
*   @date: 21/1-20
*   @brief: This is a Light sensor class which read from the sensor and return the read in float and a @isItDay variable
*   @parameters: @threshold = indikator for when it's night and day in float, @isItDay is a bool variable which check if it's day = true/night = false.
*
*/
LightSensor::LightSensor(PinName pin){
    _lightSensor = pin;
}

float LightSensor::readLight()
{
    AnalogIn lightSensor (_lightSensor);
    
    /// Sample 16hz and calculating the average
    for(int i = 0;i < 16;i++){

        lightValue += lightSensor.read();

      
       wait(0.0625);
        
    }
    
    lightValue = lightValue / 16;
    
    isItDay = lightValue >= threshold ? true : false;

    return lightValue;
}