#ifndef GRAPH_TOKEN
#define GRAPH_TOKEN

#include "Graph.h"

#include "stm32746g_discovery_lcd.h"

class Graph{

    private:
        int oldYPosSound,oldYPosLight,oldYPosTemp = 40;
        int oldXPos = 20;

        void clearDisplay();
        
    public:
        void initGraph();
       void getGraph(int soundIn,int lightIn,int tempIn);
};

#endif