#include "mbed.h"
#include "Temperature.h"
// main() runs in its own thread in the OS


Temperature tempSensor(A0,D2,D3);

int main()
{
    int read;
    
    while (true) {
        read = tempSensor.readTemperature(C);
        printf("tempereature is %i \n", read);
        
        ThisThread::sleep_for(5000);
    }
}

