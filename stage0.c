#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

// MAIN MENU

void new_frame_0(void)
{
  // sets all pixels in frame to off
  int i = 0;
  for (i = 0; i < 512; i++)
  {
    frame[i] = 255;
  }

  // Draws menu choices
  drawword("start", 148, frame, 3, 5);
  drawword("settings", 201, frame, 3, 8);
}

void stage0_int(void)
{
  //Create new default frame
  new_frame_0();

  // Draws underline under current choice
  if (pos_0 == 0)
  {
    int i;
    for (i = 276; i < 298; i++)
    frame[i] = 0xFD;
  }
  else
  {
    int i;
    for (i = 329; i < 364; i++)
    frame[i] = 0xFD;
  }

  // Send frame to display
  display_image(frame);
}

void stage0_work(void)
{
  int btnstate; // Stores buttonpushes
  int btn3pushed = 0; // 0 if ready for btn3 input
  pos_0 = 0; // Decides which choice is underlined and which stage to switch to when btn4 is pressed

  while (stage == 0)
  {
    btnstate = getbtns();

    // Changes stage if btn4 is pushed
    if (btnstate & 8)
    {
      switch (pos_0)
      {
        case 0:
          stage = 1; // To game
          break;
        case 1:
          pos_2 = 0;
          stage = 2; // To settings
          break;
      }
    }

    // If btn3 was not recently pushed changes pos
    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos_0 == 0)
        pos_0 = 1;
      else
        pos_0 = 0;

      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }
}
