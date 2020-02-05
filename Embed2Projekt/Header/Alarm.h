
#ifndef ALARM_TOKEN
#define ALARM_TOKEN

#include "mbed.h"
class Alarm{

    public:
        Alarm(PinName buzzer);
        bool alarmOn,alarmOff;
        void alarm();
    private:
        PinName _buzzer;
};


#endif