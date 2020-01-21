

#ifndef SOUND_TOKEN
#define SOUND_TOKEN

#include "mbed.h"

class Sound{

    private:
        PinName _soundSensor;


    public:
        int getCounter;
        int getHighScore;
        Sound(PinName pin);
        ~Sound();
        int readSound();
};


#endif