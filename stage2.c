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
}

void stage2_int(void)
{
  new_frame_2();
  display_image();
}


void stage2_work(void)
{

}
