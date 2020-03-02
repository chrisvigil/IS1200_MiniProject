/*  main.c

    This file written in 2020 by Chris Vigil and Sara Bertse


*/

#include <stdint.h>   // Declarations of uint_8 and uint16_t
#include <pic32mx.h>  // Declarations of system-specific addresses etc
#include "header.h"  // Declatations for this program

void user_isr( void )
{
  if ((IFS(0) & 0x100) == 0x100)
  {
    IFS(0) &= ~0x100; // clears timer 2 interrupt flag

    // determine which interrupt handling to use based on vaule of stage
    switch (stage){
      case 0: // main menu
        stage0_int();
        break;
      case 1: // game
        stage1_int();
        break;
      case 2: // settings menu
        stage2_int();
        break;
      case 3: // speed menu
        stage3_int();
        break;
      case 4: // info menu
        stage4_int();
        break;
      case 5: // highscores
        stage5_int();
        break;
      case 6: // credits
        stage6_int();
        break;
      case 7: // pipespacing
        stage7_int();
        break;
      case 8: // highscore entry
        stage8_int();
        break;
    }

  }
}

void read_highscores()
{
  int i,j;
  for (i=0; i < 4; i++)
  {
    for (j = 0; j < 5; j++)
    {
      highscore_list[i][j] = eeprom_read(0x00,((i*5)+j+adr_offset));
    }
  }
  // Sets temp_highscore to lowest hightscore
  temp_highscore = (int)((highscore_list[3][3] << 8) |  highscore_list[3][4]);
}

int main( void )
{
    init();
    stage = 0; // detrimes stage to start in
    speed = 4; // default gamespeed
    pipespacing = 15; // default pipespacing, must be 10, 15, or 20
    pos_0 = 0;
    pos_2 = 0;
    pos_4 = 0;
    highscore = 0;
    adr_offset = (speed-2) * 25;

    // Read highscores from memory
    read_highscores();

    while (1)
    {
      // determine which work routine to use based on stage vaule.
      // mains handels buttonpushes
      switch (stage)
      {
        case 0: // main menu
          stage0_work();
          srand(TMR2); // seeds new random value for pipe generation
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
        case 8: // highscore entry
          stage8_work();
          break;
      }

      // temporarily disables interrupts and sleeps to avoid
      // issues with jumping between stages
      IEC(0) &= ~(1 << 8);
      quicksleep(1000000);
      IEC(0) |= (1 << 8);
    }
}
