

// Draw the sky with the correct rotation based on the player's rotation
void drawSky() // draw sky and rotate based on player rotation
{
     int x, y;
     for (y = 0; y < 40; y++)
     {
          for (x = 0; x < 120; x++)
          {
               int xo = (int)pa * 2 - x;
               if (xo < 0)
               {
                    xo += 120;
               }
               xo = xo % 120; // return 0-120 based on player angle
               int pixel = (y * 120 + xo) * 3;
               int red = sky[pixel + 0];
               int green = sky[pixel + 1];
               int blue = sky[pixel + 2];
               glPointSize(8);
               glColor3ub(red, green, blue);
               glBegin(GL_POINTS);
               glVertex2i(x * 8, y * 8);
               glEnd();
          }
     }
}