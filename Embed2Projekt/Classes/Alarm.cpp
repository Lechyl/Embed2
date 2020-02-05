#include "Alarm.h"

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