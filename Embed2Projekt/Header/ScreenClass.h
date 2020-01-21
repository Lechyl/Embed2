#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

class Screen{


    private:
        uint8_t status;
        TS_StateTypeDef TS_State;
    public:
        
        /*
        *
        *
        *
        *
         */
         Screen();
        ~Screen();

        void ChangeColorScheme(uint32_t backgroundColor,uint32_t textColor);

        void ErrorScreen();
        void LoadingScreen(char title[], char subTitle[]);

};  