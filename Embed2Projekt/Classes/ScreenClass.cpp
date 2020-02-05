#include "ScreenClass.h"

/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: This class contains all methods used for the screen
*/

/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Constructor for the class
*/
Screen::Screen(){
BSP_LCD_Init();
BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
ChangeColorScheme(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
if(status != TS_OK){
    ErrorScreen();
}
/*

else{
    LoadingScreen("Long and Nilas Project", "Work in progress");
}
*/
}
/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Get room number of the device
*/
void Screen::GetLocationInfo(){
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    Keyboard("Room Number");
}
/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Change the color scheme
*   @param: backgroundColor     The new background color
*   @param: textColor           The new textcolor
*/
void Screen::ChangeColorScheme(uint32_t backgroundColor, uint32_t textColor){
    BSP_LCD_Clear(backgroundColor);
    BSP_LCD_SetBackColor(backgroundColor);
    BSP_LCD_SetTextColor(textColor);
}
/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Error screen in case of an error
*/
void Screen::ErrorScreen(){
    Screen:ChangeColorScheme(LCD_COLOR_RED, LCD_COLOR_BLACK);

    BSP_LCD_DisplayStringAt(0,0, (uint8_t *)  "An error has occured. Please restart the device" , CENTER_MODE);
}

/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Deconstructor
*/
Screen::~Screen(){

}
/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: First screen shown
*   @param: title       Title of the loading screen
*   @param: textColor   Subtitle of the loading screen
*/
void Screen::LoadingScreen(char title[], char subTitle[]){
    BSP_LCD_DisplayStringAt(0,50, (uint8_t *) title,CENTER_MODE);
    BSP_LCD_DisplayStringAt(0,150, (uint8_t *) subTitle,CENTER_MODE);
    BSP_LCD_FillRect(200, 200, 100, 50);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(200,215, (uint8_t *) "Enter",LEFT_MODE);
    while(1){
        BSP_TS_GetState(&TS_State);
        if(TS_State.touchDetected){
            if(( 200 < TS_State.touchY[0] &&  TS_State.touchY[0]< 300)&&(200 < TS_State.touchX[0] &&  TS_State.touchX[0]< 250)){
                break;
            }
        }
    }
    //Chaneg screen to get room number
    GetLocationInfo();

};
/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Draw a square with text inside
*   @param: Xpos    Start point on the x-axis for the square
*   @param: Ypos    Start point on the y-axis for the square
*   @param: Width   Width of the square
*   @param: Height  Height of the square
*   @param: text    Text inside the square
*/
void Screen::DrawSquare(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint8_t* text){
    //Get background and text color
    uint32_t backgroundColor = BSP_LCD_GetBackColor();
    uint32_t textColor = BSP_LCD_GetTextColor();

    //Draw the square
    BSP_LCD_FillRect(Xpos, Ypos, Width, Height);

    //Reverse them to able to draw squares, and write in them
    BSP_LCD_SetBackColor(textColor);
    BSP_LCD_SetTextColor(backgroundColor);
    //Draw the square and write the text
    BSP_LCD_DisplayStringAt(Xpos, Ypos, text, LEFT_MODE);    
    //Reset the colorScheme
    BSP_LCD_SetBackColor(backgroundColor);
    BSP_LCD_SetTextColor(textColor);
}


void Screen::Keyboard(string inputText){
    text.clear();
    char button [2];
    char * buttons = new char[4];
    buttons[0]='n';buttons[1]='0';buttons[2]='y';
    uint16_t xPos;
    uint16_t yPos;
    for(int i = 0;i < 9;i++){
        xPos = (40*(i%3))+150;
        yPos = 30*(i/3)+150;
        sprintf(button,"%d",i+1);
        DrawSquare(xPos, yPos,  30,  25, (uint8_t *)  button );
    }

    int i = 9;
    DrawSquare((40*(i%3))+150, 30*(i/3)+150,  30,  25, (uint8_t *)  "n" );

    i++;
    sprintf(button,"%d",0);
    DrawSquare((40*(i%3))+150, 30*(i/3)+150,  30,  25, (uint8_t *)  button );
    i++;
    DrawSquare((40*(i%3))+150, 30*(i/3)+150,  30,  25, (uint8_t *)  "y" );
    BSP_LCD_DisplayStringAt(100, LINE(5), (uint8_t *) "Lokale: ",LEFT_MODE);
    ThisThread::sleep_for(100);

    while(1){
        BSP_TS_GetState(&TS_State);
        if(TS_State.touchDetected){
            if(150 < TS_State.touchX[0] &&  TS_State.touchX[0]< 180){
                if((150 < TS_State.touchX[0] &&  TS_State.touchY[0]< 175)){
                    text.push_back('1');
                }else  if(180 < TS_State.touchY[0] &&  TS_State.touchY[0]< 205){
                    text.push_back('4');
                }else if (210 < TS_State.touchY[0] &&  TS_State.touchY[0]< 235){
                    text.push_back('7');                   
                }else if((240 < TS_State.touchY[0] &&  TS_State.touchY[0]< 265)){
                    text.pop_back();
                }
            }else if (190 < TS_State.touchX[0] &&  TS_State.touchX[0]< 220){
                if((150 < TS_State.touchY[0] &&  TS_State.touchY[0]< 175)){
                    text.push_back('2');
                }else  if(180 < TS_State.touchY[0] &&  TS_State.touchY[0]< 205){
                    text.push_back('5');
                }else if (210 < TS_State.touchY[0] &&  TS_State.touchY[0]< 235){
                    text.push_back('8');
                }else if((240 < TS_State.touchY[0] &&  TS_State.touchY[0]< 265)){
                    text.push_back('0');
                }
            }else if(230 < TS_State.touchX[0] &&  TS_State.touchX[0]< 260){
                if((150 < TS_State.touchY[0] &&  TS_State.touchY[0]< 175)){
                    text.push_back('3');
                }else  if(180 < TS_State.touchY[0] &&  TS_State.touchY[0]< 205){
                    text.push_back('6');
                }else if (210 < TS_State.touchY[0] &&  TS_State.touchY[0]< 235){
                    text.push_back('9');
                }else if((240 < TS_State.touchY[0] &&  TS_State.touchY[0]< 265)){
                    break;
                }
            }
            BSP_LCD_DisplayStringAt(100, LINE(5), (uint8_t *) "                                    ", LEFT_MODE);
            BSP_LCD_DisplayStringAt(100, LINE(5), (uint8_t *) (inputText+ " "+text).c_str(), LEFT_MODE);
            ThisThread::sleep_for(500);
        }
    }
    BSP_LCD_Clear(LCD_COLOR_WHITE);
}

/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Screen containing sensor information and time
*   @param: temperature    Temperature in the room
*   @param: light          Checks if the light is on
*   @param: sound          Display sound in db
*   @param: time           Timestamp     since 1. January 1970 in seconds

*/
void Screen::ScreenOne(int temperature, float light, float sound, time_t* time){
    char stringValues[20];
    BSP_LCD_DisplayStringAt(0, LINE(0  ), (uint8_t *) ("Lokale: "+text).c_str() , LEFT_MODE);
    sprintf(stringValues, "Temperatur: %d",temperature);
    BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *) stringValues , LEFT_MODE);
    sprintf(stringValues, "Light: %f.2f",light);
    BSP_LCD_DisplayStringAt(0, LINE(4), (uint8_t *) stringValues , LEFT_MODE);
    sprintf(stringValues, "Sound: %f.2f",sound);
    BSP_LCD_DisplayStringAt(0, LINE(6), (uint8_t *) stringValues , LEFT_MODE);
    sprintf(stringValues, "Time: %s",ctime(time));
    BSP_LCD_DisplayStringAt(0, LINE(8), (uint8_t *) stringValues , LEFT_MODE);
    DrawSquare( 0, 200, 50,  50, (uint8_t *) "Loud noise");
}



/**
*
*   @author:  Nilas
*   @date: 21/1-20
*   @brief: Screen containing the amount of high noise sounds
*   @param: counter     Amount of times a high noise was heard
*/
void Screen::ScreenTwo(int counter){
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    char stringValues[20];
    sprintf(stringValues, "Loud noises: %d",counter);
    BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *) stringValues , LEFT_MODE);

    DrawSquare( 0, 100, 50,  50, (uint8_t *) "Reset");

    DrawSquare( 0, 200, 50,  50, (uint8_t *) "Information");

}

/*
Screen 3
*/
