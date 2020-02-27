#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//SPACING stage

uint8_t frame[512];
uint8_t pos_7 = 0;

void new_frame_7(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }
  drawword("large", 141, frame, 3, 5);
  drawword("normal", 181, frame, 3, 6);
  drawword("small", 225, frame, 3, 5);
}

void stage7_int(void)
{
  new_frame_7();

  int i;
  switch(pos_7)
  {
    case 0:
    for (i = 269; i < 292; i++)
      frame[i] = 0xFD;
    break;

    case 1:
    for (i = 309; i < 337; i++)
      frame[i] = 0xFD;
    break;

    case 2:
    for (i = 353; i < 375; i++)
      frame[i] = 0xFD;
    break;
  }

  display_image(frame);
}


void stage7_work(void)
{
  int btnstate;
  int btn3pushed = 0;
  switch (pipespacing)
  {
    case 15:
      pos_7 = 1;
      break;
    case 20:
      pos_7 = 0;
      break;
    case 10:
      pos_7 = 2;
      break;
  }

  while (stage == 7)
  {
    btnstate = getbtns();
    if (btnstate & 8) //Button to the furthest left
    {
      switch (pos_7)
      {
        case 0:
          pipespacing = 20;
          stage = 2;
          break;
        case 1:
          pipespacing = 15;
          stage = 2;
          break;
        case 2:
          pipespacing = 10;
          stage = 2;
          break;
      }
    }

    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos_7 < 2)
        pos_7++;
      else
        pos_7 = 0;
      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }
}
