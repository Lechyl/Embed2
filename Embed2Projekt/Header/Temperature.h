#include "mbed.h"

enum Type{C = 0, F = 1};
enum Voltage{Low = 0, High = 20};
class Temperature{

    private:
        
        unsigned int a, beta = 3975, units, tens;
        float resistance, _temperature;

    public:
        int readTemperature(Type type, AnalogIn pin);

    

};
