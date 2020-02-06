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

        BSP_LCD_DrawLine(20, 50 * i, 10, 50 * i);
        
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
                
                BSP_LCD_SetTextColor(LCD_COLOR_RED);
                BSP_LCD_DrawLine(oldXPos, oldYPosSound, oldXPos +1, soundIn);
                oldY = soundIn;
                break;
            case 1:
                BSP_LCD_SetTextColor(LCD_COLOR_RED);
                BSP_LCD_DrawLine(oldXPos, oldY, oldXPos +1, lightIn);
                oldY = soundIn;
                break;
            case 2:
                BSP_LCD_SetTextColor(LCD_COLOR_RED);
                BSP_LCD_DrawLine(oldXPos, oldY, oldXPos +1, tempIn);
                oldY = soundIn;
                break;
        }
    }

    oldX++;
}