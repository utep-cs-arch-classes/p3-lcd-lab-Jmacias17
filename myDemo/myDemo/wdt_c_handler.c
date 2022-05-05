#include "draw_shapes.h"
#include "stateMachines.h"


/* the interupt handler for the watchdog timer */
void wdt_c_handler(void)
{
  /* Time Variables */
  static int secCount = 0;       /* Counts the amount of seconds */
  static int eventCount = 0;     /* Triggers and Event */

  /* Updates Values */
  secCount ++;
  eventCount ++;

   /* Measure redrawScreen */
  if (secCount >= 250) {
    eventCount = 0;  /* 2 Checks */
    redrawScreen = 1; /* Redraw Screen */
  }
  
  /* Measure Seconds Elapsed */
  if (secCount >= 250) {
    seconds++;/* 1 Second has passed */
    secCount = 0;   /* Reset Seconds */
  }

  /* Intro Done (s0) / Play Again Text (s3) After 3 Seconds */
  if ((seconds == 3 && master == 0) || (seconds == 3 && master == 2)) {
    seconds = 0;    /* Reset Seconds */
    nextState = 1;  /* Go to Next State */
  }
}
  
