#include <SPI.h>
#include "Arduboy.h"

Arduboy arduboy;

byte tileValue;
byte tileNumber;
boolean logging = true;
// up = 1; right = 2; down = 3; left = 4; a = 5; b = 6;
byte lastButton;
byte selection[1][2] = 
{
  {0,0}
};
byte board[4][4] = 
{
  {10,13,0,4},
  {15,6,7,8},
  {14,1,11,12},
  {3,9,5,2}
};

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  arduboy.start();
  arduboy.setTextSize(1);
  arduboy.setCursor(0, 0);
  arduboy.print("Hi '-'_@");
  arduboy.display();
  delay(400);
  arduboy.clearDisplay();


}

void nudgeTile() {
  Serial.println("Selection x");
  Serial.println(selection[0][0]);
  Serial.println("Selection y");
  Serial.println(selection[0][1]);
  Serial.println("----------------------");
  // Tile is not on bottom edge, see if it can be slid down
  if(selection[0][1] != 3)
  {
    Serial.println("Square below is:");
    // Look at the square below, see if it's zero
    Serial.println(board[selection[0][1]+1][selection[0][0]]);
    if(board[selection[0][1]+1][selection[0][0]] == 0)
    {
      // If the square below is zero, set it to the same value as the square above...
      board[selection[0][1]+1][selection[0][0]] = board[selection[0][1]][selection[0][0]];
      // ...then set the tile above to zero
      board[selection[0][1]][selection[0][0]] = 0;
      return;
    }
  }    
  
  // Tile is not on right edge, see if it can be slid to the right
  if(selection[0][0] != 3)
  {
    Serial.println("Square to the right is:");
    // Look at the square to the right, see if it's zero
    Serial.println(board[selection[0][1]][selection[0][0]+1]);
    if(board[selection[0][1]][selection[0][0]+1] == 0)
    {
      // If the square to the right is zero, set it to the same value as the square to the left...
      board[selection[0][1]][selection[0][0]+1] = board[selection[0][1]][selection[0][0]];
      // ...then set the tile to the left to zero
      board[selection[0][1]][selection[0][0]] = 0;
      return;
    }
  }
  
  // Tile is not on top edge, see if it can be slid up
  if(selection[0][1] != 0)
  {
    Serial.println("Square above is:");
    // Look at the square above, see if it's zero
    Serial.println(board[selection[0][1]-1][selection[0][0]]);
    if(board[selection[0][1]-1][selection[0][0]] == 0)
    {
      // If the square above is zero, set it to the same value as the square below...
      board[selection[0][1]-1][selection[0][0]] = board[selection[0][1]][selection[0][0]];
      // ...then set the tile below to zero
      board[selection[0][1]][selection[0][0]] = 0;
      return;
    }
  }    
  
  // Tile is not on the left edge, see if it can be slid to the left
  if(selection[0][0] != 0)
  {
    Serial.println("Square to the left is:");
    // Look at the square to the left, see if it's zero
    Serial.println(board[selection[0][1]][selection[0][0]-1]);
    if(board[selection[0][1]][selection[0][0]-1] == 0)
    {
      // If the square to the left is zero, set it to the same value as the square to the right...
      board[selection[0][1]][selection[0][0]-1] = board[selection[0][1]][selection[0][0]];
      // ...then set the tile to the right to zero
      board[selection[0][1]][selection[0][0]] = 0;
      return;
    }
  }
}

