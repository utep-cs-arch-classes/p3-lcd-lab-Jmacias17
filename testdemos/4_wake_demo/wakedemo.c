#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "buzzer.h"

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
  init_rectype();
  init_player();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  buzzer_set_period(0);       /* START-UP DONE -> TURN BUZZER OFF */
  clearScreen(COLOR_BLUE);    /* CLEAR SCREEN */
  P1OUT &= ~LED;	/* led off */
  
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      draw_moving_shapes();
    }
    or_sr(0x10);	/**< CPU OFF */
  }
}
