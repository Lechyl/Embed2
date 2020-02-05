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

}

/// destructor
Sound::~Sound(){

}

//define class variables


float Sound::readSound(){
    AnalogIn soundSensor (_soundSensor);

    /// Sample Sound to get a more accurate sound value 
    /// https://electronics.stackexchange.com/questions/96205/how-to-convert-volts-in-db-spl?fbclid=IwAR1g52qr6Wfldj5vlB3zHOJC6dMW5-Ycucwy1_4_UExytM3taPdswdH45rQ
    float dB;
    for(int i = 0;i < 16;i++){

    /// 3.3 is the voltage being measured, and sample the reference level/Voltage being measured
       dB += soundSensor.read();
        
    }
    
    dB = dB/16;
    dB = 3.3/dB;

    dB = 20 * log(dB);
    
    if(dB <= 0)
        dB = 0;
    

    getHighScore = dB > getHighScore ? dB : getHighScore;
    getCounter = dB > 80 ? getCounter +1: getCounter;
    return dB;
}


