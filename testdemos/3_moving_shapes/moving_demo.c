#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "draw_shapes.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 


char redraw_screen = 1;

void main(void)
{
  configureClocks();
  led_init();
  switch_p2_init();
  lcd_init();
  
  green_on = 1;
  led_changed = 1;
  led_update();

  buzzer_init();
  buzzer_set_period(1000); /* BEEP TO INFORM INITIALIZING */

  init_player();
  init_rectype();
 /* Start_up complete -> turn buzzer off and LED */
  buzzer_set_period(0);
  green_on = 0;
  led_changed = 1;
  led_update();

  // enableWDTInterrupts();
  while (1) {
    switch(redraw_screen) {
    case 1:
      clearScreen(background_color);
      break;
    case 2:
      init_rectype();
      init_player();
      redraw_screen = 3;
      break;
    case 3:
      moving_circle(20);
      break;
    }
    or_sr(0x18);     /**< CPU off , GIE on */
  }
}
  

