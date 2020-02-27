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
  display_image();
}


void stage5_work(void)
{

}
