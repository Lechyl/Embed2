#include "mbed.h"
#include "ScreenClass.h"

// main() runs in its own thread in the OS
int main()
{
    Screen* test = new Screen();

    while (true) {
            BSP_LCD_DisplayStringAt(250,280, (uint8_t *) "Enter",LEFT_MODE);

    }
}

