#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//SPEED!

uint8_t frame[512];
uint8_t pos_3 = 0;

void new_frame_3(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }

  drawword("slow", 141, frame, 3, 4);
  drawword("fast", 176, frame, 3, 4);
  drawword("insane", 210, frame, 3, 6);
}

void stage3_int(void)
{
  new_frame_3();
  int i;
  switch(pos_3)
  {
    case 0:
    for (i = 269; i < 289; i++)
      frame[i] = 0xFD;
    break;

    case 1:
    for (i = 304; i < 321; i++)
      frame[i] = 0xFD;
    break;

    case 2:
    for (i = 338; i < 365; i++)
      frame[i] = 0xFD;
    break;
  }
  display_image(frame);
}


void stage3_work(void)
{
  int btnstate;
  int btn3pushed = 0;

  while (stage == 3)
  {
    btnstate = getbtns();

    if (btnstate & 8)
    {
        switch (pos_3)
        {
          case 0:
            speed = 4;
            stage = 2;
            break;
          case 1:
            speed = 3;
            stage = 2;
            break;
          case 2:
            speed = 2;
            stage = 2;
            break;
        }
    }

    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos_3 < 2)
        pos_3++;
      else
        pos_3 = 0;
      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }
}
