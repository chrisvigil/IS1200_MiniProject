#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

uint8_t frame[512];
uint8_t bird[9][2] = {{0,16},{2,16},{3,16},{0,17},{1,17},{2,17},{0,18},{1,18},{2,18}};
uint8_t count = 0;
uint8_t jump = 0;

void new_frame_1(void)
{
    /* sets all pixels in frame to off
    int i = 0;
    for (i = 0; i < 384; i++)
    {
        frame[i] = 255;
    }
    for (i; i < 512; i++)
    {
        if (i%2)
            frame[i] = 0xbf;
        else
            frame[i] = 0x7f;
    }*/

    int i = 0;
    int j;
    for (i; i < 3; i++)
    {
        for (j = 0; j < 91; j++)
            frame[(128 * i) + j] = 255;
        for (j; j < 128; j ++)
            frame[(128 * i) + j] = 0;
    }
    for (i = 384; i < 475; i++)
    {
        if (i%2)
            frame[i] = 0xbf;
        else
            frame[i] = 0x7f;
    }
    for (i; i < 512; i++)
    {
        frame[i] = 0;
    }


}

void bird_reset(void)
{
    bird [0][0] = 0;
    bird [0][1] = 16;
    bird [1][0] = 2;
    bird [1][1] = 16;
    bird [2][0] = 3;
    bird [2][1] = 16;
    bird [3][0] = 0;
    bird [3][1] = 17;
    bird [4][0] = 1;
    bird [4][1] = 17;
    bird [5][0] = 2;
    bird [5][1] = 17;
    bird [6][0] = 0;
    bird [6][1] = 18;
    bird [7][0] = 1;
    bird [7][1] = 18;
    bird [8][0] = 2;
    bird [8][1] = 18;
}

draw_pipe(uint8_t x_point, uint8_t y_point) //Punkten i början på sista raden där glappet börjar
{
  int i = 0; //y-värdet
  int j = 0; //x-värdet
  for (i; i < y_point; i++)
  {
      for (j = x_point; j < (x_point+5); j++)
        draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
  }

  i+=12;
  for (i; i < 32; i++)
  {
      for (j = x_point; j < (x_point+5); j++)
        draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
  }
}



void stage1_int(void){
    count++;
    /* Clears frame */
    new_frame_1();

    /* Draws bird in frame */
    int i = 0;
    for (i; i < 9; i++)
    {
        draw_point(bird[i][0],bird[i][1], frame);
    }

    draw_pipe(30, 12);
    draw_pipe(45, 7);
    draw_pipe(60, 10);

    /* Sends frame to display */
    display_image(frame);

    // detectes top and bottom edge
    if (bird[8][1] >= 30)
        bird_reset();
    if (bird[0][1] <= -1)
        bird_reset();

    // updates birds possition
    if (count >= 4)
    {
        count = 0;
        /* Moves bird 1 pixel along the x-axis*/
        for (i = 0; i < 9; i++)
        {
            // x values
            if (bird[i][0] >= 90)
            bird[i][0] = 0;
            else
            (bird[i][0])++;

            // y values
            if (bird[i][1] >= 31)
                bird[i][1] = 0;
            else
            {
                if (jump <= 0)
                    (bird[i][1])++;
                else
                {
                    (bird[i][1])--;
                }
            }
        }
        if (jump > 0)
            jump--;

    }

        /*
        if (jump == 0)
            IECSET(1) = 1;*/
}

void stage1_work(void)
{
    int btnstate = getbtns();
    if (btnstate & 8)
    {
        if (jump == 0)
            jump = 5;
    }
    else if (btnstate & 1)
        stage = 0;
}
