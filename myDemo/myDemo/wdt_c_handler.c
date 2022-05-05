#include "draw_shapes.h"
#include "stateMachines.h"


/* the interupt handler for the watchdog timer */
void wdt_c_handler(void)
{
  /* Time Variables */
  static int secCount = 0;
  static int seconds = 0;
  static int eventCount = 0;

  /* Updates Values */
  secCount ++;
  eventCount ++;

   /* Measure redrawScreen */
  if (secCount >= 175) {
    eventCount = 0;  /* 2 Checks */
    redrawScreen = 1;
  }
  
  /* Measure Seconds Elapsed */
  if (secCount >= 250) {
    seconds++;/* 1 Second has passed */
    secCount = 0;
  }

  /* Intro Startup Done After 5 Seconds */
  if (seconds == 3 && master == 0) {
    seconds = 0;
    nextState = 1;
  }
}
  
