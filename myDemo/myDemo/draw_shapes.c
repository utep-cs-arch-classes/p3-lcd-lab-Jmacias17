#include "draw_shapes.h"

#include "switches.h"
#include "stateMachines.h"
#include "buzzer.h"

// global vars for the rectangle
ctrlType typeCtrl;   /* Controls the type of Tube */
rectangle rect1;     /* The 3 Tube Type default coordinates will be stored and used in each */
rectangle rect2;
rectangle rect3;


player player1;      /* The Player sprite */
int playerSkin;
int score = 0;       /* Keeps track of the score */
int twiceRepeat = 0; /* if a rectangle has repeated twice turns on */
int tempVal = 0;     /* a random variable.

/* int rect_row, rect_col; */
/* int old_rect_row, old_rect_col; */
/* u_char height, width; */

// global vars for the circle
/* int cir_y, cir_x; */
/* int old_cir_y, old_cir_x; */
/* int r; */
circle cir1;                           /* Current player */
u_int background_color = COLOR_BLUE;   /* background color */  

void
init_rectype(void)                     /* Imitialize rectange types default coords. */
{
  typeCtrl.ready_newtype = 0;          /* Not ready for a new rectangle type */
  
  // vars for the top piece in rectangle1
  rect1.rect1_row = 0;
  rect1.rect1_col = screenWidth - 1;
  rect1.old_rect1_row = 0;
  rect1.old_rect1_col = screenWidth -1;
  rect1.height1 =  ((tempVal * score) % 50) + 70;
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
rect2.rect2_row = ((cir1.cir_y * score) % 40) + 60;
  rect2.rect2_col = screenWidth - 1;
  rect2.old_rect2_row = ((0 * score) % 40) + 60;
  rect2.old_rect2_col = screenWidth -1;
  rect2.height2 = screenHeight - rect2.rect2_row;
  rect2.width2  = 20;

   // vars for the top piece in rectangle3
  rect3.rect1_row = 0;
  rect3.rect1_col = screenWidth - 1;
  rect3.old_rect1_row = 0;
  rect3.old_rect1_col = screenWidth -1;
  rect3.height1 = ((tempVal * score) % 60) + 40;
  rect3.width1  = 20;

  // vars for the second piece in rectangle3
  rect3.rect2_row = rect3.height1 + ((tempVal * score) % 20) + 45;
  rect3.rect2_col = screenWidth - 1;
  rect3.old_rect2_row = rect3.rect1_row + ((tempVal * score) % 20) + 45;
  rect3.old_rect2_col = screenWidth -1;
  rect3.height2 = screenHeight - rect3.rect2_row;
  rect3.width2 = 20;
}

void
init_player(void){           /* Sets players default coords. */
  /* Vars for the player */
  player1.curr_x = 1;
  player1.curr_y = screenWidth / 2;
  player1.old_x = 1;
  player1.old_y = screenWidth/2;
  player1.width = 10;
  player1.height = 10;
  
  // vars for the circle             */ Current Player */
  cir1.cir_y = screenWidth / 2;
  cir1.cir_x = 10;
  cir1.old_cir_y = screenWidth / 2;
  cir1.old_cir_x = 10;
  cir1.r = 9;


  /* Rectangle type starts at type 0 and doesn't need a new one yet. */
  typeCtrl.curr_type = 0;
  typeCtrl.ready_newtype = 0;
}

void
displayBackground(void){             /* Displays Various Clouds */
  displayCloud(20,20);
  displayCloud(100,20);
  displayCloud(50, 40);
  displayCloud(85, 70);
  displayCloud(10, 55);
}

