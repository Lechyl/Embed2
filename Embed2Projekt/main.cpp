#include "mbed.h"
#include "ScreenClass.h"
#include "rtos.h"


Thread ScreenThread;

#include "Temperature.h"
#include "Sound.h"
#include "LightSensor.h"

// main() runs in its own thread in the OS


Temperature tempSensor(A0,D2,D3);

Sound* soundSensor = new Sound(A1);

enum UserLocation location;

enum Type type(C);

LightSensor lightSensor(A2);

TS_StateTypeDef TS_State;

int main()
{
    location = Information;
    Screen* screen = new Screen(soundSensor);

    lightSensor.readLight();
//    if(!lightSensor.isItDay);

    screen->LoadingScreen("Nilas og Long", "Work in progress");

    while (true) {
        //Get light and update isItDay

        //Load screen based on UserLocation
//enum UserLocation{Loading = 0, Information = 1, LoudInfo=2, Locked = 3};

        switch (location){
            //Case loading
            case 0:
                screen->LoadingScreen("Nilas og Long", "Work in progress");
                break;

            //Case screen information
            case 1:
                screen->ScreenOne(tempSensor.readTemperature(type), lightSensor.readLight(), soundSensor->readSound());
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
