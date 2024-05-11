// WADS to move player, E open door after picking up the key

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#include <glut.h> // OpenGL Graphics Utility Library (GLUT)

#define _USE_MATH_DEFINES
#include <math.h>

#include "../Textures/All_Textures.ppm"
#include "../Textures/sky.ppm"
#include "../Textures/title.ppm"
#include "../Textures/won.ppm"
#include "../Textures/lost.ppm"
#include "../Textures/sprites.ppm"

#include "globals.h"

#include "funcs.h"

#include "Map.h"
#include "sprite.h"
#include "walls.h"
#include "FscrImage.h"
#include "Button.h"
#include "sky.h"

#define Maxplayers 20

#define Width 960
#define Height 640

typedef struct player // player name and score
{
     float score;
     char name[30];
} player;
player p;
player all[Maxplayers];

// Transforms angle from degrees to radians
float degToRad(float a) { return a * M_PI / 180.0; }

// Fix angle to be between 0 and 359
float FixAng(float a)
{
     if (a > 359)
     {
          a -= 360;
     }

     if (a < 0)
     {
          a += 360;
     }

     return a;
}

// olf func from v2 may become useful?
/*
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}
*/

//-----------------------------------------------------------------------------



// init all variables when game starts
void init()
{
     glClearColor(0.3, 0.3, 0.3, 0);
     px = 150;
     py = 400;
     pa = 90;
     pdx = cos(degToRad(pa));
     pdy = -sin(degToRad(pa)); // init player

     mapW[19] = 4;
     mapW[26] = 4; // close doors

     sp[0].type = 1;
     sp[0].state = 1;
     sp[0].map = 0;
     sp[0].x = 1.5 * 64;
     sp[0].y = 5 * 64;
     sp[0].z = 20; // key

     sp[1].type = 2;
     sp[1].state = 1;
     sp[1].map = 1;
     sp[1].x = 1.5 * 64;
     sp[1].y = 4.5 * 64;
     sp[1].z = 0; // light 1

     sp[2].type = 2;
     sp[2].state = 1;
     sp[2].map = 1;
     sp[2].x = 3.5 * 64;
     sp[2].y = 4.5 * 64;
     sp[2].z = 0; // light 2

     sp[3].type = 3;
     sp[3].state = 1;
     sp[3].map = 2;
     sp[3].x = 2.5 * 64;
     sp[3].y = 2 * 64;
     sp[3].z = 20; // enemy
}

void display()
{
     // frames per second
     frame2 = glutGet(GLUT_ELAPSED_TIME);
     fps = (frame2 - frame1);
     frame1 = glutGet(GLUT_ELAPSED_TIME);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     if (gameState == 0)
     {
          init();
          fade = 0;
          timer = 0;
          gameState = 1;
     } // init game
     if (gameState == 1)
     {
          imageFullScr(1);
          timer += 1 * fps;
          if (timer > 2000)
          {
               fade = 0;
               timer = 0;
               gameState = 2;
          }
     } // start screen
     if (gameState == 2) // The main game loop
     {
          // buttons
          if (Keys.a == 1)
          {
               pa += 0.2 * fps;
               pa = FixAng(pa);
               pdx = cos(degToRad(pa));
               pdy = -sin(degToRad(pa));
          }
          if (Keys.d == 1)
          {
               pa -= 0.2 * fps;
               pa = FixAng(pa);
               pdx = cos(degToRad(pa));
               pdy = -sin(degToRad(pa));
          }

          int xo = 0;
          if (pdx < 0)
          {
               xo = -20;
          }
          else
          {
               xo = 20;
          } // x offset to check map
          int yo = 0;
          if (pdy < 0)
          {
               yo = -20;
          }
          else
          {
               yo = 20;
          } // y offset to check map
          int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0, ipx_sub_xo = (px - xo) / 64.0; // x position and offset
          int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0; // y position and offset
          if (Keys.w == 1)                                                                   // move forward
          {
               if (mapW[ipy * mapX + ipx_add_xo] == 0)
               {
                    px += pdx * 0.2 * fps;
               }
               if (mapW[ipy_add_yo * mapX + ipx] == 0)
               {
                    py += pdy * 0.2 * fps;
               }
          }
          if (Keys.s == 1) // move backward
          {
               if (mapW[ipy * mapX + ipx_sub_xo] == 0)
               {
                    px -= pdx * 0.2 * fps;
               }
               if (mapW[ipy_sub_yo * mapX + ipx] == 0)
               {
                    py -= pdy * 0.2 * fps;
               }
          }
          drawSky();
          drawRays2D();
          drawSprite();
          if ((int)px >> 6 == 1 && (int)py >> 6 == 1)
          {
               fade = 0;
               timer = 0;
               gameState = 3;
          } // Entered block 1, Win game!!
     }

     if (gameState == 3)
     {
          imageFullScr(2);
          timer += 1 * fps;
          if (timer > 2000)
          {
               fade = 0;
               timer = 0;
               printf("thats awsome man!");
               clock_t tok = clock();
               double time_spent = (double)(tok - tik) / CLOCKS_PER_SEC;
               p.score = time_spent;
               printf("\n%s's score was %.2f ", p.name, p.score);
               fptr = fopen("scores.txt", "a");
               fprintf(fptr, "\n%s %.2f", p.name, p.score);
               fclose(fptr);
               glutDestroyWindow((int)*display);

               return;
          }
     } // won screen
     if (gameState == 4)
     {
          imageFullScr(3);
          timer += 1 * fps;
          if (timer > 2000)
          {
               fade = 0;
               timer = 0;
               printf("damn that sucks\n");
               clock_t tok = clock();
               p.score = (double)(tok - tik) / CLOCKS_PER_SEC;
               printf("%s has unfortiantly lost, try again ", p.name, p.score);
               printf("\npress enter-key to exit");
               getchar();

               glutDestroyWindow((int)*display);

               return;
          }
     } // lost screen

     glutPostRedisplay();
     glutSwapBuffers();
}

