
typedef struct sprite //All veriables per sprite
{
     int type;      //static, key, enemy
     int state;     //on off
     int map;       //texture to show
     float x, y, z; //position
} sprite;


sprite sp[4];
int depth[120]; //hold wall line depth to compare for sprite depth


void drawSprite()
{
     int x, y, s;
     if (px < sp[0].x + 30 && px > sp[0].x - 30 && py < sp[0].y + 30 && py > sp[0].y - 30)
     {
          sp[0].state = 0;
     } //pick up key
     if (px < sp[3].x + 30 && px > sp[3].x - 30 && py < sp[3].y + 30 && py > sp[3].y - 30)
     {
          gameState = 4;
     } //enemy kills

     //enemy attack
     int spx = (int)sp[3].x >> 6, spy = (int)sp[3].y >> 6;                       //normal grid position
     int spx_add = ((int)sp[3].x + 15) >> 6, spy_add = ((int)sp[3].y + 15) >> 6; //normal grid position plus     offset
     int spx_sub = ((int)sp[3].x - 15) >> 6, spy_sub = ((int)sp[3].y - 15) >> 6; //normal grid position subtract offset
     if (sp[3].x > px && mapW[spy * 8 + spx_sub] == 0)
     {
          sp[3].x -= 0.04 * fps;
     }
     if (sp[3].x < px && mapW[spy * 8 + spx_add] == 0)
     {
          sp[3].x += 0.04 * fps;
     }
     if (sp[3].y > py && mapW[spy_sub * 8 + spx] == 0)
     {
          sp[3].y -= 0.04 * fps;
     }
     if (sp[3].y < py && mapW[spy_add * 8 + spx] == 0)
     {
          sp[3].y += 0.04 * fps;
     }

     for (s = 0; s < 4; s++)
     {
          float sx = sp[s].x - px; //temp float variables
          float sy = sp[s].y - py;
          float sz = sp[s].z;

          float CS = cos(degToRad(pa)), SN = sin(degToRad(pa)); //rotate around origin
          float a = sy * CS + sx * SN;
          float b = sx * CS - sy * SN;
          sx = a;
          sy = b;

          sx = (sx * 108.0 / sy) + (120 / 2); //convert to screen x,y
          sy = (sz * 108.0 / sy) + (80 / 2);

          int scale = 32 * 80 / b; //scale sprite based on distance
          if (scale < 0)
          {
               scale = 0;
          }
          if (scale > 120)
          {
               scale = 120;
          }

          //texture
          float t_x = 0, t_y = 31, t_x_step = 31.5 / (float)scale, t_y_step = 32.0 / (float)scale;

          for (x = sx - scale / 2; x < sx + scale / 2; x++)
          {
               t_y = 31;
               for (y = 0; y < scale; y++)
               {
                    if (sp[s].state == 1 && x > 0 && x < 120 && b < depth[x])
                    {
                         int pixel = ((int)t_y * 32 + (int)t_x) * 3 + (sp[s].map * 32 * 32 * 3);
                         int red = sprites[pixel + 0];
                         int green = sprites[pixel + 1];
                         int blue = sprites[pixel + 2];
                         if (red != 255 && green != 0 && blue != 255) //dont draw if purple
                         {
                              glPointSize(8);
                              glColor3ub(red, green, blue);
                              glBegin(GL_POINTS);
                              glVertex2i(x * 8, sy * 8 - y * 8);
                              glEnd(); //draw point
                         }
                         t_y -= t_y_step;
                         if (t_y < 0)
                         {
                              t_y = 0;
                         }
                    }
               }
               t_x += t_x_step;
          }
     }
}