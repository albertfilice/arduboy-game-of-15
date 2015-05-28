#include <SPI.h>
#include "Arduboy.h"

Arduboy display;

byte tileValue;
byte tileNumber;
byte selection[1][2] = 
{
  {1,0}
};

byte board[4][4] = 
{
  {10,2,13,4},
  {15,6,7,8},
  {14,1,11,12},
  {3,9,5,0}
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

void updateTile() {
  
}

void getInput() {  
  display.display();
  while(true)
  {
    if(display.pressed(RIGHT_BUTTON))
    {
      if(selection[0][0] < 4)
      {
        selection[0][0]++;
        display.display();
      }
    }
  }
}


void drawBoard()
{
  // Draw the grid
  // Print the vertical lines
  display.drawFastVLine(0, 0, 61, 1);
  display.drawFastVLine(15, 0, 61, 1);
  display.drawFastVLine(30, 0, 61, 1);
  display.drawFastVLine(45, 0, 61, 1);
  display.drawFastVLine(60, 0, 61, 1);
  
  // Print the horizontal lines
  display.drawFastHLine(0, 0, 61, 1);
  display.drawFastHLine(0, 15, 61, 1);
  display.drawFastHLine(0, 30, 61, 1);
  display.drawFastHLine(0, 45, 61, 1);
  display.drawFastHLine(0, 60, 61, 1);
  
  // Highlight the current selection
  display.drawRect((selection[0][0]*15)+1, (selection[0][1]*15)+1, 14, 14, 1); 
  
  // Print the numbers
  for(byte n = 0; n < 4; n++)
  {
    for(byte m = 0; m < 4; m++)
    {
      if(board[n][m] > 9)
      {
        display.setCursor((m*15)+2, (n*15)+4);
      }
      else
      {
        display.setCursor((m*15)+5, (n*15)+4);
      }
      display.print(board[n][m]);
    }
  }
  display.display();
}

void loop()
{
  // Draw the board
  drawBoard();
  
  // Get the input from the user
  getInput();
  
  
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

