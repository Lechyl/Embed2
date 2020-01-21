#include "ScreenClass.h"


Screen::Screen(){
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    if(status != TS_OK){
        ErrorScreen();
    }else{
        LoadingScreen("Long and Nilas Project", "Work in progress");
    }

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
    BSP_LCD_DisplayStringAt(0, 200, (uint8_t *) title, CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 300, (uint8_t *) title, CENTER_MODE);
};