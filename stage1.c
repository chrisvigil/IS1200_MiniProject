#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"
#include <stdlib.h>

uint8_t frame[512];
uint8_t bird[9][2] = {{0,16},{2,16},{3,16},{0,17},{1,17},{2,17},{0,18},{1,18},{2,18}};
uint8_t count = 0;
uint8_t jump = 0;

uint8_t pipespaces[3]; //Random generator, TO DO

void *stdout = (void *) 0;

void random_pipes(void)
{
  int i = 0;
  srand(TMR2);
  for (i; i < 3; i++)
  {
    pipespaces[i] = (rand() % 9) + 3;
  }
}

int pipe_collision(int pipe)
{
    int i = 0;
    for(i; i < 9; i+=2)  //Checks collision for the four corners of the bird
    {
      if ( (bird[i][0] >= (30 + (20*pipe)) && bird[i][0] <= (35 + (20*pipe)) ) && (bird[i][1] <= pipespaces[pipe] || bird[i][1] >= (pipespaces[pipe] + 15)))
        return 1;
    }
    return 0;
}

int collision(void) //Collision detection
{
    // detectes top and bottom edge
    if (bird[8][1] >= 30)
        return 1;
    if (bird[0][1] <= -1)
        return 1;

    int col = 0;
    if(bird[0][0] > 69)
        col = pipe_collision(2);
    else if (bird[0][0] > 49)
        col = pipe_collision(1);
    else if (bird[0][0] > 29)
        col = pipe_collision(0);

    return col;
}

void new_frame_1(void)
{
    // Draws base frame for scene
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
    // Resets birds possition to start
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
  // Draws top and bootom pipe-pair in frame
  // x_point gives x-cordinate of the lfet edge of the pipe
  // y_point gives y-cordinate of where the top pipe ends

  int i = 0; //y-värdet
  int j = 0; //x-värdet
  for (i; i < y_point; i++)
  {
      draw_point(x_point, i, frame);
      for (j = (x_point+2); j < (x_point+5); j++)
      {
        draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
      }
  }

  for (j = (x_point); j < (x_point+5); j++)
  {
    draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
  }

  i+=15;

  for (j = (x_point); j < (x_point+5); j++)
  {
    draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
  }

  for (i; i < 32; i++)
  {
      draw_point(x_point, i, frame);
      for (j = (x_point+2); j < (x_point+5); j++)
        draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
  }

}



void stage1_int(void){
    // Interrupt handaling for stage 1

    count++;
    /* Clears frame */
    new_frame_1();

    // Collision detection
    if(collision())
    {
      bird_reset();
    }

    /* Draws bird in frame */
    int i = 0;
    for (i; i < 9; i++)
    {
        draw_point(bird[i][0],bird[i][1], frame);
    }

    // Draws pipes
    for (i = 0; i < 3; i++)
      draw_pipe(30 + (20 * i), pipespaces[i]);

    /*
    draw_pipe(30, pipespaces[0]);
    draw_pipe(50, pipespaces[1]);
    draw_pipe(70, pipespaces[2]); */

    /* Sends frame to display */
    display_image(frame);

    // updates birds possition
    if (count >= 4)
    {
        count = 0;
        /* Moves bird 1 pixel along the x-axis*/
        for (i = 0; i < 9; i++)
        {
          // x values
          if (bird[i][0] >= 90)
          {
            bird[i][0] = 0;
            random_pipes();
          }

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
  random_pipes();

  int btnstate;
  while (stage == 1)
  {
    btnstate = getbtns();
    if (btnstate & 8)
    {
        if (jump == 0)
            jump = 5;
    }
    else if (btnstate & 1)
        stage = 0;
  }

}
