#ifndef _DRAW_SHAPES_H_
#define _DRAW_SHAPES_H_

#include <lcdutils.h>

typedef struct rect_st {
  int rect1_row;
  int rect1_col;
  int old_rect1_row;
  int old_rect1_col;
  u_char height1;
  u_char width1;

  int rect2_row;
  int rect2_col;
  int old_rect2_row;
  int old_rect2_col;
  u_char height2;
  u_char width2;
  int ready_newtype;
} rectangle;

typedef struct ctrl_st {
  int ready_newtype;
  int curr_type;
  int random_val;
} ctrlType;  

typedef struct cir_st {
  int cir_x;
  int cir_y;
  int old_cir_x;
  int old_cir_y;
  int r;
} circle;

extern u_int background_color;

/* initializes rectangle type values*/
void init_rectype(void);

/* initialize the player */
void init_player(void);

/* handles erasing and updating all the shapes */
void draw_moving_shapes(void);

/* handles a single rectangle, updates its 
   position and draws it at its new location */
void moving_rectangle(rectangle* to_draw);

/* handles a single circle, updates its 
   position and draws it at its new amount given */
void moving_circle(int n);

/* draws a rectangle */
void draw_rectangle(void);

/* draws a triangle */
void draw_triangle(void);

/* draws a circle with the given parameters */
void draw_circle(int x, int y, int r, u_int color);

#endif // _DRAW_SHAPES_H_
