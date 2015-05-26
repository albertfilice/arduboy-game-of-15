/* Buttons
    Right Side
    ==========
    B (left button) = A0
    A (right button) = A1

    Left Side
    =========
    Up = 8
    Right = 5
    Down = 10
    Left = 9
*/

#include <SPI.h>
#include "Arduboy.h"

Arduboy display;

void setup()
{
    SPI.begin();
    display.start();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Hi '-'_@");
    display.display();
    delay(1000);
    display.clearDisplay();


}

void loop()
{

}