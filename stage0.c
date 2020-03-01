#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

// MAIN MENU

uint8_t frame_0[512];
uint8_t pos = 0;
uint8_t temp;

void new_frame_0(void)
{
  // sets all pixels in frame to off
  int i = 0;
  for (i = 0; i < 512; i++)
  {
    frame_0[i] = 255;
  }

  // Draws menu choices
  drawword("start", 148, frame_0, 3, 5);
  drawword("settings", 201, frame_0, 3, 8);

  /*
  for (i = 0; i < 4; i++)
  frame_0[i + 400] = ~(number[( (temp % 10)* 4) + i] << 0);
  */
}

void stage0_int(void)
{
  //Create new default frame
  new_frame_0();

  // Draws underline under current choice
  if (pos == 0)
  {
    int i;
    for (i = 276; i < 298; i++)
    frame_0[i] = 0xFD;
  }
  else
  {
    int i;
    for (i = 329; i < 364; i++)
    frame_0[i] = 0xFD;
  }

  // Send frame to display
  display_image(frame_0);
}

void stage0_work(void)
{
  int btnstate; // Stores buttonpushes
  int btn3pushed = 0; // 0 if ready for btn3 input
  pos = 0; // Decides which choice is underlined and which stage to switch to when btn4 is pressed

  //temp = temp_highscore;

  while (stage == 0)
  {
    btnstate = getbtns();

    // Changes stage if btn4 is pushed
    if (btnstate & 8)
    {
      switch (pos)
      {
        case 0:
          stage = 1; // To game
          break;
        case 1:
          stage = 2; // To settings
          break;
      }
    }

    // If btn3 was not recently pushed changes pos
    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos == 0)
        pos = 1;
      else
        pos = 0;
        
      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }
}
