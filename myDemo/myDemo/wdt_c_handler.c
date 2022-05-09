#include "draw_shapes.h"
#include "stateMachines.h"


/* the interupt handler for the watchdog timer */
void wdt_c_handler(void)
{
  /* Time Variables */
  static int secCount = 0;       /* Counts the amount of seconds */

  /* Updates Values */
  secCount ++;
  /* Measure Seconds Elapsed */
  if (secCount >= 250) {
    seconds++;/* 1 Second has passed */
    secCount = 0;   /* Reset Seconds */
  }
  
  if (seconds > 4) {
    seconds = 0;
  }

  if ((secCount % 250 == 0) && switchState != 1 ) {
    switchState = 0;
  }
  
  if (secCount % 30 == 0 ) {
      redrawScreen = 1;
  }

  /* Intro Done (s0) / Play Again Text (s3) After 3 Seconds */
  if ((seconds > 2 && master == 0) || (seconds > 1 && master == 3)) {
    seconds = 0;    /* Reset Seconds */
    nextState = 1;  /* Go to Next State */
  }
}
