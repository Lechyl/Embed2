
#ifndef TEMP_TOKEN
#define TEMP_TOKEN
#include "mbed.h"

enum Type{C = 0, F = 1};
//enum Voltage{Low = 0, High = 20};
class Temperature{

    private:
        
        unsigned int a, beta = 3975;
        float resistance, _temperature;      
        PinName _ledForHotTemp, _ledForColdTemp, _tempSensor;
        
  

    public:
        Temperature(PinName pinTempSensor, PinName pinLedForHotTemp, PinName pinLedForColdTemp);
        ~Temperature();
        int readTemperature(Type type);

};

#endif