#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//SPEED!

uint8_t pos_3;

void new_frame_3(void)
{
  // sets all pixels in frame to off
  int i = 0;
  for (i = 0; i < 512; i++)
  {
    frame[i] = 255;
  }

  // Addes menu choices
  drawword("slow", 141, frame, 3, 4);
  drawword("fast", 176, frame, 3, 4);
  drawword("insane", 210, frame, 3, 6);
}

void stage3_int(void)
{
  new_frame_3();

  // Determines possition of underline
  int i;
  switch(pos_3)
  {
    case 0:
      for (i = 269; i < 289; i++)
        frame[i] = 0xFD;
      break;

    case 1:
      for (i = 304; i < 321; i++)
        frame[i] = 0xFD;
      break;

    case 2:
      for (i = 338; i < 365; i++)
        frame[i] = 0xFD;
      break;
  }

  display_image(frame);
}

void change_check(int new)
{
  if (new != speed)
    highscore = 0;
}


void stage3_work(void)
{
  int btnstate;
  int btn3pushed = 0;

  // sets pos based on current speed value
  switch(speed)
  {
    case 4:
      pos_3 = 0;
      break;
    case 3:
      pos_3 = 1;
      break;
    case 2:
      pos_3 = 2;
      break;
  }

  while (stage == 3)
  {
    btnstate = getbtns();

    // if btn 4 is pressed speed is set and returns to setting menu
    // is determined by current pos value
    if (btnstate & 8)
    {
      switch (pos_3)
      {
        case 0:
          change_check(4);
          speed = 4;
          break;
        case 1:
          change_check(3);
          speed = 3;
          break;
        case 2:
          change_check(2);
          speed = 2;
          break;
      }
      pos_2 = 3;
      stage = 2; // Back to settings
    }

    // if btn3 was not recently pushed pos is advanced
    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos_3 < 2)
        pos_3++;
      else
        pos_3 = 0;
      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }
}