void
displayCloud(int x, int y){
  /* Pixel art for a cloud */
  u_int cloudcolor1 = COLOR_WHITE;
  u_int cloudcolor2 = '0xd9e';
  u_int cloudcolor3 = '0xbfc';

  //First ROW
  fillRectangle(x + 9, y, 3, 1, cloudcolor1);
  //Second ROW
  fillRectangle(x + 5, y + 1, 2, 1, cloudcolor1);
  fillRectangle(x + 7, y + 1, 9, 1, cloudcolor1);
  //Third Row
  fillRectangle(x + 4, y + 2, 4, 1, cloudcolor1);
  fillRectangle(x + 8, y + 2, 3, 1, cloudcolor2);
  fillRectangle(x + 11, y + 2, 8, 1, cloudcolor1);
  //Fourth Row
  fillRectangle(x + 2, y + 3, 6, 1, cloudcolor1);
  fillRectangle(x + 8, y + 3, 5, 1, cloudcolor2);
  fillRectangle(x + 13, y + 3, 3, 1, cloudcolor1);
  fillRectangle(x + 16, y + 3, 3, 1, cloudcolor2);
  fillRectangle(x + 19, y+ 3, 1, 1, cloudcolor1);
  //Fifth Row
  fillRectangle(x + 1, y + 4, 2, 1, cloudcolor1);
  fillRectangle(x + 3, y + 4, 1, 1, cloudcolor2);
  fillRectangle(x + 4, y + 4, 1, 1, cloudcolor1);
  fillRectangle(x + 5, y + 4, 15, 1, cloudcolor2);
  fillRectangle(x + 19, y + 4, 1, 1, cloudcolor1);
  //Sixth Row
  fillRectangle(x, y + 5, 1, 1, cloudcolor1);
  fillRectangle(x + 1, y + 5, 20, 1, cloudcolor2);
  //Seventh Row
  fillRectangle(x, y + 6, 1, 1, cloudcolor1);
  fillRectangle(x + 1, y + 6, 3 , 1, cloudcolor2);
  fillRectangle(x + 4, y + 6, 1, 1, cloudcolor3);
  fillRectangle(x + 5, y + 6, 2, 1, cloudcolor2);
  fillRectangle(x + 7, y + 6, 2, 1, cloudcolor3);
  fillRectangle(x + 9, y + 6, 12, 1, cloudcolor2);
  //Eigth Row
  fillRectangle(x, y + 7, 1, 1, cloudcolor1);
  fillRectangle(x + 1, y + 7, 3 , 1, cloudcolor2);
  fillRectangle(x + 4, y + 7, 3, 1, cloudcolor3);
  fillRectangle(x + 7, y + 7, 3, 1, cloudcolor2);
  fillRectangle(x + 10, y + 7, 1, 1, cloudcolor3);
  fillRectangle(x + 11, y + 7, 1, 1, cloudcolor2);
  fillRectangle(x + 12, y + 7, 1, 1, cloudcolor3);
  fillRectangle(x + 13, y + 7, 7, 1, cloudcolor2);
  //Ninth Row
  fillRectangle(x + 1, y + 8, 7, 1, cloudcolor3);
  fillRectangle(x + 8, y + 8, 3, 1, cloudcolor2);
  fillRectangle(x + 11, y + 8, 4, 1, cloudcolor3);
  fillRectangle(x + 15, y + 8, 3, 1, cloudcolor2);
  fillRectangle(x + 18, y + 8, 1, 1, cloudcolor3);
  //Tenth Row
  fillRectangle(x + 5, y + 9, 14, 1, cloudcolor3);
  //Eleventh Row
  fillRectangle(x + 6, y + 10, 11, 1, cloudcolor3);
  //LastRow
  fillRectangle(x + 7, y + 11, 2, 1, cloudcolor3);
  fillRectangle(x + 12, y + 11, 3, 1, cloudcolor3);
}


