
#ifndef ALARM_TOKEN
#define ALARM_TOKEN

#include "mbed.h"
class Alarm{

    public:
        Alarm(PinName pin);
        void alarmOn(),alarmOff(),alarmTasks();
        
    private:
        
        PinName _buzzer;
        bool turnOnAlarm = false;

};


#endif