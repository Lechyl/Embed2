#include "Graph.h"



/**
*
*   @author: Long and Nilas
*   @date: 21/1-20
*   @brief: This is the Graph class whereI can init the graph diagram and draw the graph based on 3 diffrent values which has to be updated and run in a endless loop;
*   
*
*/
void Graph::clearDisplay(){
    BSP_LCD_Clear(LCD_COLOR_BLACK);
}
void Graph::initGraph(){
    
    clearDisplay();

    oldXPos = 20;
    oldYPosSound = 250;
    oldYPosLight = 250;
    oldYPosTemp = 250;
    uint8_t *text[30];
    BSP_LCD_SetFont(&Font12);
   
    
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    sprintf((char*)&text,"Sound Graph");
    BSP_LCD_DisplayStringAt(0, 1, (uint8_t*)&text, RIGHT_MODE);

     BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    sprintf((char*)&text,"Light Graph");
    BSP_LCD_DisplayStringAt(0, 12, (uint8_t*)&text, RIGHT_MODE);

    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    sprintf((char*)&text,"Temperature Graph");
    BSP_LCD_DisplayStringAt(0, 24, (uint8_t*)&text, RIGHT_MODE);
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
    

    if(oldXPos >= 450){
        initGraph();
    }
    if(oldXPos == 20){
        oldYPosSound = 250 -soundIn;
        oldYPosLight = 250 - lightIn;
        oldYPosTemp = 250 - tempIn;
        
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