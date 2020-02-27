#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

uint8_t frame[512];
uint8_t pos_4 = 0;

void new_frame_4(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }

drawword("highscores", 20, frame, 3, 10);
drawword("credits", 90, frame, 3, 7);
drawword("back", 278, frame, 3, 4);
//
}

void stage4_int(void)
{
  new_frame_4();
  int i = 0;
  switch(pos_4)
  {
    case 0:
    for (i = 148; i < 194; i++)
      frame[i] = 0xFD;
    break;

    case 1:
    for (i = 218; i < 250; i++)
      frame[i] = 0xFD;
    break;

    case 2:
    for (i = 406; i < 424; i++)
      frame[i] = 0xFD;
    break;
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
  }
}
