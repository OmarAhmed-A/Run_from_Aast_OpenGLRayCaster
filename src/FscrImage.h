
void imageFullScr(int v) //draw any full screen image. 120x80 pixels
{
     int x, y;
     int *T;
     if (v == 1)
     {
          T = title;
     }
     if (v == 2)
     {
          T = won;
     }
     if (v == 3)
     {
          T = lost;
     }
     for (y = 0; y < 80; y++)
     {
          for (x = 0; x < 120; x++)
          {
               int pixel = (y * 120 + x) * 3;
               int red = T[pixel + 0] * fade;
               int green = T[pixel + 1] * fade;
               int blue = T[pixel + 2] * fade;
               glPointSize(8);
               glColor3ub(red, green, blue);
               glBegin(GL_POINTS);
               glVertex2i(x * 8, y * 8);
               glEnd();
          }
     }
     if (fade < 1)
     {
          fade += 0.001 * fps;
     }
     if (fade > 1)
     {
          fade = 1;
     }
}