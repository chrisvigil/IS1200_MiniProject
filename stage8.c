#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//HIGHSCORE entry

int letters_counter;
int select;
char name[3];

void new_frame_8(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }
}

int check_highscore(void)
{
  // Addes highscore to lista and returns posstion value, 0 for 3rd, 1 for 2nd and 0 for first

  // determines a value for listnum based on where in the highscore list new highscore is to be placed
  // 0 for 3rd, 1 for 2nd and 0 for first
  int listnum = -1;
  if (temp_highscore > ((highscore_list[2][3] << 8) |  highscore_list[2][4]))
  {
    listnum = 0;
    if (temp_highscore > ((highscore_list[1][3] << 8) |  highscore_list[1][4]))
    {
      listnum = 1;
      if (temp_highscore > ((highscore_list[0][3] << 8) |  highscore_list[0][4]))
      {
        listnum = 2;
      }
    }

    // rearanges current highcores and adds new highscore to the correct possition
    int i,j;
    for (i = 0; i < listnum; i++)
    {
      for (j = 0; j < 5; j++)
      {
        highscore_list[(2-i)][j] = highscore_list[(1-i)][j];
      }
    }
    highscore_list[(2-i)][3] = (temp_highscore & 0xFF00) >> 8;
    highscore_list[(2-i)][4] = (temp_highscore & 0xFF);

    return i;
  }
}

void stage8_int(void)
{
  // draws current frame
  new_frame_8();
  drawword("new", 30, frame, 0, 3);
  drawword("highscore", 50, frame, 0, 9);

  frame[95] = 0xE8;

  int line2 = 164;
  drawletter(name[0], line2, frame, 3);
  drawletter(name[1], (line2+8), frame, 3);
  drawletter(name[2], (line2+8+8), frame, 3);

  drawnumbers(temp_highscore, (line2+50),1,frame, 3);

  int line = 384;
  drawword("btn", line, frame, 3, 3);
  drawnumbers(4, (line+=14), 1, frame, 3);
  frame[(line+=5)] = 0xAF;
  drawword("select", (line+=2), frame, 3, 6);
  drawword("btn", (line+=30), frame, 3, 3);
  drawnumbers(3, (line+=14), 1, frame, 3);
  frame[(line+=5)] = 0xAF;
  drawword("next", (line+=2), frame, 3, 4);
  drawword("letter", (line+=20), frame, 3, 6);

  int i;
  for (i=0; i < 4; i++)
  {
    frame[(select*8)+(line2+128)+i] &= 0xFD;
  }

  display_image(frame);
}


void stage8_work(void)
{
  pos_8 = 0;
    // allows user to enter 3 initials for highscore
  	int btnstate;
    int btn4pushed = 0;
  	int btn3pushed = 0;
    letters_counter = 0; // keeps track of current letter posstion
    select = 0; // keeps track of which initial is currently beeing choosen

    // name stores initials, starts at "aaa"
    name[0] = 'a';
    name[1] = 'a';
    name[2] = 'a';

    // checks which placing new highscore has
    int scorepos = check_highscore();

  	while (stage == 8)
  	{
  		btnstate = getbtns();

      // If btn4 is pushed and was not pused recently
      // then current inital is set and select is advanced
      if ((btnstate & 8) && (btn4pushed <=0))
      {
        select++;
        btn4pushed = 100000;
      }
      else
      {
        btn4pushed--;
      }

      // if btn3 is pushed and was not pushed recently
      // letters_counter is advanced which cycles initial
      // that is currently being chosen
  		if ((btnstate & 4) && (btn3pushed <= 0) )
      {
        if (letters_counter >= 25)
        {
          letters_counter = 0;
          name[select] = 'a';
        }
        else
        {
          letters_counter++;
          name[select]++;
        }
        btn3pushed = 100000;
      }
      else
      {
        btn3pushed--;
      }

      // When all three initials have been chosen the new lowest highscores
      // is written to temp_highscore, the chosen initals  are added to the
      // new highscore and finaly the new highscore list is written to the
      // eeprom and the game resumes
      if (select > 2 )
      {
        temp_highscore = ((highscore_list[2][3] << 8) |  highscore_list[2][4]);

        int i,j;

        for(i = 0; i < 3; i++)
        {
          highscore_list[2-scorepos][i] = name[i];
        }

        for (i=0; i < 3; i++)
        {
          for (j = 0; j < 5; j++)
            eeprom_write(0x00, ((i*5)+j), (highscore_list[i][j] & 0xFF));
        }
        stage = 1;
      }
  	}
  }
