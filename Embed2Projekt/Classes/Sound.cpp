#include "Sound.h"

/**
*
*   @author: Long and Nilas
*   @date: 21/1-20
*   @brief: this class is used to read sound noises and return it. @Count the number of noises over preset loud sound and check if the noise is the loudest every head and set it to @highScore variable
*   @parameters: @getCounter; @getHighScore;
*/

/// Constructor used to get the PinName from sound sensor
Sound::Sound(PinName pin){
    _soundSensor = pin;
    getCounter = 0;
    getHighScore = 0;
}

/// destructor
Sound::~Sound(){

}

//define class variables


/// Read Sound noises as int values and return it.
int Sound::readSound(){
    AnalogIn soundSensor (_soundSensor);

    int soundValue = soundSensor.read_u16();
    getHighScore = soundValue > getHighScore ? soundValue : getHighScore;
    getCounter = soundValue > 4000 ? getCounter +1: getCounter;
    return soundValue;
}


