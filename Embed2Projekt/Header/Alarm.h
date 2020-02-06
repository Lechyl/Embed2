
#ifndef ALARM_TOKEN
#define ALARM_TOKEN

#include "mbed.h"



class Alarm{

    public:
        DigitalOut* Buzzer;
        Alarm(PinName pin);
        void alarmOn(),alarmOff();
        bool getTurnOnAlarm();
        
    private:
        
        PinName _buzzer;
        bool turnOnAlarm = false;

};


#endif