#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

uint8_t frame[512];
uint8_t pos = 0;

void new_frame_4(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }

drawword("highscores", 148, frame, 3, 10);
drawword("about", 201, frame, 3, 5);
//
}

void stage4_int(void)
{
new_frame_4();
if (pos == 0)
  {
    int i;
    for (i = 276; i < 303; i++)
      frame[i] = 0xFD;
  }
  else
  {
    int i;
    for (i = 329; i < 361; i++)
      frame[i] = 0xFD;
  }
  display_image(frame);
}

void stage4_work(void)
{
  int btnstate;
  int btn3pushed = 0;
  //pos = 0;

  while (stage == 4)
  {
    btnstate = getbtns();
    if (btnstate & 8) //Button to the furthest left
    {
      switch (pos)
      {
        case 0:
          stage = 1;
          break;
        case 1:
          stage = 5;
          break;
        case 2:
          stage = 6;
          break;
      }
    }

    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos == 0)
        pos++;
      else
        pos = 0;
      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }
}

}
