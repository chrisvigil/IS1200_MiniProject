#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

//CREDITS stage

uint8_t frame[512];
uint8_t pos_6 = 0;

int letters_counter = 0;

void new_frame_6(void)
{
  /* sets all pixels in frame to off */
  int i = 0;
  for (i = 0; i < 512; i++)
  {
      frame[i] = 255;
  }
/*
  drawword("made", 20, frame, 3, 4);
  drawword("by", 41, frame, 3, 2);
  drawword("chris", 148, frame, 3, 5);
  drawword("vigil", 175, frame, 3, 5);
  drawword("and", 276, frame, 3, 3);
  drawword("sara", 404, frame, 3, 4);
  drawword("bertse", 426, frame, 3, 6);
  */

}

void stage6_int(void)
{
  new_frame_6();
  display_image(frame);
}


void stage6_work(void)
{
  	int btnstate;
  	int i = 97;
  	int btn3pushed = 0;
    int j = 20;

  	while (stage == 6)
  	{
  		btnstate = getbtns();
  		if (btnstate & 8)
  			letters_counter++;
  		if (letters_counter >= 1)
  		{
  			drawletter(i, j, frame, 3);
  			i++;
        j+=5;
  			if (i >= 123)
  		  	i = 97;
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
