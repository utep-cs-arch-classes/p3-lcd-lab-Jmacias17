#include "draw_shapes.h"
#include "switches.h"

// global vars for the rectangle
ctrlType typeCtrl;
rectangle rect1;
rectangle rect2;
rectangle rect3;
/* int rect_row, rect_col; */
/* int old_rect_row, old_rect_col; */
/* u_char height, width; */

// global vars for the circle
/* int cir_y, cir_x; */
/* int old_cir_y, old_cir_x; */
/* int r; */
circle cir1;
short redrawScreen = 1;
u_int background_color = COLOR_BLUE;

void
init_rectype(void)
{
  typeCtrl.ready_newtype = 0;
  // vars for the top piece in rectangle1
  rect1.rect1_row = 0;
  rect1.rect1_col = screenWidth - 1;
  rect1.old_rect1_row = 0;
  rect1.old_rect1_col = screenWidth -1;
  rect1.height1 = 100;
  rect1.width1  = 20;

  // vars for the bottom piece in rectangle1
  rect1.rect2_row = 0;
  rect1.rect2_col = screenWidth - 1;
  rect1.old_rect2_row = 0;
  rect1.old_rect2_col = screenWidth -1;
  rect1.height2 = 0;
  rect1.width2  = 0;

  // vars for the top piece in rectangle2
  rect2.rect1_row = 0;
  rect2.rect1_col = screenWidth - 1;
  rect2.old_rect1_row = 0;
  rect2.old_rect1_col = screenWidth -1;
  rect2.height1 = 0;
  rect2.width1  = 0;

  // vars for the bottom piece in rectangle2
  rect2.rect2_row = 60;
  rect2.rect2_col = screenWidth - 1;
  rect2.old_rect2_row = 60;
  rect2.old_rect2_col = screenWidth -1;
  rect2.height2 = 100;
  rect2.width2  = 20;

   // vars for the top piece in rectangle3
  rect3.rect1_row = 0;
  rect3.rect1_col = screenWidth - 1;
  rect3.old_rect1_row = 0;
  rect3.old_rect1_col = screenWidth -1;
  rect3.height1 = 50;
  rect3.width1  = 20;

  // vars for the second piece in rectangle2
  rect3.rect2_row = 110;
  rect3.rect2_col = screenWidth - 1;
  rect3.old_rect2_row = 100;
  rect3.old_rect2_col = screenWidth -1;
  rect3.height2 = 50;
  rect3.width2  = 20;
}

void
init_player(void){
  typeCtrl.ready_newtype = 0;
  // vars for the circle
  cir1.cir_y = screenWidth / 2;
  cir1.cir_x = 10;
  cir1.old_cir_y = screenWidth / 2;
  cir1.old_cir_x = 10;
  cir1.r = 9;

  typeCtrl.curr_type = 0;
  typeCtrl.ready_newtype = 0;
}

void
draw_moving_shapes(void)
{
  int i = typeCtrl.curr_type;
  
  if(typeCtrl.ready_newtype == 1) {
    i = ((typeCtrl.random_val * typeCtrl.curr_type) + 1) % 3;
    typeCtrl.curr_type = i;
    typeCtrl.ready_newtype = 0;
  }
  
  //Defaults
  int left_col= 0;
  int top_row = 0;
  int height= 0;
  int width= 0;

  int left_col2 = 0;
  int top_row2 = 0;
  int height2 = 0;
  int width2 = 0;
  

  switch(i) {
  case 0:
    left_col = rect1.old_rect1_col;
    top_row  = rect1.old_rect1_row;
    height = rect1.height1;
    width = rect1.width1;

    left_col2 = rect1.old_rect2_col;
    top_row2 = rect1.old_rect2_row;
    height2 = rect1.height2;
    width2 = rect1.width2;
    break;
  case 1:
    left_col = rect2.old_rect1_col;
    top_row  = rect2.old_rect1_row;
    height = rect2.height1;
    width = rect2.width1;

    left_col2 = rect2.old_rect2_col;
    top_row2 = rect2.old_rect2_row;
    height2 = rect2.height2;
    width2 = rect2.width2;
    break;
  case 2:
    left_col = rect3.old_rect1_col;
    top_row  = rect3.old_rect1_row;
    height = rect3.height1;
    width = rect3.width1;
    
    left_col2 = rect3.old_rect2_col;
    top_row2 = rect3.old_rect2_row;
    height2 = rect3.height2;
    width2 = rect3.width2;
    break;
  default:
    left_col = 0; top_row = 0; height = 0; width = 0; height2 = 0; width2 = 0;
  }
  
  // blank out the old rectangle
  fillRectangle(left_col, top_row, width, height, background_color);
  //blank out the old bottom piece of rectangle
  fillRectangle(left_col2, top_row2, width2, height2, background_color);
  
  // blank out the old circle
  draw_circle(cir1.old_cir_x, cir1.old_cir_y, cir1.r, background_color);
  switch (i) {
  case 0:
    // draw and update the rectangle
    moving_rectangle(&rect1);
    break;
  case 1:
    // draw and update the rectangle
    moving_rectangle(&rect2);
    break;
  case 2:
    // draw and update the rectangle
    moving_rectangle(&rect3);
    break;
   
  }
  moving_circle(0);
}

