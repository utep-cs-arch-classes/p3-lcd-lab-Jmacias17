#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "led.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

int color_change;
char redraw_screen = 1;
u_int backgroundColor;


void
update_text(void)
{
  const u_char text_row = 20;
  const u_char text_col = 40;
  const u_char char_width = 12;
  static u_char blue = 31, green = 16, red = 31;
  u_int on_color  =                (green << 5) | red;
  u_int off_color = (blue << 11)                | red;
  
  if (switch1_state == down) {
    color_change = 1;
    drawChar5x7(text_col, text_row, 'J',on_color, backgroundColor);
  } else {
    drawChar5x7(text_col, text_row, '-',off_color, backgroundColor);
  }
  if (switch2_state == down) {
    color_change = 2;
    drawChar5x7(text_col + char_width, text_row, '2',on_color, backgroundColor);
  } else {
    drawChar5x7(text_col + char_width, text_row, '-',off_color, backgroundColor);
  }

}



void main(void)
{
  
  configureClocks();
  led_init();
  switch_p2_init();
  lcd_init();
  
  //enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  backgroundColor = COLOR_GREEN;
  
  clearScreen(backgroundColor);

  while (1) {			/* forever */
    if (redraw_screen) {
      if (color_change == 1) {
	backgroundColor = COLOR_BLUE;
      } else if (color_change == 2) {
	backgroundColor = COLOR_RED;
      }
      
      clearScreen(backgroundColor);
      redraw_screen = 0;
      update_text();
    }
    green_on = 0;   	/* led off */
    led_changed = 1;
    led_update();
    or_sr(0x10);	/**< CPU OFF */
    
    green_on = 1;	/* led on */
    led_changed = 1;
    led_update();
  }
}

    
    
