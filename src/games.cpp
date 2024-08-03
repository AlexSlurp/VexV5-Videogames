/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       games.h                                                   */
/*    Author:       Alex Vansen (Fun Programmer)                              */
/*    Created:      Sat Nov 11 2023 - Sat Nov 18 2023                         */
/*    Description:  Contains all the video games I've made                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

void Pong() {
  // Set initial paddle positions and scoring system
  int leftPaddlePosition = 0;
  int rightPaddlePosition = 0;
  int leftPaddleScore = 0;
  int rightPaddleScore = 0;
  double PaddleSensitivity = 0.1; // Customizable
  int Round = 1;

  // Set initial ball position and velocity
  int ballX = 160;
  int ballY = 120;
  int ballVelocityX = 3;
  int ballVelocityY = 2;

  // Set initial speed increase parameters
  int speedIncreaseInterval = 5000; // Increase speed every 5 seconds
  int lastSpeedIncreaseTime = Brain.timer(msec);

  // Title Screen
  Brain.Screen.setFont(monoXXL);
  Brain.Screen.setCursor(1,7);
  Brain.Screen.print("PONG");
    // Subtitle
  Brain.Screen.setFont(monoS);
  Brain.Screen.setCursor(5,25);
  Brain.Screen.print("- Press A to play -");
    // Graphic
  Brain.Screen.setPenColor(white);
  Brain.Screen.setPenWidth(2);
  Brain.Screen.drawLine(10, 120 + -30 - 30, 10, 120 + -30 + 30);
  Brain.Screen.drawLine(470, 120 + 20 - 30, 470, 120 + 20 + 30);
  Brain.Screen.drawCircle(170, 180, 5, white);
  wait (500, msec);
  waitUntil(Controller1.ButtonA.pressing() || Controller2.ButtonA.pressing());
  Brain.Screen.setFont(monoM);
  Brain.Screen.clearScreen();

  while (true) {
    // Clear the screen
    Brain.Screen.clearScreen();

    // Move paddles based on controller input
    if (Controller2.installed() == true) {
      leftPaddlePosition -= (Controller1.Axis2.position(pct) * PaddleSensitivity);
      rightPaddlePosition -= (Controller2.Axis2.position(pct) * PaddleSensitivity);
    } else {
      leftPaddlePosition -= (Controller1.Axis3.position(pct) * PaddleSensitivity);
      rightPaddlePosition -= (Controller1.Axis2.position(pct) * PaddleSensitivity);
    }

    // Limit paddle positions to stay within the screen
    if (leftPaddlePosition > 120) { leftPaddlePosition = 120; }
    else if (leftPaddlePosition < -120) { leftPaddlePosition = -120; }
    if (rightPaddlePosition > 120) { rightPaddlePosition = 120; }
    else if (rightPaddlePosition < -120) { rightPaddlePosition = -120; }

    // Draw paddles on the screen
    Brain.Screen.setPenColor(white);
    Brain.Screen.setPenWidth(2);
    Brain.Screen.drawLine(10, 120 + leftPaddlePosition - 30, 10, 120 + leftPaddlePosition + 30);
    Brain.Screen.drawLine(470, 120 + rightPaddlePosition - 30, 470, 120 + rightPaddlePosition + 30);

    // Move the ball
    ballX += ballVelocityX;
    ballY += ballVelocityY;

    // Bounce the ball off the top and bottom walls
    if (ballY <= 0 || ballY >= 240) {
      ballVelocityY = -ballVelocityY;
    }

    // Bounce the ball off the paddles
    if ((ballX <= 20 && ballX >= 10 && ballY >= 120 + leftPaddlePosition - 30 && ballY <= 120 + leftPaddlePosition + 30) ||
      (ballX >= 460 && ballX <= 470 && ballY >= 120 + rightPaddlePosition - 30 && ballY <= 120 + rightPaddlePosition + 30)) {
      ballVelocityX = -ballVelocityX;
    }

    // Draw the ball on the screen
    Brain.Screen.drawCircle(ballX, ballY, 5, white);

    // Increase ball speed over time
    int currentTime = Brain.timer(msec);
    if (currentTime - lastSpeedIncreaseTime >= speedIncreaseInterval) {
      // Increase speed
      ballVelocityX = (ballVelocityX > 0) ? (ballVelocityX + 1) : (ballVelocityX - 1);
      ballVelocityY = (ballVelocityY > 0) ? (ballVelocityY + 1) : (ballVelocityY - 1);

      // Update last speed increase time
      lastSpeedIncreaseTime = currentTime;
    }

    // Score points and increase Rounds
    if (ballX > 490 || ballX < 0) {
      // Declare winner
      Brain.Screen.setCursor(3, 18);
      if (ballX > 490) {
        Brain.Screen.print("Player 1 Scored");
        leftPaddleScore += 1;
      }
      else if (ballX < 0) {
        Brain.Screen.print("Player 2 Scored");
        rightPaddleScore += 1;
      }
      wait (1, sec);
      Brain.Screen.clearLine(3);
      // Display round
      Brain.Screen.setCursor(3, 22);
      Brain.Screen.print("Round %d", Round++);
      wait (1, sec);
      Brain.Screen.clearScreen();
      // Reset field
      ballVelocityX = 3;
      ballVelocityY = 2;
      leftPaddlePosition = 0;
      rightPaddlePosition = 0;
      ballX = 160; 
      ballY = 120;
    }
    // Game over
    if (Round > 10) break;

    // Speed of the game
    wait(20,msec);
  }

  // Declare winner
  Brain.Screen.setCursor(3,7);
  Brain.Screen.setFont(monoXL);
  if (leftPaddleScore > rightPaddleScore) {
    Brain.Screen.print("PLAYER 1 WINS");
  } 
  else if (rightPaddleScore > leftPaddleScore) {
    Brain.Screen.print("PLAYER 2 WINS");
  }
  wait (2, sec);
  Brain.Screen.clearScreen();
  Pong();
}

void Snake() {
  // Snake Variables
  int snakeX[100];
  int snakeY[100]; 
  int Movement = 3;

  // Snake starting parameters
  int snakeLength = 1;
  snakeX[0] = 240;
  snakeY[0] = 120; 
  int foodX = 100;
  int foodY = 150;

  // Title Screen
  Brain.Screen.setFont(monoXXL);
  Brain.Screen.setCursor(1,7);
  Brain.Screen.print("Snake");
    // Subtitle
  Brain.Screen.setFont(monoS);
  Brain.Screen.setCursor(5,26);
  Brain.Screen.print("- Press A to play -");
    // Graphic
  int titleX[10] = {190, 200, 210, 220, 230, 240, 240, 240, 250, 260};
  int titleY[10] = {180, 180, 180, 180, 180, 180, 170, 160, 160, 160};
  Brain.Screen.drawCircle(310, 140, 7, red);
  for (int i = 0; i < 10; i++) {
    Brain.Screen.drawRectangle(titleX[i] - 5, titleY[i] - 5, 15, 15, green);
  }
  wait (500, msec);
  waitUntil(Controller1.ButtonA.pressing());
  Brain.Screen.setFont(monoM);
  Brain.Screen.clearScreen();
  
  // Gameplay loop
  while (true) {
    // Clear the screen
    Brain.Screen.clearScreen();

    // Move snake based on controller input (toggle)
    if (Controller1.ButtonUp.pressing()) { Movement = 1; }
    else if (Controller1.ButtonDown.pressing()) { Movement = 2; }
    else if (Controller1.ButtonRight.pressing()) { Movement = 3; }
    else if (Controller1.ButtonLeft.pressing()) { Movement = 4; }

    // Draw the snake on the brain
    for (int i = 0; i < snakeLength; i++) {
      Brain.Screen.drawRectangle(snakeX[i] - 5, snakeY[i] - 5, 15, 15, green);
    }

    // Draw the food
    Brain.Screen.drawCircle(foodX, foodY, 7, red);

    // Move snakes body segments
    for (int i = snakeLength - 1; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }

    // Set new head position
    snakeX[0] += (Movement == 3) ? 10 : (Movement == 4) ? -10 : 0;
    snakeY[0] += (Movement == 1) ? -10 : (Movement == 2) ? 10 : 0;

    // Check for collision with food
    if ((snakeX[0] <= foodX + 6 && snakeX[0] >= foodX -6) && (snakeY[0] <= foodY + 6 && snakeY[0] >= foodY - 6)) {
      // Increase snake length
      snakeLength++;

      // Generate new food position
      foodX = rand() % (475 - 5 + 1) + 5;
      foodY = rand() % (235 - 5 + 1) + 5;
    }

    // Check for collision with the walls
    if (snakeX[0] >= 480 || snakeX[0] <= 0 || snakeY[0] <= 0 || snakeY[0] >= 240) {
      // Game over
      wait (1,sec);
      Brain.Screen.clearScreen();
      Brain.Screen.setFont(monoXL);
      Brain.Screen.setCursor(3, 9);
      Brain.Screen.print("Game Over");
        // Score
      Brain.Screen.setFont(monoS);
      Brain.Screen.setCursor(10,26);
      Brain.Screen.print("Your score is: %d", snakeLength);
      wait(2, sec);
      Brain.Screen.clearScreen();
      Snake();
    }

    // Check for collision with snake's body
    for (int i = 1; i < snakeLength; i++) {
      if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
        // Game over
        wait (1,sec);
        Brain.Screen.clearScreen();
        Brain.Screen.setFont(monoXL);
        Brain.Screen.setCursor(3, 9);
        Brain.Screen.print("Game Over");
          // Score
        Brain.Screen.setFont(monoS);
        Brain.Screen.setCursor(10,26);
        Brain.Screen.print("Your score is: %d", snakeLength);
        wait(2, sec);
        Brain.Screen.clearScreen();
        Snake();
      }
    }

    // Game speed / Resource overload prevention
    wait (100, msec);
  }
}