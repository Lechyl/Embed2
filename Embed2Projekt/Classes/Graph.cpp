#include "Graph.h"



void Graph::clearDisplay(){
    BSP_LCD_Clear(LCD_COLOR_BLACK);
}
void Graph::initGraph(){
    
    clearDisplay();
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    /// Draw the Graph Diagram
    
    // X Line
    BSP_LCD_DrawLine(20, 40, 450, 40);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    // Y Line
    BSP_LCD_DrawLine(20, 40, 20, 250);
    for(int i = 1;i < 4;i++){

        BSP_LCD_DrawLine(20, 50 * i + 40, 10, 50 * i + 40);
        
    }
}   
void Graph::getGraph(int soundIn,int lightIn,int tempIn){
    

    if(oldXPos >= 450){
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
                soundIn +=40;
                BSP_LCD_SetTextColor(LCD_COLOR_RED);
                BSP_LCD_DrawLine(oldXPos, oldYPosSound, oldXPos +1, soundIn);
                oldYPosSound = soundIn;
                break;
            case 1:
                lightIn +=40;

                BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
                BSP_LCD_DrawLine(oldXPos, oldYPosLight, oldXPos +1, lightIn);
                oldYPosLight = lightIn;
                break;
            case 2:
                tempIn +=40;

                BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
                BSP_LCD_DrawLine(oldXPos, oldYPosTemp, oldXPos +1,tempIn);
                oldYPosTemp = tempIn;
                break;
        }
    }
    oldXPos++;
}