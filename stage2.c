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
}

void stage2_int(void)
{
  new_frame_2();
  display_image(frame);
}


void stage2_work(void)
{
  int btnstate;
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
        }
    }
  }
}
