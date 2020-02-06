#include "mbed.h"
#include "ScreenClass.h"
#include "rtos.h"



Thread ScreenThread;
#include "SD.h"
#include "Temperature.h"
#include "Sound.h"
#include "LightSensor.h"
#include "EthernetClass.h"
#include "Alarm.h"
#include "Graph.h"
// main() runs in its own thread in the OS



//Different sensors
Temperature tempSensor(A0,D2,D3);

Thread clockThread;

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

//Alarm object
Alarm* alarm = new Alarm(D4);

//Sound soundSensor(A1);
//LightSensor lightSensor(A2);
SD sd ;

Screen* screen = new Screen();

Thread screenThread;

void DisplayTime(){
    screen->DisplayTime(net.GetTime());
    ThisThread::sleep_for(1000);
}

Graph graph;
int main()
{   

    int seconds = 0;
    //clockThread.start(DisplayTime);    
     //sd.ReadPassword("123456");
    bool touches = true;
    //Set the default location
    location = Information;
    lightSensor.threshold = 0.01;
    //New instance of the screen class. Used to navigate    
    //Read the light. Used to make sure it'sday
    lightSensor.readLight();
    
    
    if(lightSensor.isItDay){
        location=Locked;
    }
    
    
    //Check if unlocked
    bool pw=true;


    //Get room number
    screen->LoadingScreen("Nilas og Long", "Work in progress");

    while (true) {
        touches = true;
        if(seconds == 25){
            seconds =0;
        }else{
            seconds++;
        }
        //Change the screen based on location
        if(seconds == 0){
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
                screen->ScreenTwo(soundSensor->getCounter);
                break;
            //Case screen locked
            case 3:
                screen->locked();
                break;
            //Case graph
            case 4:
                //screen->graph();
                break;
            //Default error
            default:
                BSP_LCD_DisplayStringAtLine(LINE(2), (uint8_t *) "Error");
                break;

            }
        }
        
        //Run while loop checking for touch input
        BSP_TS_GetState(&TS_State);
        if(TS_State.touchDetected){
            switch (location){
                //Case loading
                case 0:
                    screen->LoadingScreen("Nilas og Long", "Work in progress");
                    break;

                //Case screen information
                case 1:
                    if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 100) && (200 < TS_State.touchY[0] &&  TS_State.touchY[0]< 250)){
                        location = LoudInfo;
                    }else if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 100) && (300 < TS_State.touchY[0] &&  TS_State.touchY[0]< 350))
                    seconds=25;
                    break;
                //Case screen load noises
                case 2:
                    if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 100) && (100 < TS_State.touchY[0] &&  TS_State.touchY[0]< 150)){
                        soundSensor->getCounter = 0;
                        seconds=25;
                    }else if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 200) && (200 < TS_State.touchY[0] &&  TS_State.touchY[0]< 250)){
                        location = Information;
                        seconds = 25;
                    }
                    touches=false;
                    break;
                //Case screen locked
                case 3:
                    do{
                        screen->Keyboard("Password");
                        if(sd.ReadPassword(screen->text)){
                            location=Information;
                            alarm->alarmOff();
                            pw=false;
                        }else{
                            alarm->alarmOn();
                            alarm->alarmTasks();
                        }
                    }while(pw);
                    pw=true;
                    seconds=25;                    
                    break;

                //Graph
                case 4:
                    break;
                    
                //Default error
                default:
                    break;
            }
        }
        ThisThread::sleep_for(40); 
    }
    
}   
