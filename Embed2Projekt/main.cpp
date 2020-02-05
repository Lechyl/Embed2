#include "mbed.h"
#include "ScreenClass.h"
#include "rtos.h"


Thread ScreenThread;
#include "SD.h"
#include "Temperature.h"
#include "Sound.h"
#include "LightSensor.h"
#include "EthernetClass.h"

// main() runs in its own thread in the OS

//Different sensors
Temperature tempSensor(A0,D2,D3);

Sound* soundSensor = new Sound(A1);

LightSensor lightSensor(A2);

//Enum containing the relevant screen
enum UserLocation location;

//Enum containing the temperature type
enum Type type(C);

//Used to detect touches on the screen
TS_StateTypeDef TS_State;

//Object to get the time via ethernet
Ethernet net;

Sound soundSensor(A1);
//LightSensor lightSensor(A2);
SD sd ;
int main()
{   
    
    //Set the default location
    location = Information;

    //New instance of the screen class. Used to navigate    
    Screen* screen = new Screen(soundSensor);
    //Read the light. Used to make sure it'sday
    lightSensor.readLight();
    if(!lightSensor.isItDay){
        location=Locked;
    }
    //sd.ReadPassword("123456");
/* 
    Screen* test = new Screen();
    test->LoadingScreen("Nilas og Long", "Work in progress");
    */
    float d;
    while (true) {
        d =soundSensor.readSound();
        printf("%f dB \n",d);

        
            //BSP_LCD_DisplayStringAt(250,280, (uint8_t *) "Enter",LEFT_MODE);
    }

    //Get room number
    screen->LoadingScreen("Nilas og Long", "Work in progress");

    while (true) {
        //Change the screen based on location
        switch (location){
            //Case loading
            case 0:
                screen->LoadingScreen("Nilas og Long", "Work in progress");
                break;

            //Case screen information
            case 1:
                screen->ScreenOne(tempSensor.readTemperature(type), lightSensor.readLight(), soundSensor->readSound(), net.getTime());
                break;
            //Case screen load noises
            case 2:
                screen->ScreenTwo();
                break;
            //Case screen locked
            case 3:
                screen->locked();
                break;
            //Default error
            default:
                break;

        }
        //Run while loop checking for touch input
        while(1){
            BSP_TS_GetState(&TS_State);
            if(TS_State.touchDetected){
                switch (location){
                    //Case loading
                    case 0:
                        screen->LoadingScreen("Nilas og Long", "Work in progress");
                        break;

                    //Case screen information
                    case 1:
                        if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 50) && (200 < TS_State.touchY[0] &&  TS_State.touchY[0]< 250)){
                            location = LoudInfo;
                        }
                        break;
                    //Case screen load noises
                    case 2:
                        if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 1150) && (100 < TS_State.touchY[0] &&  TS_State.touchY[0]< 150)){
                            soundSensor->getCounter = 0;
                        }else if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 150) && (200 < TS_State.touchY[0] &&  TS_State.touchY[0]< 250)){
                            location = Information;
                        }
                        break;
                    //Case screen locked
                    case 3:
                        
                        break;
                    //Default error
                    default:
                        break;
                }
            }
        }   
    }
}   
