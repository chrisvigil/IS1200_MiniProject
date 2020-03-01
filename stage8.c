#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//CREDITS stage

uint8_t frame[512];
uint8_t pos_8 = 0;

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

int check_highscore()
{
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
    /*
    int i,j;
    for (i=0; i < 3; i++)
    {
      for (j = 0; j < 5; j++)
        eeprom_write(0x00, ((i*5)+j), (highscore_list[i][j] & 0xFF));
    }
    */
  }
}

void stage8_int(void)
{
  new_frame_8();
  drawword("new", 30, frame, 0, 3);
  drawword("highscore", 50, frame, 0, 9);

  frame[95] = 0xE8;

  int line2 = 164;
  drawletter(name[0], line2, frame, 3);
  drawletter(name[1], (line2+8), frame, 3);
  drawletter(name[2], (line2+8+8), frame, 3);

  drawnumbers((line2+50),temp_highscore,1,3,frame);

/*  int line = 266;
  drawword("enter", line, frame, 3, 5);
  drawword("name", (line+30), frame, 3, 4);*/

  int line = 384;
  drawword("btn", line, frame, 3, 3);
  drawnumbers((line+=14),4,1,3,frame);
  frame[(line+=5)] = 0xAF;
  drawword("select", (line+=2), frame, 3, 6);
  drawword("btn", (line+=30), frame, 3, 3);
  drawnumbers((line+=14),3,1,3,frame);
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
  	int btnstate;
    int btn4pushed = 0;
  	int btn3pushed = 0;
    letters_counter = 0;
    select = 0;
    name[0] = 'a';
    name[1] = 'a';
    name[2] = 'a';
    int scorepos = check_highscore();

  	while (stage == 8)
  	{
  		btnstate = getbtns();
      if ((btnstate & 8) && (btn4pushed <=0))
      {
        select++;
        btn4pushed = 100000;
      }
      else
      {
        btn4pushed--;
      }
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





  /*
  int btnstate;
  int btn3pushed = 0;

  while (stage == 6)
  {
    btnstate = getbtns();
    if (btnstate & 8) //Button to the furthest left
    {
      stage = 2;
    }

    if ((btnstate & 4) && (btn3pushed <= 0) )
    {
      if (pos_6 = 0)
        pos_6 = 1;
      else
      btn3pushed = 100000;
    }
    else
    {
      btn3pushed--;
    }
  }
}
*/


//Gör att den här cyklar igenom bokstäverna
//Den ska dock bara gå till nästa om knappen trycks
//letters_counter går upp om knappen trycks in


/*


//Gör att den här cyklar igenom bokstäverna
//Den ska dock bara gå till nästa om knappen trycks
//letters_counter går upp om knappen trycks in
void cycle_letters(void)
{
	int btnstate;
	int letters_counter = 0;
	int i = 97;
	int btn3pushed = 0;

	while (stage == 5)
	{
		btnstate = getbtns();
		if ((btnstate & 4) && (btn3pushed <= 0)) //
			letters_counter++;
		if (letters_counter = 1)
		{
			drawletter(i, 90, frame, 3);
			i++;
			if (i >= 123)
		  	i = 97;
			btn3pushed = 100000;
		}
		else
		{
	  	btn3pushed--;
		}
	}
}
//Sen måste det finnas en "OK" på knapp 4 också.*/
