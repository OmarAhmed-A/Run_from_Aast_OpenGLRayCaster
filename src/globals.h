clock_t tik;
FILE *fptr;
float px, py, pdx, pdy, pa;
float frame1, frame2, fps;
int gameState = 0, timer = 0, n=0; //game state. init 0, start screen , game loop, win/lose
float fade = 0;               //the 3 screens can fade up from black

int lvl= 0;

int * sky;