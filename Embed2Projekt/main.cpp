#include "mbed.h"
#include "ScreenClass.h"
#include "rtos.h"


Thread ScreenThread;
// main() runs in its own thread in the OS
int main()
{
    Screen* test = new Screen();
    test->LoadingScreen("Nilas og Long", "Work in progress");
    while (true) {
            BSP_LCD_DisplayStringAt(250,280, (uint8_t *) "Enter",LEFT_MODE);

    }
}

