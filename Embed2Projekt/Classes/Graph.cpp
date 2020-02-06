#include "Graph.h"



void Graph::clearDisplay(){
    BSP_LCD_Clear(LCD_COLOR_BLACK);
}
void Graph::initGraph(){
    
    clearDisplay();
    uint8_t *text[30];
    BSP_LCD_SetFont(&Font12);
   
    
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    sprintf((char*)&text,"Sound Graph");
    BSP_LCD_DisplayStringAt(470, 260, (uint8_t*)&text, LEFT_MODE);

     BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    sprintf((char*)&text,"Light Graph");
    BSP_LCD_DisplayStringAt(450, 260, (uint8_t*)&text, LEFT_MODE);

    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    sprintf((char*)&text,"Temperature Graph");
    BSP_LCD_DisplayStringAt(430, 260, (uint8_t*)&text, LEFT_MODE);
    /// Draw the Graph Diagram
    
    /// X Line
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_DrawLine(20, 250, 450, 250);
    
    /// Y Line
    BSP_LCD_DrawLine(20, 40, 20, 250);
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);

    /// draw graph side lines at each 10th place.
    for(int i = 1;i < 10;i++){

        BSP_LCD_DrawLine(20,250 - 10 * i, 10, 250 - 10 * i);
        
    }
}   
void Graph::getGraph(int soundIn,int lightIn,int tempIn){
    

    if(oldXPos >= 40){
        initGraph();
        oldXPos = 20;
        oldYPosSound = 40;
        oldYPosLight = 40;
        oldYPosTemp = 40;
    }

    ///Draw graph
    for(int i = 0;i < 3;i++){
        switch(i){
            case 0:
                soundIn =250 - soundIn;
                BSP_LCD_SetTextColor(LCD_COLOR_RED);
                BSP_LCD_DrawLine(oldXPos, oldYPosSound, oldXPos +1, soundIn);
                oldYPosSound = soundIn;
                break;
            case 1:
                lightIn =250 - lightIn;

                BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
                BSP_LCD_DrawLine(oldXPos, oldYPosLight, oldXPos +1, lightIn);
                oldYPosLight = lightIn;
                break;
            case 2:
                tempIn =250 - tempIn;

                BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
                BSP_LCD_DrawLine(oldXPos, oldYPosTemp, oldXPos +1,tempIn);
                oldYPosTemp = tempIn;
                break;
        }
    }
    oldXPos++;
}