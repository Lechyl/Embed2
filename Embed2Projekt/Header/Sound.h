
#ifndef SOUND_TOKEN
#define SOUND_TOKEN

#include "mbed.h"

class Sound{

    private:
        PinName _soundSensor;


    public:
        int getCounter = 0;
        float threshold = 80.0;
        float getHighScore = 0.0;
        Sound(PinName pin);
        ~Sound();
        float readSound();
};


#endif