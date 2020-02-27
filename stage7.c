#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//SPACING stage

uint8_t frame[512];
uint8_t pos_7 = 0;

void new_frame_7(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }
  drawword("large", 141, frame, 3, 5);
  drawword("normal", 176, frame, 3, 6);
  drawword("small", 210, frame, 3, 5);
}

void stage7_int(void)
{
  new_frame_7();
  display_image();
}


void stage7_work(void)
{

}
