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
//Sound soundSensor(A1);
//LightSensor lightSensor(A2);
SD sd ;
int main()
{
sd.Test();
    
/* 
    Screen* test = new Screen();
    test->LoadingScreen("Nilas og Long", "Work in progress");
    */
    while (true) {
            //BSP_LCD_DisplayStringAt(250,280, (uint8_t *) "Enter",LEFT_MODE);
    }
}

