#include "Alarm.h"

Alarm::Alarm(PinName pin){
    _buzzer = pin;
}

void Alarm::alarmOn(){
    turnOnAlarm = true;

}
void Alarm::alarmOff(){
    turnOnAlarm = false;

}

void Alarm::alarmTasks(){
    DigitalInOut buzzer(_buzzer);
    if(turnOnAlarm){
        buzzer = 1;
    }  
}