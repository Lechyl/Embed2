#include "mbed.h"
#include "Temperature.h"
#include "Sound.h"
#include "LightSensor.h"
// main() runs in its own thread in the OS


//Temperature tempSensor(A0,D2,D3);
//Sound soundSensor(A1);
LightSensor lightSensor(A2);
int main()
{
    float read;
    lightSensor.threshold = 0.3f;
    while (true) {
        //read = tempSensor.readTemperature(C);

       // read = soundSensor.readSound();
        read = lightSensor.readLight();
        printf("Light is %f and isItDay is %d \n", read, lightSensor.isItDay);
        
        ThisThread::sleep_for(1000);
    }
}

