#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "buzzer.h"
#include "stateMachines.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

void main()
{
  buzzer_init();
  buzzer_set_period(1000);                 /* inititate the Buzzer Start Up */
  P1DIR |= LED;		                   /**< Led on when CPU Starts Up */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  enableWDTInterrupts();                   /**< enable periodic interrupt */
  or_sr(0x8);	                           /**< GIE (enable interrupts) */

  buzzer_set_period(0);                    /* START-UP DONE -> TURN BUZZER OFF */
  clearScreen(COLOR_BLACK);                /* CLEAR SCREEN */
  P1OUT &= ~LED;	                   /* led off */
  
  while (1) {			           /* forever */
    if (redrawScreen) {                    /* Time is set to redrawScreen */
      switch (master) {                    /* Program displays depending on state */
      case 0:                              /* Splash State */
	redrawScreen = 0;
	if(redrawScreen2) {                /* if first time in this state since diff state */
	  clearScreen(COLOR_BLACK);        /* Clear the screen black */
	  redrawScreen2 = 0;         
	  seconds = 0;
	}
	splashScreen();                    /* Display splash screen */
	break;
      case 1:                              /* Intro State (Choose Skin) */
	redrawScreen = 0;
	if (redrawScreen2 == 1) {          /* If first time in this state since diff state */
	  clearScreen(COLOR_BLACK);        /* Clear the screen black */
	  redrawScreen2 = 0;
	}
	introScreen();                     /* Display Intro Screen Settings */
	break;
      case 2:                                /* Game State */
	redrawScreen = 0;
	if(redrawScreen2 == 1) {             /* If first time in state since diff state*/
	  clearScreen(background_color);     /* Clear screen to background color */
	  score = 0;                        /* Reset the score to 0
	  
	                                   /* Start Game */
	  resetGame();                      /* Reset Game Settings */
	  redrawScreen2 = 0;              
         }
      playGame();                          /* Display Game */
       	break;
    case 3:                                /* Game Over State */
      redrawScreen = 0;
      if(redrawScreen2) {                  /* If first time in state since diff state */
	clearScreen(COLOR_BLACK);          /* Resets background to black */
	  redrawScreen2 = 0;
	  seconds = 0;
      }
      gameOver();                          /* Show Game Over Screen */
      break;
      }
    }
    or_sr(0x10);	                   /**< CPU OFF */
  }
}
