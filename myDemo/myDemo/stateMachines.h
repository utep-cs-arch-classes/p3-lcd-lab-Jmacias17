#ifndef stateMachines_included
#define stateMachines_included


extern int master;          /* Controls the overall main state of the program */
extern int nextState;       /* Controls if nextState needs to be moved */
extern int textState;       /* Controls the textState */
extern int switchState;     /* Controls the switchState */

extern short redrawScreen;  /* Controls if the screen needs to be redrawn */
extern short redrawScreen2; /* Controls if the special event needs to be redrawn */

/* This function is used to displayText */
void displayText();

/* This function is used to display a Splash Screen */
void splashScreen(void);

/* This function is the introScreen State */
void introScreen();

/* This function is the playGame State */
void playGame();

/* This function is used to reset playGame state */
void resetGame();
/* This function is the GameOver State */
void gameOver(); 
#endif