void getInput() {
  while(true)
  {
    if(arduboy.pressed(UP_BUTTON))
    {
      if(lastButton != 1)
      {
        // Top edge is 0 so make sure the selection isn't on the edge before incrementing
        if(selection[0][1] > 0)
        {
          // Deincrement and redraw the board, which will redraw the outline
          selection[0][1]--;
          drawBoard();
        }
        // Set the button as the last pressed
        lastButton = 1;
      }
    }
    else if(arduboy.pressed(RIGHT_BUTTON))
    {
      if(lastButton != 2)
      {
        // Right edge is 3 so make sure the selection isn't on the edge before incrementing
        if(selection[0][0] < 3)
        {
          // Increment and redraw the board, which will redraw the outline
          selection[0][0]++;
          drawBoard();
        }
        // Set the button as the last pressed
        lastButton = 2;
      }
    }
    else if(arduboy.pressed(DOWN_BUTTON))
    {
      if(lastButton != 3)
      {
        // Bottom edge is 3 so make sure the selection isn't on the edge before incrementing
        if(selection[0][1] < 3)
        {
          // Ieincrement and redraw the board, which will redraw the outline
          selection[0][1]++;
          drawBoard();
        }
        // Set the button as the last pressed
        lastButton = 3;
      }
    }
    else if(arduboy.pressed(LEFT_BUTTON))
    {
      if(lastButton != 4)
      {
        // Left edge is 0 so make sure the selection isn't on the edge before incrementing
        if(selection[0][0] > 0)
        {
          // Deincrement and redraw the board, which will redraw the outline
          selection[0][0]--;
          drawBoard();
        }
        // Set the button as the last pressed
        lastButton = 4;
      }
    }
    else if(arduboy.pressed(A_BUTTON))
    {
      if(lastButton != 5)
      {
        nudgeTile();
        drawBoard();
        lastButton = 5;
      }
    }
    else
    {
      // No buttons are being pressed
      lastButton = 0;
    }
    delay(15);
  }
}


void drawBoard()
{
  // Clear the display
  arduboy.clearDisplay();
  
  // Draw the grid
  // Print the vertical lines
  arduboy.drawFastVLine(0, 0, 61, 1);
  arduboy.drawFastVLine(15, 0, 61, 1);
  arduboy.drawFastVLine(30, 0, 61, 1);
  arduboy.drawFastVLine(45, 0, 61, 1);
  arduboy.drawFastVLine(60, 0, 61, 1);
  
  // Print the horizontal lines
  arduboy.drawFastHLine(0, 0, 61, 1);
  arduboy.drawFastHLine(0, 15, 61, 1);
  arduboy.drawFastHLine(0, 30, 61, 1);
  arduboy.drawFastHLine(0, 45, 61, 1);
  arduboy.drawFastHLine(0, 60, 61, 1);
  
//  // Draw the selection if necessary
//  if(selection[0][0] < 4 && selection[0][1] < 4)
//  {
//    arduboy.fillRect((selection[0][0]*15)+1, (selection[0][1]*15)+1, 14, 14, 1);
//  }
  
  // Draw the outline for user selection
//  // If the outline passes over the selection draw it inverse so you an see
//  if(selection[0][0] == outline[0][0] && selection[0][1] == outline[0][1])
//  {
//    arduboy.drawRect((outline[0][0]*15)+1, (outline[0][1]*15)+1, 14, 14, 0);
//  }
//  else
//  {
//    arduboy.drawRect((outline[0][0]*15)+1, (outline[0][1]*15)+1, 14, 14, 1); 
//  }
  arduboy.drawRect((selection[0][0]*15)+1, (selection[0][1]*15)+1, 14, 14, 1);
  
  // Print the numbers
  for(byte n = 0; n < 4; n++)
  {
    for(byte m = 0; m < 4; m++)
    {
      if(board[n][m] > 9)
      {
        arduboy.setCursor((m*15)+2, (n*15)+4);
      }
      else
      {
        arduboy.setCursor((m*15)+5, (n*15)+4);
      }
      if(board[n][m] != 0)
      {
        arduboy.print(board[n][m]);
      }
    }
  }
  if(logging)
  {
    arduboy.setCursor(75, 5);
    arduboy.print(selection[0][0]);
    arduboy.setCursor(85, 5);
    arduboy.print(selection[0][1]);
    arduboy.setCursor(75, 15);
    arduboy.print("last");
    arduboy.setCursor(100, 15);
    arduboy.print(lastButton);
  }
  arduboy.display();
}

void loop()
{
  // Draw the board
  drawBoard();
  
  // Get the input from the user
  getInput();  
}