void
draw_moving_shapes(void)
{
  if(typeCtrl.ready_newtype == 1) {       /* If ready for a new rectangle type */
                                          /* tempVal = the next rectangle type */
    tempVal = ((typeCtrl.random_val * typeCtrl.curr_type) + score) % 3;
    if (tempVal == typeCtrl.curr_type) {  /* The rectangle new type will be the same as before */
      twiceRepeat += 1;                   /* Increase the repeated rectangle type count */
    } else if (twiceRepeat == 2) {        /* rectangle type repeated three times reset */
      typeCtrl.curr_type = (typeCtrl.curr_type + 1) % 3;
      twiceRepeat = 0;                    /* reset twice repeat to 0 */
    } else {
      typeCtrl.curr_type = tempVal;       /* curr type is set to the random value */
    }
    typeCtrl.ready_newtype = 0;           /* no longer ready for a new rectangle type */
  }
  
  displayBackground();                    /* Print cloud background */
  
  switch (typeCtrl.curr_type) {           /* Based on which rectangle type */
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
  moving_circle(0); /* Moves the player in stall position */
}

void
moving_rectangle(rectangle *to_draw)
{
   
  //Defaults
  int left_col= 0;
  int top_row = 0;
  int height= 0;
  int width= 0;

  int left_col2 = 0;
  int top_row2 = 0;
  int height2 = 0;
  int width2 = 0;

  /* Manage the Rectangle Type Displayed */
  switch(typeCtrl.curr_type) {
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
  static int x_vel = 15;
  static int y_vel = 0;

  left_col = to_draw->rect1_col;
  top_row  = to_draw->rect1_row;
  left_col2 = to_draw->rect2_col;
  top_row2 = to_draw->rect2_row;
  
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

  /* If either the top or bottom of the rectangle hit the left screen reset */
  if ( (to_draw->rect1_col ) <= -15 ||
       (to_draw->rect2_col ) <= -15) {
    
    /* Set a sound for score! */
    buzzer_set_period(2000);
    
    // Set to Original Values.
    fillRectangle(to_draw->old_rect1_col, to_draw->old_rect1_row, to_draw->width1, to_draw->height1, background_color);
    fillRectangle(to_draw->old_rect2_col, to_draw->old_rect2_row, to_draw->width2, to_draw->height2, background_color);

    /* score increase! */
    score+= 1;
    init_rectype();
    typeCtrl.ready_newtype = 1;
    buzzer_set_period(0);
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

    
  // blank out the old circle
  draw_circle(cir1.old_cir_x, cir1.old_cir_y, cir1.r, background_color);
  
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

  hit_detection();
  
}

void hit_detection(void){
  // check boundaries, see if rectangle has hit the edges
  if ( ( cir1.cir_y - cir1.r ) <= 0 ||            // top
       ( cir1.cir_y + cir1.r ) >= screenHeight - 2) { // bottom
    cir1.cir_y = 140;
  }

  switch(typeCtrl.curr_type) {                               /* Player Lost */
  case 0:                                                    /* Per Rectangle Type */              
    if( ( (cir1.cir_y - cir1.r) <= rect1.height1 ) &&       /* If hit the edges */
	 ( (cir1.cir_x + cir1.r) >= rect1.rect1_col ) ) {
      gameOverNote();                                       /* game over noise */
      if (score > highScore) {                             /* Set highScorw */
	 highScore = score;
       }
       score = 0;
       master = 2;
       redrawScreen2 = 1;
       switchState = 2;
    }
    break;
  case 1:
    if( ( (cir1.cir_y + cir1.r) >= rect2.rect2_row ) &&
	( (cir1.cir_x + cir1.r) >= rect2.rect2_col ) ) {
      gameOverNote();
      if (score > highScore) {
	 highScore = score;
       }
       score = 0;
       master = 2;
       redrawScreen2 = 1;
       switchState = 2;
    }
    break;
  case 2:
    if( ( ( (cir1.cir_y - cir1.r) <= rect3.height1 ) &&
	  ( (cir1.cir_x + cir1.r) >= rect3.rect1_col ) ) ||
	( ( (cir1.cir_y + cir1.r) >= rect3.rect2_row ) &&
	  ( (cir1.cir_x + cir1.r) >= rect3.rect2_col ) ) ) {     
      gameOverNote();
      if (score > highScore) {
	 highScore = score;
       }
       score = 0;
       master = 2;
       redrawScreen2 = 1;
       switchState = 2;
    }
    break;
  }
}
  
