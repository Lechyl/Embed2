#include "Alarm.h"

/*
*
*   @author: Long and Nilas
*   @date: 21/1-20
*   @brief: This is the alarm class which will Trigger the alarm when it's dark and the sound is above max.
*   @parameters: @threshold = indikator for when it's night and day in float, @isItDay is a bool variable which check if it's day = true/night = false.
*
 */
Alarm::Alarm(PinName pin){
    _buzzer = pin;
    Buzzer = new DigitalOut(pin);
}

void Alarm::alarmOn(){
    turnOnAlarm = true;

}
void Alarm::alarmOff(){
    turnOnAlarm = false;
    *Buzzer = 0;
}

void Alarm::alarmTasks(){
    
    if(turnOnAlarm){
        *Buzzer = 1;
    }  
}