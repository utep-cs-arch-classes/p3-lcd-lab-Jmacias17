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
  buzzer_set_period(1000); /* inititate the Buzzer Start Up */
  P1DIR |= LED;		/**< Led on when CPU Starts Up */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  buzzer_set_period(0);       /* START-UP DONE -> TURN BUZZER OFF */
  clearScreen(COLOR_BLACK);    /* CLEAR SCREEN */
  P1OUT &= ~LED;	/* led off */
  
  while (1) {			/* forever */
    if (redrawScreen) {                     /* Time is set to redrawScreen */
      switch (master) {                     /* Program displays depending on state */
      case 0:                               /* Intro State */
	redrawScreen = 0;
	if(redrawScreen2) {  /* Reset Screen Once */
	  clearScreen(COLOR_BLACK);
	  redrawScreen2 = 0;
	  seconds = 0;
	}
	splashScreen();
	break;
      case 1:                                  /* Game State */
	introScreen();
	if(redrawScreen2) {                  /* Start Game */
	  resetGame();                     /* Reset Game Settings */
	  redrawScreen2 = 0;
	  seconds = 0;
	}

	if(switchState == 1) {
	  playGame();
	}
	break;
      case 2:
	redrawScreen = 0;
	if(redrawScreen2) {
	  clearScreen(COLOR_BLACK);
	  redrawScreen2 = 0;
	  seconds = 0;
	}
	gameOver();
	break;
      }
    }
    or_sr(0x10);	/**< CPU OFF */
  }
}
