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

  int i;
  int num;

  for (i=0; i < 3; i++)
  {
    drawword(highscore_list[i], ((128*i)+20), frame, 3, 3);

    num = ((highscore_list[i][3] << 8) |  highscore_list[i][4]);
    drawnumbers(((128*i)+60), num, 1, 3, frame);
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
    btnstate = getbtns();
    if (btnstate & 8) //Button to the furthest left
    {
      stage = 4;
    }
    if (btnstate & 1)
    {
      int i,j;
      for (i = 0; i < 16; i++)
      {
          eeprom_write(0x00, (uint8_t)i, (uint8_t)0);
      }
      for (i = 0; i < 3; i++)
      {
        for (j = 0; j < 5; j++)
        {
          highscore_list[i][j] = eeprom_read(0x00,(uint8_t)((i*5)+j));
        }
      }

    }
  }
}
