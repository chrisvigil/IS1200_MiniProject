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

  drawletter('s',20,frame,3);
  drawletter('p',25,frame,3);
  drawletter('e',29,frame,3);
  drawletter('e',33,frame,3);
  drawletter('d',38,frame,3);

  drawletter('s',75,frame,3);
  drawletter('p',80,frame,3);
  drawletter('a',85,frame,3);
  drawletter('c',89,frame,3);
  drawletter('i',93,frame,3);
  drawletter('n',98,frame,3);
  drawletter('g',103,frame,3);

  drawletter('i',275+3,frame,3);
  drawletter('n',280+3,frame,3);
  drawletter('f',284+3,frame,3);
  drawletter('o',289+3,frame,3);

  drawletter('b',347-9,frame,3);
  drawletter('a',352-9,frame,3);
  drawletter('c',356-9,frame,3);
  drawletter('k',361-9,frame,3);
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
    for (i = 406; i < 425; i++)
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

  while (stage == 2)
  {
    btnstate = getbtns();

    if (btnstate & 8)
    {
        switch (pos_2)
        {
          case 0:
            stage = 0;
            break;
          case 1:
            stage = 0;
            break;
          case 2:
            stage = 0;
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
