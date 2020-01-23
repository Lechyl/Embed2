#include "ScreenClass.h"


Screen::Screen(){
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    ChangeColorScheme(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
    if(status != TS_OK){
        ErrorScreen();
    }else{
        LoadingScreen("Long and Nilas Project", "Work in progress");
    }

}

void Screen::GetLocationInfo(){
    
    BSP_LCD_Clear(BSP_LCD_GetBackColor());
    Keyboard();
}

void Screen::ChangeColorScheme(uint32_t backgroundColor, uint32_t textColor){
    BSP_LCD_Clear(backgroundColor);
    BSP_LCD_SetBackColor(backgroundColor);
    BSP_LCD_SetTextColor(textColor);
}

void Screen::ErrorScreen(){
    Screen:ChangeColorScheme(LCD_COLOR_RED, LCD_COLOR_BLACK);

    BSP_LCD_DisplayStringAt(0,0, (uint8_t *)  "An error has occured. Please restart the device" , CENTER_MODE);
}


Screen::~Screen(){

}

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
    GetLocationInfo();

};

void Screen::DrawSquare(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint8_t* text){
    //Get background and text color
    uint32_t backgroundColor = BSP_LCD_GetBackColor();
    uint32_t textColor = BSP_LCD_GetTextColor();

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

void Screen::Keyboard(){
    buttons = new char[13];
    for(int i=0;i <= 9;i++){
        buttons[i] = (char)i;
    }
    buttons[10]='n';buttons[11]=0;buttons[12]='y';
    uint16_t xPos;
    uint16_t yPos;
    for(int i = 0;i < 12;i++){
        xPos = (40*(i%3))+150;
        yPos = 30*(i/3)+150;
        DrawSquare(xPos, yPos,  30,  25, (uint8_t *) "a");
    }    
    while(1){
        BSP_TS_GetState(&TS_State);
        if(TS_State.touchDetected){
            if(150 < TS_State.touchX[0] &&  TS_State.touchX[0]< 180){
                if((150 < TS_State.touchY[0] &&  TS_State.touchY[0]< 175)){
                    text.push_back('1');
                }else  if(180 < TS_State.touchY[0] &&  TS_State.touchY[0]< 205){
                    text.push_back('2');
                }else if (210 < TS_State.touchY[0] &&  TS_State.touchY[0]< 235){
                    text.push_back('3');
                   
                }
            }else if (190 < TS_State.touchX[0] &&  TS_State.touchX[0]< 220){
                if((150 < TS_State.touchY[0] &&  TS_State.touchY[0]< 175)){
                    text.push_back('4');
                }else  if(180 < TS_State.touchY[0] &&  TS_State.touchY[0]< 205){
                    text.push_back('5');
                }else if (210 < TS_State.touchY[0] &&  TS_State.touchY[0]< 235){
                    text.push_back('6');
                }
            }else if(230 < TS_State.touchX[0] &&  TS_State.touchX[0]< 260){
                if((150 < TS_State.touchY[0] &&  TS_State.touchY[0]< 175)){
                    text.push_back('7');
                }else  if(180 < TS_State.touchY[0] &&  TS_State.touchY[0]< 205){
                    text.push_back('8');
                }else if (210 < TS_State.touchY[0] &&  TS_State.touchY[0]< 235){
                    text.push_back('9');
                }
            }else if(270 < TS_State.touchX[0] &&  TS_State.touchX[0]< 300){
                if((150 < TS_State.touchY[0] &&  TS_State.touchY[0]< 175)){
                    text.pop_back()
                }else  if(180 < TS_State.touchY[0] &&  TS_State.touchY[0]< 205){
                    text.push_back('0');
                }else if (210 < TS_State.touchY[0] &&  TS_State.touchY[0]< 235){
                    break;
                }
            }
        }
    }
}