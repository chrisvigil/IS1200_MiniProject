#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//ABOUT stage

uint8_t frame[512];
uint8_t pos_6 = 0;

void new_frame_6(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }
}

void stage6_int(void)
{
  new_frame_6();
  display_image();
}


void stage6_work(void)
{

}
