#include "mbed.h"
#include "Temperature.h"
// main() runs in its own thread in the OS


AnalogIn tempSensor(A0);
Temperature tmp;
int main()
{
    int read;
    
    while (true) {
        read = tmp.readTemperature(C, tempSensor);
        printf("tempereature is %i \n", read);
        
        ThisThread::sleep_for(1000);
    }
}

