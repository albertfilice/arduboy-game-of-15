#include <SPI.h>
#include "Arduboy.h"

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Hi");
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

byte tileValue;
byte tileNumber;
byte board[4][4] = {
  {1,2,3,4},
  {5,6,7,8},
  {9,10,11,12},
  {13,14,15,0}
};

void setup()
{
  SPI.begin();
  display.start();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Hi '-'_@");
  display.display();
  delay(400);
  display.clearDisplay();


}



void drawBoard()
{
  // Draw the grid
  display.drawFastVLine(0, 0, 61, 1);
  display.drawFastVLine(15, 0, 61, 1);
  display.drawFastVLine(30, 0, 61, 1);
  display.drawFastVLine(45, 0, 61, 1);
  display.drawFastVLine(60, 0, 61, 1);
  
  display.drawFastHLine(0, 0, 61, 1);
  display.drawFastHLine(0, 15, 61, 1);
  display.drawFastHLine(0, 30, 61, 1);
  display.drawFastHLine(0, 45, 61, 1);
  display.drawFastHLine(0, 60, 61, 1);
  
  
//  updateTile(1, 5);
  display.display();
}

void loop()
{
  drawBoard();
  
  
//  for(byte n = 0; n < 4; n++)
//  {
//    for(byte m = 0; m < 4; m++)
//    {
//      display.setCursor(m*12, n*14);
//      display.print(board[n][m]);
//    }
//  }
//  display.display();
  
//  
//  display.fillRect(1, 1, 14, 14, 1);
//  display.setCursor(5, 4);
//  display.print("1");
//  
//  display.setCursor(20, 4);
//  display.print("2");
//  
//  display.setCursor(35, 4);
//  display.print("3");
//  
//  display.setCursor(50, 4);
//  display.print("4");
//  
//  display.setCursor(5, 20);
//  display.print("5");
//  
//  display.setCursor(20, 20);
//  display.print("6");
//  
//  display.setCursor(35, 20);
//  display.print("7");
//  
//  display.setCursor(50, 20);
//  display.print("8");
//  
//  display.setCursor(5, 35);
//  display.print("9");
//  
//  display.setCursor(20, 35);
//  display.print("10");
//  
//  display.setCursor(35, 35);
//  display.print("11");
//  
//  display.setCursor(50, 35);
//  display.print("12");
//
//  display.setCursor(5, 50);
//  display.print("13");
//
//  display.setCursor(15, 50);
//  display.print("14");
//
//  display.setCursor(35, 50);
//  display.print("15");
//  
//  display.display();

  
}
}
