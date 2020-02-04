#ifndef ScreenClass_Nilas
#define ScreenClass_Nilas

#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include<string> // for string class
#include "Sound.h"

enum UserLocation{Loading = 0, Information = 1, LoudInfo=2, Locked = 3};

class Screen{


    private:
        uint8_t xLength;
        uint8_t yLength;
        uint8_t status;
        char* buttons;
        Sound* _sound;


    public:
        TS_StateTypeDef TS_State;
        string text; 
        /*
        *
        *
        *
        *
         */
         Screen(Sound* sound);
        ~Screen();

        void ChangeColorScheme(uint32_t backgroundColor,uint32_t textColor);

        void ErrorScreen();
        void LoadingScreen(char title[], char subTitle[]);


        void DrawSquare(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint8_t* text);

        void GetLocationInfo();
        void Keyboard();

        void ScreenOne(int temperature, float light, float sound);
        //void ScreenTwo(Sound* sound);
        void ScreenTwo();

        void locked();

};  
#endif