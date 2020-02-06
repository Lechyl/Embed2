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

//Graph object to draw graph
class Graph graph;
//Used to detect touches on the screen
TS_StateTypeDef TS_State;
//Enum containing the relevant screen
enum UserLocation location;

//Enum containing the temperature type
enum Type type(C);


float rtSoundValue;
float rtLightValue;
int rtTempCValue;
int seconds = 0;

//Check if unlocked
bool pw=true;

Thread screenThread;

void DisplayTime(){
    //screen->DisplayTime(net.GetTime());
    //ThisThread::sleep_for(1000);
}
void realTimeReadings(){
    while(1){
       rtSoundValue = soundSensor->readSound();
       rtLightValue = lightSensor.readLight();
       rtTempCValue = tempSensor.readTemperature(C);


        ///Read the light. Used to make sure it's day/night base on threshold
        lightSensor.threshold = 0.3;
        printf("sound %f  isitday %i\n",rtSoundValue,lightSensor.isItDay);
        if(!lightSensor.isItDay && rtSoundValue >= soundSensor->threshold){
            location=Locked;
            alarm->alarmOn();
            printf("alarm on!\n");
        }
    }
}
void screenSettings(){

    //Get room number
    screen->LoadingScreen("Nilas og Long", "Work in progress");
}
void getCurrentScreenInfo(){
    while(1){
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
                    if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 100) && (100 < TS_State.touchY[0] &&  TS_State.touchY[0]< 130)){
                        location = LoudInfo;
                    }else if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 100) && (150 < TS_State.touchY[0] &&  TS_State.touchY[0]< 180)){
                        location=Graph;
                        graph.initGraph();
                    }else if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 220) && (200 < TS_State.touchY[0] &&  TS_State.touchY[0]< 230)){
                        location = Location;
                    }
                    break;
                //Case screen load noises
                case 2:
                    if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 100) && (100 < TS_State.touchY[0] &&  TS_State.touchY[0]< 150)){
                        soundSensor->getCounter = 0;
                    }else if((0 < TS_State.touchX[0] &&  TS_State.touchX[0]< 200) && (200 < TS_State.touchY[0] &&  TS_State.touchY[0]< 250)){
                        soundSensor->getCounter = 100;
                        location = Information;
                    }
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
                            
                        }
                    }while(pw);
                    pw=true;
                    seconds=25;                    
                    break;

                //Graph
                case 4:
                    location=Information;
                    break;
                    
                //Default error
                default:
                    break;
            }
        }
        //ThisThread::sleep_for(40);
    }

}
void touchScreen(){
    //Change the screen based on location
    while(1){
            switch (location){
            //Case loading
            case 0:
                screen->LoadingScreen("Nilas og Long", "Work in progress");
                break;

            //Case screen information
            case 1:
            /*
                soundSensor->readSound();
                rtLightValue = lightSensor.readLight();
                rtTempCValue = tempSensor.readTemperature(C); */
                //screen->ScreenOne(tempSensor.readTemperature(C), lightSensor.readLight(), soundSensor->readSound());
                screen->ScreenOne(rtTempCValue, rtLightValue, rtSoundValue);

                break;
            //Case screen load noises
            case 2:
                screen->ScreenTwo(soundSensor->getCounter);
                location=LoudInfo;
                break;
            //Case screen locked
            case 3:
                screen->locked();
                location=Locked;
                break;
            //Case graph
            case 4:
                //screen->graph();
                location=Graph;
                graph.getGraph(rtSoundValue, rtLightValue, rtTempCValue);
                break;
            case 5:
                screen->GetLocationInfo();
                location=Information;
                break;
            //Default error
            default:
                screen->ErrorScreen();
                break;

            }

           // getCurrentScreenInfo();
            ThisThread::sleep_for(1000);

        }
}


int main()
{        
    //Set the default location
    location = Information;

    //clockThread.start(DisplayTime);    
     //sd.ReadPassword("123456");


    /// thread for running all readings from sensors in real time and its logics
    Thread thread1;
    thread1.start(&realTimeReadings);
    screenSettings();

    /// thread for running touch input in real time
    Thread thread2;
    thread2.start(&touchScreen);
    Thread thread3;
    thread3.start(&getCurrentScreenInfo);

    while (true) {

       // ThisThread::sleep_for(40); 
    }
    
}   
