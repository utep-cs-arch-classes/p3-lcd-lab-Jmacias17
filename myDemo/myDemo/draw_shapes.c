#include "draw_shapes.h"
#include "switches.h"
#include "stateMachines.h"
#include "buzzer.h"
#include "lcdutils.h"
// global vars for the pipe
/* int pipe1_row, pipe1_col, pipe2_row, pipe2_col; */
/* int old_pipe1_row, old_pipe1_col, old_pipe2_row, old_pipe2_col; */
/* u_char height1, width1, height2, width2; */

// global vars for the player
/* int curr_y, curr_x; */
/* int old_y, old_x; */
/* u_char height, width1 */
/* int player_skin_type; */
pipe pipe1;                   /* The pipe being used throughout the game */
int pipeRepeat = 0;           /* if the same pipe type has repeated three times turns on */

player player1;               /* The Player sprite */
int skinType = 0;               /* The skin color of the sprite */
int score = 0;                /* Keeps track of the score */

int randomVal;            /* Holds a random number value to help choose the next pipe */
int tempVal;              /* A temp variable. */

u_int background_color = COLOR_BLUE;   /* background color */  

void
init_pipetype(int n)          /* Initialize pipe type back to default coords based on n. */
{
  switch (n) {                /* n is the current pipe type */
  case 0:
    // vars for the top piece in pipe1 type 0
    pipe1.pipe1_row = 0;
    pipe1.pipe1_col = screenWidth - 10;
    pipe1.old_pipe1_row = 0;
    pipe1.old_pipe1_col = screenWidth - 10;
    pipe1.height1 =  ((tempVal * score) % 50) + 70;
    pipe1.width1  = 20;

    // vars for the bottom piece in pipe1 type 0
    pipe1.pipe2_row = 0;
    pipe1.pipe2_col = screenWidth - 10;
    pipe1.old_pipe2_row = 0;
    pipe1.old_pipe2_col = screenWidth - 10;
    pipe1.height2 = 0;
    pipe1.width2  = 0;
    break;
  case 1:
    // vars for the top piece in pipe1 type 1
    pipe1.pipe1_row = 0;
    pipe1.pipe1_col = screenWidth - 10;
    pipe1.old_pipe1_row = 0;
    pipe1.old_pipe1_col = screenWidth - 10;
    pipe1.height1 = 0;
    pipe1.width1  = 0;

    // vars for the bottom piece in pipe1 type
    pipe1.pipe2_row = ((player1.curr_y * score) % 40) + 60;
    pipe1.pipe2_col = screenWidth - 10;
    pipe1.old_pipe2_row = ((player1.curr_y * score) % 40) + 60;
    pipe1.old_pipe2_col = screenWidth - 10;
    pipe1.height2 = screenHeight - pipe1.pipe2_row;
    pipe1.width2  = 20;
    break;
  case 2:
     // vars for the top piece in pipe1 type 2
    pipe1.pipe1_row = 0;
    pipe1.pipe1_col = screenWidth - 10;
    pipe1.old_pipe1_row = 0;
    pipe1.old_pipe1_col = screenWidth - 10;
    pipe1.height1 = ((tempVal * score) % 60) + 40;
    pipe1.width1  = 20;

    // vars for the second piece in rectangle3
    pipe1.pipe2_row = pipe1.height1 + ((tempVal * score) % 30) + 50;
    pipe1.pipe2_col = screenWidth - 10;
    pipe1.old_pipe2_row = pipe1.height1 + ((tempVal * score) % 30) + 50;
    pipe1.old_pipe2_col = screenWidth - 10;
    pipe1.height2 = screenHeight - pipe1.pipe2_row;
    pipe1.width2 = 20;
    break;
  }
}

