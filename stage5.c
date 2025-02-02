#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//HIGHSCORES stage

void new_frame_5(void)
{
  // sets all pixels in frame to off
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }
  drawword("speed", 85, frame, 3, 5);
  frame[108] = 0xAF;

}

void stage5_int(void)
{
  new_frame_5();

  // Addes highscores to frame
  int i;
  int num;
  for (i=0; i < 4; i++)
  {
    drawword(highscore_list[i], ((128*i)+20), frame, 3, 3);

    num = ((highscore_list[i][3] << 8) |  highscore_list[i][4]);
    drawnumbers(num, ((128*i)+60),  1, frame, 3);
  }

  switch(speed)
  {
    case 4:
      drawword("slow", 213, frame, 3, 4);
      break;
    case 3:
      drawword("fast", 213, frame, 3, 4);
      break;
    case 2:
      drawword("insane", 213, frame, 3, 6);
      break;
  }

  display_image(frame);
}


void stage5_work(void)
{
  int btnstate;
  int btn3pushed = 0;

  while (stage == 5)
  {
    btnstate = getbtns();

    // returns to info menu if btn 4 is pused
    if (btnstate & 8)
    {
      pos_4 = 2;
      stage = 4;
    }

    // btn 3,2 and 1 are pused at the same time highscores are reset
    if (btnstate == 7)
    {
      int i,j;
      for (i = 0; i < 20; i+=5)
      {
        for (j = 0; j < 3; j++)
        {
          eeprom_write(0x00, (uint8_t)((i+j)+adr_offset), 'a');
        }
        for (j; j < 5; j++)
        {
          eeprom_write(0x00, (uint8_t)((i+j)+adr_offset), (uint8_t)0);
        }
      }

      for (i = 0; i < 4; i++)
      {
        for (j = 0; j < 5; j++)
        {
          highscore_list[i][j] = eeprom_read(0x00,(uint8_t)((i*5)+j)+adr_offset);
        }
        temp_highscore = 0;
      }
    }

  }
}
