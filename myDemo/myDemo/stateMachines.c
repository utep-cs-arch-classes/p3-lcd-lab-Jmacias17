
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
int textState = 0;       /* Controls which text state to display */
int switchState = 0;     /* Controls the state of the switches */

void
displayText(void) {
  /* Three Different Texts (INTRO, READY TO PLAY, GAMEOVER) */
  switch (textState) {
  case 0:
    drawString5x7(30, 30, "CREATED BY", COLOR_WHITE, COLOR_BLACK);
    drawString5x7(40, 40, "JESUS M.", COLOR_WHITE, COLOR_BLACK);
    break;
  case 1:
    drawString5x7(screenWidth/2, screenHeight/2, "PRESS ANY SWITCH TO PLAY", COLOR_WHITE, COLOR_BLACK); 
  case 2:
    drawString5x7(30, 30, "GAME OVER", COLOR_WHITE, COLOR_BLACK); 
    drawString5x7(screenWidth/2, screenHeight/2, "PRESS ANY SWITCH TO PLAY", COLOR_WHITE, COLOR_BLACK);
    break;
  }
}

void
introScreen(void){
  buzzer_set_period(200000/500);
  displayText();
  if (nextState == 1) {
    buzzer_set_period(0);
    master = 1;
    nextState = 0;
    textState = 1;
  }
}

void
playGame(void){
  if (nextState == 1 ) {
    master = 2;
    nextState = 0;
    redrawScreen2 = 1;
  }
  
  draw_moving_shapes();
  if (switches & SW1) {
    moving_circle(10);
  } else if (switches & SW2) {
    moving_circle(-10);
  }
}
void
resetGame(void){
  init_rectype();
  init_player();
  clearScreen(COLOR_BLUE);
}
void
gameOver(void){
}
