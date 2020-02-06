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

//Alarm object
Alarm* alarm = new Alarm(D4);
SD sd;
Screen* screen = new Screen();

//Object to get the time via ethernet
Ethernet net;

//Used to detect touches on the screen
TS_StateTypeDef TS_State;
//Enum containing the relevant screen
enum UserLocation location;

//Enum containing the temperature type
enum Type type(C);


float* rtSoundValue;
float* rtLightValue;
int* rtTempCValue;
int seconds = 0;
bool touches = true;

//Check if unlocked
bool pw=true;

class Graph graph;
Thread screenThread;

void DisplayTime(){
    //screen->DisplayTime(net.GetTime());
    //ThisThread::sleep_for(1000);
}
void realTimeReadings(){
    while(1){
       *rtSoundValue = soundSensor->readSound();
       *rtLightValue = lightSensor.readLight();
       *rtTempCValue = tempSensor.readTemperature(C);


        ///Read the light. Used to make sure it's day/night base on threshold
        lightSensor.threshold = 0.01;
    
        if(lightSensor.isItDay){
            location=Locked;
        }
    }
}
void screenSettings(){

    //Get room number
    screen->LoadingScreen("Nilas og Long", "Work in progress");
}
void getCurrentScreenInfo(){
 
        touches = true;
        if(seconds == 25){
            seconds =0;
        }else{
            seconds++;
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
}
void touchScreen(){
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

            getCurrentScreenInfo();
        }
}


int main()
{        
    //Set the default location
    location = Information;

    //clockThread.start(DisplayTime);    
     //sd.ReadPassword("123456");

    screenSettings();

    /// thread for running all readings from sensors in real time and its logics
    Thread thread1;
    thread1.start(&realTimeReadings);

    /// thread for running touch input in real time
    Thread thread2;
    thread2.start(&touchScreen);


    while (true) {

        ThisThread::sleep_for(40); 
    }
    
}   
