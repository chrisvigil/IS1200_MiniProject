#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

uint8_t frame[512];
uint8_t pos_2 = 0;

void new_frame_2(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }

  drawword("speed", 20, frame, 3, 5);

  drawword("spacing", 75, frame, 3, 7);

  drawword("info", 278, frame, 3, 4);

  drawword("back", 338, frame, 3, 4);
}

void stage2_int(void)
{
  new_frame_2();

  int i;
  switch(pos_2)
  {
    case 0:
    for (i = 148; i < 171; i++)
      frame[i] = 0xFD;
    break;

    case 1:
    for (i = 203; i < 236; i++)
      frame[i] = 0xFD;
    break;

    case 2:
    for (i = 406; i < 423; i++)
      frame[i] = 0xFD;
    break;

    case 3:
    for (i = 466; i < 485; i++)
      frame[i] = 0xFD;
    break;

  }
  display_image(frame);
}


void stage2_work(void)
{
  int btnstate;
  int btn3pushed = 0;
  pos_2 = 0;

  while (stage == 2)
  {
    btnstate = getbtns();

    if (btnstate & 8)
    {
        switch (pos_2)
        {
          case 0:
            stage = 3;
            break;
          case 1:
            stage = 0;
            break;
          case 2:
            stage = 4;
            break;
          case 3:
            stage = 0;
            break;
        }
    }

    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos_2 < 3)
        pos_2++;
      else
        pos_2 = 0;
      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }
}