void
moving_rectangle(rectangle *to_draw)
{
  static int x_vel = 20;
  static int y_vel = 0;

  int left_col = to_draw->rect1_col;
  int top_row  = to_draw->rect1_row;
  int left_col2 = to_draw->rect2_col;
  int top_row2 = to_draw->rect2_row;
  
  unsigned int blue = 16, green = 0, red = 31;
  unsigned int color = (blue << 11) | (green << 5) | red;

  // draw rectangle at current position
  fillRectangle(left_col, top_row, to_draw->width1, to_draw->height1, color);
  fillRectangle(left_col2, top_row2, to_draw->width2, to_draw->height2, color);
  // save current position
  to_draw->old_rect1_row = to_draw->rect1_row;
  to_draw->old_rect1_col = to_draw->rect1_col;
  to_draw->old_rect2_row = to_draw->rect2_row;
  to_draw->old_rect2_col = to_draw->rect2_col;
  // update position
  to_draw->rect1_row += y_vel;
  to_draw->rect1_col -= x_vel;
  to_draw->rect2_row += y_vel;
  to_draw->rect2_col -= x_vel;
  

  if ( (to_draw->rect1_col ) <= -15 ||
       (to_draw->rect2_col ) <= -15) { 
    // Set to Original Values.
    fillRectangle(to_draw->old_rect1_col, to_draw->old_rect1_row, to_draw->width1, to_draw->height1, background_color);
    fillRectangle(to_draw->old_rect2_col, to_draw->old_rect2_row, to_draw->width2, to_draw->height2, background_color);
    init_rectype();
    typeCtrl.ready_newtype = 1;
  }
}

void
drawHorizontalLine(u_int x_start, u_int x_end, u_int y, u_int colorBGR)
{
  u_int length = x_end - x_start;
  // set the draw area from the start of the line to the end
  // height is 1 since its a line
  lcd_setArea(x_start, y, x_end, y);
  for (u_int i = 0; i < length; i++) {
    lcd_writeColor(colorBGR);
  }
  
}

void
drawLines(u_int x_coord, u_int y_coord, u_int x_point, u_int y_point, u_int color)
{
  // bottom
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord + y_point, color);
  // top
  drawHorizontalLine(x_coord - x_point, x_coord + x_point, y_coord - y_point, color);
  // and the middle two
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord + x_point, color);
  drawHorizontalLine(x_coord - y_point, x_coord + y_point, y_coord - x_point, color);
					  
}

void
draw_circle(int x, int y, int r, u_int color)
{
  int x_coord = x;
  int y_coord = y;
  // first point will be the very top;
  int x_point = 0;
  int y_point = r;
  int decision = 3 - (2 * r);

  drawLines(x_coord, y_coord, x_point, y_point, color);

  while (y_point >= x_point) {
    // move x over one
    x_point++;

    // check decision point
    if (decision > 0) {
      // move y down one
      y_point--;
      decision = decision + 4 * (x_point - y_point) + 10;
    } else {
      decision = decision + 4 * x_point + 6;
    }
    drawLines(x_coord, y_coord, x_point, y_point, color);
  }
}

void
moving_circle(int n)
{
  int y_vel = n;
  
  if (switches & SW1) {
    y_vel = 10;
  } else if (switches & SW2) {
    y_vel = -10;
  }
  
  u_int color = COLOR_SIENNA;


  // draw at the new position
  draw_circle(cir1.cir_x, cir1.cir_y, cir1.r, color);

  // save current position
  cir1.old_cir_x = cir1.cir_x;
  cir1.old_cir_y = cir1.cir_y;

  if (switches & SW3) {
    cir1.old_cir_y = 10;
  } else if (switches & SW4) {
    cir1.cir_y = 140;
  } else {
    cir1.cir_y += y_vel;
  }
  typeCtrl.random_val = cir1.cir_y;
  
  // check boundaries, see if rectangle has hit the edges
  if ( ( cir1.cir_y - cir1.r ) <= 0 ||            // top
       ( cir1.cir_y + cir1.r ) >= screenHeight - 2) { // bottom
    cir1.cir_y = 140;
  }

  switch(typeCtrl.curr_type) {
  case 0:
     if( ( (cir1.cir_y + cir1.r) <= rect1.height1 ) &&
	 ( (cir1.cir_x + cir1.r) >= rect1.rect1_col ) ) {
       cir1.cir_y = screenWidth / 2;
       cir1.cir_x = 10;
    }
    break;
  case 1:
    if( ( (cir1.cir_y + cir1.r) >= rect2.rect2_row ) &&
	( (cir1.cir_x + cir1.r) >= rect2.rect2_col ) ) {				     
      cir1.cir_y = screenWidth / 2;
      cir1.cir_x = 10;
    }
    break;
  case 2:
    if( ( ( (cir1.cir_y + cir1.r) <= rect3.height1 ) &&
	  ( (cir1.cir_x + cir1.r) >= rect3.rect1_col ) ) ||
	( ( (cir1.cir_y + cir1.r) >= rect3.rect2_row ) &&
	  ( (cir1.cir_x + cir1.r) >= rect3.rect2_col ) ) ) {     
      cir1.cir_y = screenWidth / 2;
      cir1.cir_x = 10;
    break;
    }
  }
}
