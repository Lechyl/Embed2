#include "mbed.h"
#include "ScreenClass.h"
#include "rtos.h"


Thread ScreenThread;
#include "SD.h"
#include "Temperature.h"
#include "Sound.h"
#include "LightSensor.h"

// main() runs in its own thread in the OS


Temperature tempSensor(A0,D2,D3);
Sound soundSensor(A1);
//LightSensor lightSensor(A2);
SD sd ;
int main()
{   
    
    
    
    //sd.ReadPassword("123456");
/* 
    Screen* test = new Screen();
    test->LoadingScreen("Nilas og Long", "Work in progress");
    */
    float d;
    while (true) {
        d =soundSensor.readSound();
        printf("%f dB \n",d);

        wait(0.2);
            //BSP_LCD_DisplayStringAt(250,280, (uint8_t *) "Enter",LEFT_MODE);
    }
}

