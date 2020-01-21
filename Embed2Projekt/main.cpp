#include "mbed.h"
#include "Temperature.h"
#include "Sound.h"
#include "LightSensor.h"
// main() runs in its own thread in the OS


Temperature tempSensor(A0,D2,D3);
//Sound soundSensor(A1);
//LightSensor lightSensor(A2);
int main()
{
    int read;
    //lightSensor.threshold = 0.3f;
    while (true) {
        read = tempSensor.readTemperature(F);

       // read = soundSensor.readSound();
        //read = lightSensor.readLight();
        printf("Tempereature in Fahnheit %i \n\r", read);
        
        ThisThread::sleep_for(1000);
    }
}

