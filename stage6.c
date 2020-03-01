#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//CREDITS stage

uint8_t frame[512];
uint8_t pos_6 = 0;

int letters_counter;
int select;
char name[3];

void new_frame_6(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }
  drawword("made", 20, frame, 3, 4);
  drawword("by", 41, frame, 3, 2);
  drawword("chris", 148, frame, 3, 5);
  drawword("vigil", 175, frame, 3, 5);
  drawword("and", 276, frame, 3, 3);
  drawword("sara", 404, frame, 3, 4);
  drawword("bertse", 426, frame, 3, 6);
}

void stage6_int(void)
{
  new_frame_6();
  display_image(frame);
}


void stage6_work(void)
{
    // returns to info menu if any btn i pushed
    if (getbtns())
    {
      stage = 4;
    }
  }
