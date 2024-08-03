/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\alexv                                            */
/*    Created:      Sat Nov 11 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "games.h"

using namespace vex;

// Game Selector Variables / Methods
int Game = 1;
bool GameSelected = false;
void GameAdd() { Game++; }
void GameSubtract() { Game--; }
#define MinGames 1
#define MaxGames 2

void GameSelector() {
  Controller1.ButtonRight.pressed(GameAdd);
  Controller1.ButtonLeft.pressed(GameSubtract);

  while (GameSelected == false) {
    // Overflow Protection (Loop selection)
    if (Game > MaxGames) { Game = MinGames; }
    else if (Game < MinGames) { Game = MaxGames; }

    // Reset Brain Screen
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(monoM);
    Brain.Screen.setCursor(1,1);

    // Display Game Graphic
    switch (Game) {
      // Pong
      case 1:
        Brain.Screen.setFont(monoXXL);
        Brain.Screen.setCursor(1,7);
        Brain.Screen.print("PONG");
        Brain.Screen.setPenColor(white);
        Brain.Screen.drawLine(10, 120 + -30 - 30, 10, 120 + -30 + 30);
        Brain.Screen.drawLine(470, 120 + 20 - 30, 470, 120 + 20 + 30);
        Brain.Screen.drawCircle(170, 180, 5, vex::color::white);
      break;
      // Snake
      case 2:
        Brain.Screen.setFont(monoXXL);
        Brain.Screen.setCursor(1,7);
        Brain.Screen.print("Snake");
        int titleX[10] = {190, 200, 210, 220, 230, 240, 240, 240, 250, 260};
        int titleY[10] = {180, 180, 180, 180, 180, 180, 170, 160, 160, 160};
        Brain.Screen.drawCircle(310, 140, 7, red);
        for (int i = 0; i < 10; i++) {
          Brain.Screen.drawRectangle(titleX[i] - 5, titleY[i] - 5, 15, 15, green);
        }
      break;
    }

    // Confirm Game Select
    if (Controller1.ButtonA.pressing()) {
      GameSelected = true;
    }

    // Prevent Resource Overflow
    wait (50, msec);
  }

  // Void the Controller Callbacks
  Controller1.ButtonRight.pressed(NULL);
  Controller1.ButtonLeft.pressed(NULL);

  // Initiate Selected Game
  switch (Game) {
    case 1:
      Pong();
    break;
    case 2:
      Snake();
    break;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  GameSelector();
}
