
#include <msp430.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "buzzer.h"
#include "switches.h"

int master = 0;          /* Controls the overall main state of the program */

short redrawScreen = 1;  /* Controls if the screen needs to be redrawn */
short redrawScreen2 = 1; /* Controls if the special event needs to be redrawn */

int nextState = 0;       /* Controls if needed to go to the next_state */;
int resetState= 0;        /* Controls if game needs to be reset */
int textState = 0;       /* Controls which text state to display */
int switchState = 0;     /* Controls the state of the switches */

int seconds = 0;         /* Controls the elapsed seconds */
int highScore = 0;       /* Current High Score */

void
displayScore(int x, int y, int score, int color) {
  int firstD = score / 10;
  int secondD = score % 10;
  switch (firstD) {
  case 0:
    drawString5x7(x,y, "0", COLOR_WHITE, color);
    break;
  case 1:
    drawString5x7(x,y, "1", COLOR_WHITE, color);
    break;
  case 2:
    drawString5x7(x,y, "2", COLOR_WHITE, color);
    break;
  case 3:
    drawString5x7(x,y, "3", COLOR_WHITE, color);
    break;
  case 4:
    drawString5x7(x,y, "4", COLOR_WHITE, color);
    break;
  case 5:
    drawString5x7(x,y, "5", COLOR_WHITE, color);
    break;
  case 6:
    drawString5x7(x,y, "6", COLOR_WHITE, color);
    break;
  case 7:
    drawString5x7(x,y, "7", COLOR_WHITE, color);
    break;
  case 8:
    drawString5x7(x,y, "8", COLOR_WHITE, color);
    break;
  case 9:
    drawString5x7(x,y, "9", COLOR_WHITE, color);
    break;
  }
  switch (secondD) {
  case 0:
    drawString5x7(x + 5,y, "0", COLOR_WHITE, color);
    break;
  case 1:
    drawString5x7(x + 5,y, "1", COLOR_WHITE, color);
    break;
  case 2:
    drawString5x7(x + 5,y, "2", COLOR_WHITE, color);
    break;
  case 3:
    drawString5x7(x + 5,y,"3", COLOR_WHITE, color);
    break;
  case 4:
    drawString5x7(x + 5,y,"4", COLOR_WHITE, color);
    break;
  case 5:
    drawString5x7(x + 5,y,"5", COLOR_WHITE, color);
    break;
  case 6:
    drawString5x7(x + 5,y, "6", COLOR_WHITE, color);
    break;
  case 7:
    drawString5x7(x + 5,y,"7", COLOR_WHITE, color);
    break;
  case 8:
    drawString5x7(x + 5,y,"8", COLOR_WHITE, color);
    break;
  case 9:
    drawString5x7(x + 5,y,"9", COLOR_WHITE, color);
    break;
    }
}

void
displayText(void) {
  /* Three Different Texts (INTRO, READY TO PLAY, GAMEOVER) */
  switch (textState) {
  case 0:
    drawString5x7(30, 30, "CREATED BY", COLOR_WHITE, COLOR_BLACK);
    drawString5x7(40, 40, "JESUS M.", COLOR_WHITE, COLOR_BLACK);
    break;
  case 1:
    if(switchState == 0) {
      drawString5x7(20, 40, "CHOOSE A SKIN", COLOR_WHITE, COLOR_BLACK);
      drawString5x7(10, screenHeight/2, "PRESS SW1 TO CYCLE", COLOR_WHITE, COLOR_BLACK);
      drawString5x7(2, screenHeight/2 + 15, "PRESS SW2 TO CONFIRM", COLOR_WHITE, COLOR_BLACK);
    } else if (switchState == 1) {
      drawString5x7(5, 80, "PRESS ANY SW TO PLAY", COLOR_WHITE, COLOR_BLACK);
    }
      break;
  case 2:
    //BEGINNER 
    break;
  case 3:
    //Display Current Score
    displayScore(50, screenHeight/2 - 14, score, COLOR_BLACK);
    drawString5x7(28, screenHeight/2 - 26, "YOUR SCORE", COLOR_WHITE, COLOR_BLACK);

    //If Delay Time has Passed
    if(nextState == 1 && switchState == 0) {
      //Turn off Buzzer
      buzzer_set_period(0);

      //Fill and Replace Text Areas
      fillRectangle(30,40,56,7,COLOR_BLACK);
      drawString5x7(28, screenHeight/2 - 56, "HIGH SCORE", COLOR_WHITE, COLOR_BLACK);

      displayScore(50, screenHeight/2 - 45, highScore, COLOR_BLACK);

      drawString5x7(10, screenHeight/2, "PRESS ANY SWITCH", COLOR_WHITE, COLOR_BLACK);
      drawString5x7(30, screenHeight/2 + 12, "TO RESTART", COLOR_WHITE, COLOR_BLACK);
    } else {
      drawString5x7(30, 40, "GAME OVER", COLOR_WHITE, COLOR_BLACK);
    }
    break;
  }
}

void
splashScreen(void){
  buzzer_set_period(200000/500);
  displayText();
  if (nextState == 1) {
    redrawScreen2 = 1;
    buzzer_set_period(0);
    master = 1;
    nextState = 0;
    textState = 1;
  }
}
void
introScreen(void) {
  buzzer_set_period(0);
  seconds = 0;
  if(switches && switchState == 1) {     /* If switches pressed and switch state 1 then start */
    redrawScreen2 = 1;                   /* triggers the screen to reset in next master state*/
    master = 2;                          /* Start Game */
    switchState = 0;                     /* switches go back to 0 */
    textState = 2;                       /* Text state changes */
  } else {
    displayText();
    chooseSkin();                        /* Else display Choose Skin! */
    if (switches & SW2) {
      switchState = 1;
      redrawScreen2 = 1;
    }
  }
}
 
void
playGame(void){
  draw_moving_game();
}

void
resetGame(void){
  init_player();
}

void
gameOver(void){
  /* If switches pressed and next state = 1 then start and make noise */
  if((switch1_down | switch2_down | switch3_down | switch4_down) && nextState == 1) {
    redrawScreen2 = 1;  /* Ready to refresh screen */
    master = 1;         /* Back to character selection */
    nextState = 0;      /* RESTART GAME */
    textState = 1;      /* Sets the Text State for Intro */
    switchState = 0;    /* Sets the Switch State for Intro */
  } else {              /* Else display Press to Play! */
    displayText();
   }
}
