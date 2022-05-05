#ifndef stateMachines_included
#define stateMachines_included


extern int master;          /* Controls the overall main state of the program */
extern int nextState;       /* Controls if nextState needs to be moved */
extern int textState;       /* Controls the textState */
extern int switchState;     /* Controls the switchState */
extern int resetState;      /* Controls if the game needs to be reset */

extern int highScore;       /* Controls the highScore */
extern int seconds;         /* Elapsed seconds that have past */

extern short redrawScreen;  /* Controls if the screen needs to be redrawn */
extern short redrawScreen2; /* Controls if the special event needs to be redrawn */

/* This function displays score */
void displayScore(int x, int y, int score, int color);

/* This function is used to displayText */
void displayText(void);

/* This function is used to display a Splash Screen */
void splashScreen(void);

/* This function is the introScreen State */
void introScreen(void);

/* This function is the playGame State */
void playGame(void);

/* This function is used to reset playGame state */
void resetGame(void);

/* This function is the GameOver State */
void gameOver(void); 
#endif
