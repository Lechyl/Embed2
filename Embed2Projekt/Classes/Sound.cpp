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

   
    float rms;
    /// dB Equation Source at = https://electronics.stackexchange.com/questions/96205/how-to-convert-volts-in-db-spl?fbclid=IwAR1g52qr6Wfldj5vlB3zHOJC6dMW5-Ycucwy1_4_UExytM3taPdswdH45rQ
    /// RMS Source at = http://mathworld.wolfram.com/Root-Mean-Square.html
    /// RMS is a equation for average voltage waveform being read.
    /// Sample Sound to get a more accurate sound value     

    /// Equation for getting the average rms
    /// Sample sound 16 times in a second
    for(int i = 0;i < 16;i++){

       float read = soundSensor.read(); 
       rms += read * read;
       wait(0.0625);
        
    }
    rms = rms/16;
    rms = sqrt(rms);
 
    /// 3.3 is the input voltage being measured, and rms the reference level/Voltage being measured
    ///Equation for converting Voltage to dB
    //printf("read %.2f \n",rms);
    float dB = 20 * log(3.3/rms);
    
    if(dB <= 0)
        dB = 0;
    

    getHighScore = dB > getHighScore ? dB : getHighScore;

    getCounter = dB > 80 ? getCounter +1: getCounter;
    return dB;
}


