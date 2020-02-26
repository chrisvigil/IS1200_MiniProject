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
}

void stage4_int(void)
{
  new_frame_4();
  display_image();
}


void stage4_work(void)
{

}
