#ifndef _DRAW_SHAPES_H_
#define _DRAW_SHAPES_H_

#include <msp430.h>
#include <lcdutils.h>
#include "lcddraw.h"
#include "switches.h"
#include "buzzer.h"

#define COLOR_CLOUD1           0xd9e0
#define COLOR_CLOUD2           0xbfc0
typedef struct pipe_st {
                        /* This is Pipe 1 (Top Pipe) */
  int pipe1_row;        /* The x starting coord point */
  int pipe1_col;        /* The y starting coord point */
  int old_pipe1_row;    /* The old x starting coord point */
  int old_pipe1_col;    /* The old y starting coord point */
  u_char height1;       /* The height of the pipe (pipe1_row + height1) leads to end point of y. */
  u_char width1;        /* The width of the pipe (pipe2_col + width1) leads to end point of x. */

  int pipe2_row;        /* Same as above but for pipe2 (bottom) */
  int pipe2_col;
  int old_pipe2_row;
  int old_pipe2_col;
  u_char height2;
  u_char width2;

  int curr_type;
  int ready_newtype;    /* If a new type of pipe format is ready to be applied 1 else 0 */
} pipe;

typedef struct play_st {
  int curr_x;           /* This is the x starting coord point */
  int curr_y;           /* This is the y starting coord point */
  int old_x;            /* This is the old x starting coord point */
  int old_y;            /* This is the old y starting coord point */
  u_char height;        /* This is the width of the player (curr_x + height) leads to end point of y */
  u_char width;         /* This is the height of the player (curr_y + width leads to the end point of x */
  int skin_type;        /* The color type of the sprite */
} player;

extern int score;
extern u_int background_color;
extern int skinType;

/* initializes the n (type) pipe type values*/
void init_pipetype(int n);

/* initialize the player */
void init_player(void);

/* Choose a skin type */
void chooseSkin(void);

/* displays the backgroundScreen with clouds */
void displayBackground(void);

/* displays a single cloud at x, y coord */
void displayCloud(int x, int y);

/* handles erasing and updating all the objects in the game */
void draw_moving_game(void);

/* handles a single pipe, updates its 
   position and draws it at its new location */
void moving_pipe(pipe* to_draw);

/* handles a single player, updates its 
   position and draws it at its new amount given */
void moving_player(int n);

/* draws a pipe */
void draw_pipe(void);

/* draw the player */
void draw_player(player* to_draw);

/* Checks if pipe has hit player */
void hit_detection(void);
#endif // _DRAW_SHAPES_H_
