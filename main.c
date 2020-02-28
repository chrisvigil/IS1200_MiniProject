/*  main.c

    This file written 2020 by Chris Vigil


*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "header.h"  /* Declatations for this program */

void user_isr( void )
{
  if ((IFS(0) & 0x100) == 0x100)
  {
    IFS(0) &= ~0x100; // clears timer 2 interrupt flag
    switch (stage){
      case 0:
        stage0_int();
        break;
      case 1:
        stage1_int();
        break;
      case 2:
        stage2_int();
        break;
      case 3:
        stage3_int();
        break;
      case 4:
        stage4_int();
        break;
      case 5:
        stage5_int();
        break;
      case 6:
        stage6_int();
        break;
      case 7:
        stage7_int();
        break;
    }

  }
}

int main( void )
{
    init();
    stage = 0;
    speed = 4; // default = 4
    pipespacing = 15; // default  = 15

    int i,j;
    for (i=0; i < 3; i++)
    {
      /*
      highscore_list[i][0] = 'c';
      highscore_list[i][1] = 'c';
      highscore_list[i][2] = 'v';
      highscore_list[i][3] = 0;
      highscore_list[i][4] = 0;
      */

      for (j = 0; j < 5; j++)
        highscore_list[i][j] = eeprom_read(0x00,((i*5)+j));

    }


    temp_highscore = 0;


    while (1)
    {
      switch (stage)
      {
        case 0: // main menu
          stage0_work();
          srand(TMR2);
          break;
        case 1: // game
          stage1_work();
          break;
        case 2: // settings
          stage2_work();
          break;
        case 3: // speed
          stage3_work();
          break;
        case 4: // info
          stage4_work();
          break;
        case 5: // highscores
          stage5_work();
          break;
        case 6: // credits
          stage6_work();
          break;
        case 7: // spacing
          stage7_work();
          break;
      }
      IEC(0) &= ~(1 << 8);
      quicksleep(1000000);
      IEC(0) |= (1 << 8);
    }
}
