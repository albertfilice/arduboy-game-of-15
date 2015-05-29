#include <SPI.h>
#include "Arduboy.h"

Arduboy arduboy;

byte tileValue;
byte tileNumber;
boolean logging = false;
byte lastButton;  // up = 1; right = 2; down = 3; left = 4; a = 5; b = 6;
byte selection[1][2] =  // [0][0] = y, [0][1] = x
{
  {0,0}
};
byte board[4][4] = 
{
  {1,2,3,4},
  {5,6,7,8},
  {9,10,11,12},
  {13,14,0,15}
};
byte boardComplete[4][4] =
{
  {1,2,3,4},
  {5,6,7,8},
  {9,10,11,12},
  {13,14,15,0}
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

void endGame()
{
  while(true)
  {
    arduboy.clearDisplay();
    arduboy.setCursor(30, 20);
    arduboy.print("You Win");
    arduboy.display();
  }
}

void checkBoard()
{
  // Check to see if the latest move won the game
  byte count = 1;
  for(byte h = 0; h < 4; h++)
  {
    for(byte i = 0; i < 4; i++)
    {
      if(board[h][i] != count)
      {
        return;
      }
      count++;
      if(count == 15)
      {
        endGame();
      }
    }
  }
}

void nudgeRandomAdjacent()
{
  if(logging)
  {
    Serial.println("Nudging random adjacent");
    delay(5000);
  }
  byte choices[4];
  byte choiceCount = 0;
  if(selection[0][0] > 0 && selection[0][0] < 3 && selection[0][1] > 0 && selection[0][1] < 3)
  {
    if(logging)
    {
      Serial.println("Selection in middle, not on edge");
      delay(5000);
    }
    choices[0] = 1;
    choices[1] = 2;
    choices[2] = 3;
    choices[3] = 4;
    choiceCount = 4;
  }
  else
  {
    if(logging)
    {
      Serial.println("Selection on edge");
      delay(5000);
    }
    // Tile is not on top edge
    if(selection[0][1] != 0)
    {
      if(logging) { Serial.println("Up"); }
      choices[choiceCount] = 1;
      choiceCount++;
    }
    // Tile is not on bottom edge
    if(selection[0][1] != 3)
    {
      if(logging) { Serial.println("Down"); }
      choices[choiceCount] = 3;
      choiceCount++;
    }
    // Tile is not on the right edge
    if(selection[0][0] != 3)
    {
      if(logging) { Serial.println("Right"); }
      choices[choiceCount] = 2;
      choiceCount++;
    }
    // Tile is not on left edge
    if(selection[0][0] != 0)
    {
      if(logging) { Serial.println("Left"); }
      choices[choiceCount] = 4;
      choiceCount++;
    } 
    if(logging)
    {
      Serial.println("^^^^^^^-------Possibilities!");
      delay(5000);
    }
  }
  // Pick a random value from choices array
  if(logging)
  {
    Serial.println("Picking random from count of:");
    Serial.println(choiceCount);
    delay(5000);
  }
  switch (choices[random(choiceCount)])
  {
    case 1:
      if(logging)
      {
        Serial.println("Random choice was 1, up");
        delay(5000);
      }
      selection[0][1]--;
      if(logging)
      {
        drawBoard();
        Serial.println("Should have moved up");
        delay(5000);
        Serial.println("Nudging");
      }
      nudgeTile();
      drawBoard();
      break;
    case 2:
      if(logging)
      {
        Serial.println("Random choice was 2, right");
        delay(5000);
      }
      selection[0][0]++;
      if(logging)
      {
        drawBoard();
        Serial.println("Should have moved right");
        delay(5000);
        Serial.println("Nudging");
      }
      nudgeTile();
      drawBoard();
      break;
    case 3:
      if(logging)
      {
        Serial.println("Random choice was 3, down");
        delay(5000);
      }
      selection[0][1]++;
      if(logging)
      {
        drawBoard();
        Serial.println("Should have moved down");
        delay(5000);
        Serial.println("Nudging");
      }
      nudgeTile();
      drawBoard();
      break;
    case 4:
      if(logging)
      {
        Serial.println("Random choice was 4, left");
        delay(5000);
      }
      selection[0][0]--;
      if(logging)
      {
        drawBoard();
        Serial.println("Should have moved left");
        delay(5000);
        Serial.println("Nudging");
      }
      nudgeTile();
      drawBoard();
      break;
  }
}

void scrambleBoard()
{
  // Scramble 100 times
  for(int i = 0; i < 500; i++)
  {
    if(logging)
    {
      Serial.println("Scramble!!!!!");
      Serial.println(i);
      Serial.println("==");
      delay(1000);
    }
    // Loop over the board to and select the empty square
    for(byte m = 0; m < 4; m++)
    {
      for(byte n = 0; n < 4; n++)
      {
        if(board[m][n] == 0)
        {
          selection[0][0] = n;
          selection[0][1] = m;
          if(logging)
          {
            drawBoard();
            Serial.println("Found empty square");
            delay(1000);
          }
        }
      }
    }
    nudgeRandomAdjacent();
    delay(10);
  }
}

void nudgeTile() 
{
  if(logging)
  {
    Serial.println("Selection x");
    Serial.println(selection[0][0]);
    Serial.println("Selection y");
    Serial.println(selection[0][1]);
    Serial.println("----------------------");
  }
  // Tile is not on bottom edge, see if it can be slid down
  if(selection[0][1] != 3)
  {
    if(logging)
    {
      Serial.println("Square below is:");
      Serial.println(board[selection[0][1]+1][selection[0][0]]);
    }
    // Look at the square below, see if it's zero
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
    if(logging)
    {
      Serial.println("Square to the right is:");
      Serial.println(board[selection[0][1]][selection[0][0]+1]);
    }
    // Look at the square to the right, see if it's zero
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
    if(logging)
    {
      Serial.println("Square above is:");
      Serial.println(board[selection[0][1]-1][selection[0][0]]);
    }
    // Look at the square above, see if it's zero
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
    if(logging)
    {
      Serial.println("Square to the left is:");
      Serial.println(board[selection[0][1]][selection[0][0]-1]);
    }
    // Look at the square to the left, see if it's zero
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

void play() {
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
        checkBoard();
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
  
  // Draw the outline for user selection
  arduboy.drawRect((selection[0][0]*15)+1, (selection[0][1]*15)+1, 14, 14, 1);
  
  // Print the numbers
  for(byte n = 0; n < 4; n++)
  {
    for(byte m = 0; m < 4; m++)
    {
      // Each character is 6x8 pixels so place them accordingly 
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
  
  // Scramble the board
  scrambleBoard();
  
  // Get the input from the user
  play(); 
}