void
init_player(void){           /* Sets players default coords. */
  /* Vars for the player */
  /* More detailed explained in draw_shapes.h */
  player1.curr_x = (screenWidth / 2) - 17;
  player1.curr_y = (screenHeight / 2) - 12;
  player1.old_x = (screenWidth / 2) - 17;
  player1.old_y = (screenHeight /2) - 12;
  player1.width = 17;
  player1.height = 12;
  
  /* Init default pipe to default values */
  init_pipetype(0);
  
  /* Pipe type starts at type 0 and doesn't need a new one yet. */
  pipe1.curr_type = 0;
  pipe1.ready_newtype = 0;
}

void
displayBackground(void){      /* Displays Various Clouds */
  displayCloud(5,5);
  displayCloud(12,8);

  displayCloud(90, 10);
  displayCloud(97, 14);
  displayCloud(93, 9);

  displayCloud(53, 25);
  displayCloud(100,45);

  displayCloud(15, 48);
  displayCloud(23, 58);
  displayCloud(13, 135);
 
  displayCloud(85, 85);
  displayCloud(90, 90);
  displayCloud(17, 95);

  displayCloud(75, 123);

  displayCloud(10, 130);
  displayCloud(110, 140);
}

void
displayCloud(int x, int y){
  /* Pixel art for a cloud */
  // These are the color codes
  u_int cloudcolor1 = COLOR_WHITE;
  u_int cloudcolor2 = COLOR_CLOUD1;
  u_int cloudcolor3 = COLOR_CLOUD2;

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
draw_moving_game(void)
{
  if(pipe1.ready_newtype == 1) {       /* If ready for a new pipe type */
                                       /* tempVal = the next pipe type (random) */
    tempVal = ((randomVal * pipe1.curr_type) + (score + 1)) % 3;
    if (tempVal == pipe1.curr_type) {  /* The pipe new type will be the same as before */
      pipeRepeat += 1;                 /* Increase the repeated pipe type count */
    } else if (pipeRepeat == 2) {      /* pipe type has repeated three times so new type */
      pipe1.curr_type = (pipe1.curr_type + 1) % 3;
      pipeRepeat = 0;                  /* reset pipe Repeat to 0 */
    } else {
      pipe1.curr_type = tempVal;       /* curr type is set to the random value */
    }
    
    init_pipetype(pipe1.curr_type);
    pipe1.ready_newtype = 0;           /* no longer ready for a new pipe type */
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

  /* Set the values of the pipe to be blanked */
  left_col = pipe1.old_pipe1_col;
  top_row  = pipe1.old_pipe1_row;
  height = pipe1.height1;
  width = pipe1.width1;

  left_col2 = pipe1.old_pipe2_col;
  top_row2 = pipe1.old_pipe2_row;
  height2 = pipe1.height2;
  width2 = pipe1.width2;
  
  // Blank out the old pipe
  fillRectangle(left_col, top_row, width, height, background_color);
  // Blank out the old bottom piece of pipe
  fillRectangle(left_col2, top_row2, width2, height2, background_color);

  //If the player isn't in the old location then blank out
  if(player1.curr_y != player1.old_y){
      // Blank out the old player
    fillRectangle(player1.old_x, player1.old_y, player1.width, player1.height, background_color);
  }
  // Replace the clouds missing
  displayBackground();

  // draw and update the pipe
  moving_pipe(&pipe1);

  // Switch Control
  if (switches & SW1) {           /* If Switch 1 is down */       
    moving_player(10);            /* Move Player by 10 pixel down */
  } else if (switches & SW2) {    /* If Switch 2 is down */
    moving_player(-10);           /* Move Player by 10 pixels up */
  } else if (switches & SW3) {    /* If Switch 3 is down */
    moving_player(0);             /* Player 1 doesn't move but goes to 0,0 */
    player1.old_x = 0;
    player1.curr_y = 0;
  } else if (switches & SW4) {    /* if Switch 4 is down  */
    fillRectangle(player1.old_x, player1.old_y, 17, 12, background_color);

    /* Player 1 doesn't move but goes to 0,151 */
    player1.old_y = 151;
    player1.curr_y = 151;
  } else {
    moving_player(0);
  }
  
  // Show the score
  displayScore(55, 10, score, background_color);

}

void
moving_pipe(pipe *to_draw)
{
  // The value pixels to be changed per x and y
  static int x_vel = 10;
  static int y_vel = 0;

  // Values to draw current pipe location
  int left_col = to_draw->pipe1_col;
  int top_row  = to_draw->pipe1_row;
  int left_col2 = to_draw->pipe2_col;
  int top_row2 = to_draw->pipe2_row;

  // Color code for the pipe
  unsigned int color = COLOR_BLACK;
  // draw pipe at current position
  fillRectangle(left_col, top_row, to_draw->width1, to_draw->height1, color);
  fillRectangle(left_col2, top_row2, to_draw->width2, to_draw->height2, color);

  // save current position
  to_draw->old_pipe1_row = to_draw->pipe1_row;
  to_draw->old_pipe1_col = to_draw->pipe1_col;
  to_draw->old_pipe2_row = to_draw->pipe2_row;
  to_draw->old_pipe2_col = to_draw->pipe2_col;

  // update position
  to_draw->pipe1_row += y_vel;
  to_draw->pipe1_col -= x_vel;
  to_draw->pipe2_row += y_vel;
  to_draw->pipe2_col -= x_vel;

  /* If either the top or bottom of the pipe hit the left screen reset */
  if ( (to_draw->old_pipe1_col ) <= 0 ||
       (to_draw->old_pipe2_col ) <= 0) {
    
    /* Set a sound for score! */
    buzzer_set_period(2000);
    
    // Set to Original Values.
    fillRectangle(to_draw->old_pipe1_col, to_draw->old_pipe1_row, to_draw->width1, to_draw->height1, background_color);
    fillRectangle(to_draw->old_pipe2_col, to_draw->old_pipe2_row, to_draw->width2, to_draw->height2, background_color);

    /* score increase! */
    score+= 1;

    // Set Pipe ready for new type
    pipe1.ready_newtype = 1;

    //Turn buzzer off for score
    buzzer_set_period(0);
  }
}

void
chooseSkin(void){
  if ((switches & SW1) && switchState == 0) {
    buzzer_set_period(1560); // Cycled Skin Noise
    skinType = skinType + 1; // Skin Type Choice increases by 1
    switchState = 2;         // Out of Bond state to delay cycle    
  }
  if (skinType == 8) {       // Skin out of range
    skinType = 0;            // Skin type goes back to 0
  }

  // Blank out the old player and set the skin type and display
  fillRectangle(player1.curr_x, player1.curr_y, player1.width, player1.height, COLOR_BLACK);
  player1.skin_type = skinType;
  player1.curr_x = (screenWidth / 2) - 10;
  player1.curr_y = (screenHeight / 2) - 20;
  draw_player(&player1);
}

void
draw_player(player *to_draw)
{
  // Gets the x,y start point and skin type. 
  int x = to_draw->curr_x;
  int y  = to_draw->curr_y;

  // Based on player skin choice
  int skin = to_draw->skin_type;

  // Default char colors
  u_int white = COLOR_WHITE;
  u_int blk = COLOR_BLACK;
  u_int skincolor1 = COLOR_YELLOW;
  u_int skincolor2 = COLOR_GREEN_YELLOW;
  u_int lipcolor = COLOR_PINK;

  //Depending on skin choice
  switch(skin) {
  case 1:
    skincolor1 = COLOR_ORANGE;
    skincolor2 = COLOR_DARK_ORANGE;
    break;
  case 2:
    skincolor1 = COLOR_GREEN;
    skincolor2 = COLOR_DARK_GREEN;
    break;
  case 3:
    skincolor1 = COLOR_GOLD;
    skincolor2 = COLOR_GOLDENROD;
    break;
  case 4:
    skincolor1 = COLOR_SPRING_GREEN;
    skincolor2 = COLOR_DARK_OLIVE_GREEN;
    break;
  case 5:
    skincolor1 = COLOR_GRAY;
    skincolor2 = COLOR_CHOCOLATE;
    break;
  case 6:
    skincolor1 = COLOR_RED;
    skincolor2 = COLOR_ORANGE_RED;
    break;
  case 7:
    skincolor1 = COLOR_VIOLET;
    skincolor2 = COLOR_DARK_VIOLE;
    break;
  }
  //First ROW
  fillRectangle(x + 6, y, 6, 1, blk);
  //Second ROW
  fillRectangle(x + 4, y + 1, 2, 1, blk);
  fillRectangle(x + 6, y + 1, 4, 1, skincolor1);
  fillRectangle(x + 10, y + 1, 1, 1, blk);
  fillRectangle(x + 11, y + 1, 1, 1, white);
  fillRectangle(x + 12, y + 1, 1, 1, blk);
  //Third Row
  fillRectangle(x + 3, y + 2, 1, 1, blk);
  fillRectangle(x + 4, y + 2, 5, 1, skincolor1);
  fillRectangle(x + 9, y + 2, 1, 1, blk);
  fillRectangle(x + 10, y + 2, 3, 1, white);
  fillRectangle(x + 13, y + 2, 1, 1, blk);
  //Fourth Row
  fillRectangle(x + 1, y + 3, 4, 1, blk);
  fillRectangle(x + 5, y + 3, 4, 1, skincolor1);
  fillRectangle(x + 9, y + 3, 1, 1, blk);
  fillRectangle(x + 10, y + 3, 2, 1, white);
  fillRectangle(x + 12, y + 3, 1, 1, blk);
  fillRectangle(x + 13, y+ 3, 1, 1, white);
  fillRectangle(x + 14, y + 3, 1, 1, blk);
  //Fifth Row
  fillRectangle(x, y + 4, 1, 1, blk);
  fillRectangle(x + 1, y + 4, 4, 1, white);
  fillRectangle(x + 5, y + 4, 1, 1, blk);
  fillRectangle(x + 6, y + 4, 3, 1, skincolor1);
  fillRectangle(x + 9, y + 4, 1, 1, blk);
  fillRectangle(x + 10, y + 4, 2, 1, white);
  fillRectangle(x + 12, y + 4, 1, 1, blk);
  fillRectangle(x + 13, y + 4, 1, 1, white);
  fillRectangle(x + 14, y + 4, 1, 1, blk);
  //Sixth Row
  fillRectangle(x, y + 5, 1, 1, blk);
  fillRectangle(x + 1, y + 5, 5, 1, white);
  fillRectangle(x + 6, y + 5, 1, 1, blk);
  fillRectangle(x + 7, y + 5, 3, 1, skincolor1);
  fillRectangle(x + 10, y + 5, 1, 1, blk);
  fillRectangle(x + 11, y + 5, 3, 1, white);
  fillRectangle(x + 13, y + 5, 1, 1, blk);
  //Seventh Row
  fillRectangle(x, y + 6, 1, 1, blk);
  fillRectangle(x + 1, y + 6, 1 , 1, skincolor1);
  fillRectangle(x + 2, y + 6, 3, 1, white);
  fillRectangle(x + 5, y + 6, 1, 1, skincolor1);
  fillRectangle(x + 6, y + 6, 1, 1, blk);
  fillRectangle(x + 7, y + 6, 4, 1, skincolor1);
  fillRectangle(x + 11, y + 6, 5, 1, blk);
  //Eigth Row
  fillRectangle(x + 1, y + 7, 1, 1, blk);
  fillRectangle(x + 2, y + 7, 3 , 1, skincolor1);
  fillRectangle(x + 5, y + 7, 1, 1, blk);
  fillRectangle(x + 6, y + 7, 4, 1, skincolor1);
  fillRectangle(x + 10, y + 7, 1, 1, blk);
  fillRectangle(x + 11, y + 7, 5, 1, lipcolor);
  fillRectangle(x + 16, y + 7, 1, 1, blk);
  //Ninth Row
  fillRectangle(x + 2, y + 8, 3, 1, blk);
  fillRectangle(x + 5, y + 8, 4, 1, skincolor2);
  fillRectangle(x + 9, y + 8, 1, 1, blk);
  fillRectangle(x + 10, y + 8, 1, 1, lipcolor);
  fillRectangle(x + 11, y + 8, 5, 1, blk);
  //Tenth Row
  fillRectangle(x + 4, y + 9, 1, 1, blk);
  fillRectangle(x + 5, y + 9, 5, 1, skincolor2);
  fillRectangle(x + 10, y + 9, 1, 1, blk);
  fillRectangle(x + 11, y + 9, 4, 1, lipcolor);
  fillRectangle(x + 15, y + 9, 1, 1, blk);
  //Eleventh Row
  fillRectangle(x + 5, y + 10, 2, 1, blk);
  fillRectangle(x + 7, y + 10, 4, 1, skincolor2);
  fillRectangle(x + 11, y + 10, 5, 1, blk);
  //LastRow
  fillRectangle(x + 7, y + 11, 4, 1, blk);
}

void
moving_player(int n)
{
  int y_vel = n;
  
  // draw at the new position
  draw_player(&player1);

  // check if player hit pipe
  hit_detection();
  
  // save current position
  player1.old_x = player1.curr_x;
  player1.old_y = player1.curr_y;
  
  // Updates the new position
  player1.curr_y += y_vel;

  // Uses current y location of player as a random val for next pipe type
  randomVal = player1.curr_y;
  
}

void hit_detection(void){
  // check boundaries, see if rectangle has hit the top or bottom
  if (player1.curr_y <= 0 ) {                                     // TOP
    //BLANK
     fillRectangle(player1.old_x, player1.curr_y, player1.width, player1.height, background_color);
    player1.curr_y = 150;                                         // Set to bottom of screen
  } else if ((player1.curr_y + player1.height) >= screenHeight ){ // BOTTOM
    //BLANK
    fillRectangle(player1.old_x, player1.curr_y, player1.width, player1.height, background_color); 
    player1.curr_y = 1;                                           // Set to top of screen
  }
  
  if(
       /* If players top hit the bottom part of top pipe AND ( (players curr_x is more than top pipe x and less than top pipe x + width of top pipe) OR (players curr_x + player width is greater than top pipe x and less than top pipe x + width of top pipe) ) AND */
     (
      ( player1.curr_y <= pipe1.height1 ) &&     /* If hit the bottom part of top pipe */
       ( ( ( player1.curr_x >= pipe1.old_pipe1_col ) &&
         ( player1.curr_x <= (pipe1.old_pipe1_col + pipe1.width1) )
         ) ||
         ( ( (player1.curr_x + player1.width) >= pipe1.old_pipe1_col ) &&
	   ( (player1.curr_x + player1.width) <= (pipe1.old_pipe1_col + pipe1.width1) )
	 )
       )
     ) ||
       /* If players bottom hit the top part of bottom pipe AND ( (players curr_x is more than bottom pipe x and less than bottom pipe x + width of bottom pipe) OR (players curr_x + player width is greater than bottom pipe x and less than bottom pipe x + width of bottom pipe) ) */
     (
       ( (player1.curr_y + player1.height) >= pipe1.old_pipe2_row ) && 
       ( ( ( player1.curr_x >= pipe1.old_pipe2_col ) &&
	 ( player1.curr_x <= (pipe1.old_pipe2_col + pipe1.width2) )
         ) ||
         ( ( (player1.curr_x + player1.width) >= pipe1.old_pipe2_col ) &&
	 ( (player1.curr_x + player1.width) <= (pipe1.old_pipe2_col + pipe1.width2) )
	 )
       )
     )
    )
    {
      if (score > highScore) {   /* Set highScore */
	 highScore = score;
       }
      
      master = 3;               /* Game Over state */
      redrawScreen2 = 1;       /* Trigger a refresh screen for Game Over */
      textState = 3;           /* Switch text state for game over */
      seconds = 0;
      gameOverNote();         /* Game over noise */
  }
}

  
