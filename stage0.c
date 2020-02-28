#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

uint8_t frame_0[512];
uint8_t pos = 0;
uint8_t temp;

void new_frame_0(void)
{
    /* sets all pixels in frame to off */
    int i = 0;
    for (i = 0; i < 512; i++)
    {
        frame_0[i] = 255;
    }

    drawword("start", 148, frame_0, 3, 5);
    drawword("settings", 201, frame_0, 3, 8);

    for (i = 0; i < 4; i++)
      frame_0[i + 400] = ~(number[( (temp % 10)* 4) + i] << 0);
}

void stage0_int(void)
{
    new_frame_0();
    if (pos == 0)
    {
      int i;
      for (i = 276; i < 298; i++)
        frame_0[i] = 0xFD;
    }
    else
    {
      int i;
      for (i = 329; i < 364; i++)
        frame_0[i] = 0xFD;
    }
    display_image(frame_0);
}

void stage0_work(void)
{
  int btnstate;
  int btn3pushed = 0;
  pos = 0;

  //uint8_t stuff = 3;
  //eeprom_write(0x00, 0x01, stuff);
  temp = eeprom_read(0x00,0x01);

  while (stage == 0)
  {
    btnstate = getbtns();
    if (btnstate & 8)
    {
        switch (pos)
        {
          case 0:
            stage = 1;
            break;
          case 1:
            stage = 2;
            break;
        }
    }

    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos == 0)
        pos = 1;
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
