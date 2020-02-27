#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//SPEED!

uint8_t frame[512];
uint8_t pos_3 = 0;

void new_frame_3(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }

  drawword("slow", 141, frame, 3, 4);
  drawword("fast", 176, frame, 3, 4);
  drawword("insane", 210, frame, 3, 6);
}

void stage3_int(void)
{
  new_frame_3();
  display_image(frame);
}


void stage3_work(void)
{

}
