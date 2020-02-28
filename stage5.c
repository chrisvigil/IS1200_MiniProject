#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//HIGHSCORES stage

uint8_t frame[512];
uint8_t pos_5 = 0;

void new_frame_5(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }
}

void stage5_int(void)
{
  new_frame_5();

  int i,j;
  char name[3];

  for (i=0; i < 3; i++)
  {
    /*
    for (j=0; j < 3; j++)
    {
      name[i] = highscore_list[i];
    }*/
    drawword(highscore_list[i], ((128*i)+20), frame, 3, 3);
  }

  display_image(frame);
}


void stage5_work(void)
{
  int btnstate;
  int btn3pushed = 0;
  //pos = 0;

  while (stage == 5)
  {
    /*
    btnstate = getbtns();
    if (btnstate & 8) //Button to the furthest left
    {
      switch (pos_4)
      {
        case 0:
          stage = 5;
          break;
        case 1:
          stage = 6;
          break;
        case 2:
          stage = 2;
          break;
      }
    }

    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos_4 < 2)
        pos_4++;
      else
        pos_4 = 0;
      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }*/
  }
}