void resize(int w, int h) // screen window rescaled, snap back
{
     glutReshapeWindow(w, h);
}
void bsortStruct(struct player list[20], int s)
{
     int i, j;
     player temp;

     for (i = 0; i < s - 1; i++)
     {
          for (j = 0; j < (s - 1 - i); j++)
          {
               if (list[j].name != "@")
                    if (list[j].score > list[j + 1].score) // strcmp(list[j].name , list[j + 1].name)>0 condition to sort by name
                    {
                         temp = list[j];
                         list[j] = list[j + 1];
                         list[j + 1] = temp;
                    }
          }
     }
}

int main(int argc, char *argv[])
{
     char ch;
     for (int c = 0; c < Maxplayers; c++)
     {
          all[c].score = 0.0;
          strcpy(all[c].name, "@");
     } // initiallise struct array with weird values

     fptr = fopen("scores.txt", "r");
     if (fptr == NULL)
          printf("Error opening scores file");

     for (int q = 0; q < Maxplayers; q++)
     {

          fscanf(fptr, "%s", all[q].name);
          fflush(stdin);
          fscanf(fptr, "%f", &all[q].score);
          n++;

          if ((ch = getc(fptr)) != EOF)
               continue;
          break;
     }
     fclose(fptr);

     bsortStruct(all, n); // sort all scores in struct array

     fptr = fopen("scores.txt", "w");
     if (fptr == NULL)
          printf("Error opening scores file");
     for (int e = 0; e < n - 1; e++)
     {
          if (e == n - 2)
               fprintf(fptr, "%s %.2f", all[e].name, all[e].score);
          else
               fprintf(fptr, "%s %.2f\n", all[e].name, all[e].score);
     }
     fclose(fptr);

     printf("top five scores:\n");
     for (int w = 0; w < 5; w++)
     {
          if (all[w].name != "@")
          {
               printf("%d)%s's score was:%.2f seconds\n", w + 1, all[w].name, all[w].score);
          }
          else
               break;
     }

     printf("please enter your name\n");
     gets(p.name);

     glutInit(&argc, argv);

     // initialise mode of display
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

     // set size of window
     glutInitWindowSize(Width, Height);

     // init window pos to center in display
     glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - Width / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - Height / 2);
     glutCreateWindow("Omar Ahmed-Applied project");
     gluOrtho2D(0, Width, Height, 0);
     init();
     clock_t tik = clock();
     glutDisplayFunc(display);
     glutReshapeFunc(resize);
     glutKeyboardFunc(ButtonDown);
     glutKeyboardUpFunc(ButtonUp);
     glutMainLoop();
     printf("end"); // never runs
}
