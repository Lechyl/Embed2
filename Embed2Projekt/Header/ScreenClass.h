#ifndef ScreenClass_Nilas
#define ScreenClass_Nilas

#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include<string> // for string class
#include "Sound.h"

enum UserLocation{Loading = 0, Information = 1, LoudInfo=2, Locked = 3, Graph=4, Location=5};

class Screen{


    private:
        uint8_t xLength;
        uint8_t yLength;
        uint8_t status;
        char* buttons;
        string room;
        string building;


    public:
        TS_StateTypeDef TS_State;
        string text; 

         Screen();
        ~Screen();

        void ChangeColorScheme(uint32_t backgroundColor,uint32_t textColor);

        void ErrorScreen();
        void LoadingScreen(char title[], char subTitle[]);


        void DrawSquare(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint8_t* text);

        void GetLocationInfo();

        void Keyboard(string inputText);

        void ScreenOne(int temperature, float light, float sound,UserLocation location);
        void ScreenTwo(int counter, UserLocation location, float highScore);

        void DisplayTime(char* time);

        void locked(UserLocation location);

};  
#endif