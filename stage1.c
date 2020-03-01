#include <stdint.h>
#include <pic32mx.h>
#include "header.h"
#include <stdlib.h> // Needed for rand()

// GAME stage

uint8_t frame[512];
uint8_t bird[9][2] = {{0,16},{2,16},{3,16},{0,17},{1,17},{2,17},{0,18},{1,18},{2,18}};
uint8_t count = 0; // Used to check if birds possition should be updated in current interrupt cycle
uint8_t jump = 0; // Used to move bird up
int randomseed; // Used to further increase randomness of pipe offset
uint8_t pipespaces[3]; // Used to store y value of the bottom of all 3 top pipes
int score_counter = 0; // Keeps track of current score
int highscore = 0; // Keeps track of game sessions current best score

void *stdout = (void *) 0; // Needed to compile correctly with rand()

void random_pipes(void)
{
  // Generates random vaules of y axis possitions for all three pipes
  int i = 0;

  for (i; i < 3; i++)
  {
    pipespaces[i] = ((rand() | randomseed)  % 9) + 3;
  }
}

int pipe_collision(int pipe)
{
  int i = 0;
  for(i; i < 9; i+=2)  //Checks collision for the four corners of the bird
  {
    if ( (bird[i][0] >= (30 + (20*pipe)) && bird[i][0] <= (35 + (20*pipe)) ) && (bird[i][1] <= pipespaces[pipe] || bird[i][1] >= (pipespaces[pipe] + pipespacing)))
      return 1;
  }
  return 0;
}

void scores(void)
{
  int i = 36;
  for (i; i < 77; i+= 20) //Checks values 36, 56, 76
  {
    if (bird[3][0] == i)
      score_counter++;   //Adds a score point for every pipe passed (36, 56, 76 = 3 points)
  }
}

int collision(void) //Collision detection for top and bottom of display
{
  if (bird[8][1] >= 30)
    return 1;
  if (bird[0][1] <= -1)
    return 1;

  int col = 0;
  if(bird[0][0] > 69)
    col = pipe_collision(2);
  else if (bird[0][0] > 49)
    col = pipe_collision(1);
  else if (bird[0][0] > 29)
    col = pipe_collision(0);

  return col;
}

void new_frame_1(void)
{
  // Draws base frame for scene
  int i = 0;
  int j;
  for (i; i < 3; i++)
  {
    for (j = 0; j < 91; j++)
      frame[(128 * i) + j] = 255;
    for (j; j < 128; j ++)
      frame[(128 * i) + j] = 0;
  }
  for (i = 384; i < 475; i++)
  {
    if (i%2)
      frame[i] = 0xbf;
    else
      frame[i] = 0x7f;
  }
  for (i; i < 512; i++)
  {
    frame[i] = 0;
  }

  //Letter S
  frame[98] = 0x90;
  frame[99] = 0xA8;
  frame[100] = 0xA8;
  frame[101] = 0x48;

  //C
  frame[103] = 0x70;
  frame[104] = 0x88;
  frame[105] = 0x88;

  //O
  frame[107] = 0x70;
  frame[108] = 0x88;
  frame[109] = 0x88;
  frame[110] = 0x70;

  //R
  frame[112] = 0xF8;
  frame[113] = 0x48;
  frame[114] = 0x48;
  frame[115] = 0xB0;

  //E
  frame[117] = 0xF8;
  frame[118] = 0xA8;
  frame[119] = 0xA8;

  //B
  frame[357] = 0x7C;
  frame[358] = 0x54;
  frame[359] = 0x54;
  frame[360] = 0x28;

  //E
  frame[362] = 0x7C;
  frame[363] = 0x54;
  frame[364] = 0x54;

  //S
  frame[366] = 0x48;
  frame[367] = 0x54;
  frame[368] = 0x54;
  frame[369] = 0x24;

  //T
  frame[371] = 0x04;
  frame[372] = 0x7C;
  frame[373] = 0x04;
}

void bird_reset(void)
{
  // Resets birds possition to start
  bird [0][0] = 0;
  bird [0][1] = 16;
  bird [1][0] = 2;
  bird [1][1] = 16;
  bird [2][0] = 3;
  bird [2][1] = 16;
  bird [3][0] = 0;
  bird [3][1] = 17;
  bird [4][0] = 1;
  bird [4][1] = 17;
  bird [5][0] = 2;
  bird [5][1] = 17;
  bird [6][0] = 0;
  bird [6][1] = 18;
  bird [7][0] = 1;
  bird [7][1] = 18;
  bird [8][0] = 2;
  bird [8][1] = 18;
}

draw_pipe(uint8_t x_point, uint8_t y_point) //Punkten i början på sista raden där glappet börjar
{
  // Draws top and bootom pipe-pair in frame
  // x_point gives x-cordinate of the left edge of the pipe
  // y_point gives y-cordinate of where the top pipe ends

  int i = 0; //y-value
  int j = 0; //x-value
  for (i; i < y_point; i++)
  {
    draw_point(x_point, i, frame);
    for (j = (x_point+2); j < (x_point+5); j++)
    {
      draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
    }
  }

  for (j = (x_point); j < (x_point+5); j++)
  {
    draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
  }

  i+=pipespacing;

  for (j = (x_point); j < (x_point+5); j++)
  {
    draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
  }

  for (i; i < 32; i++)
  {
    draw_point(x_point, i, frame);
    for (j = (x_point+2); j < (x_point+5); j++)
      draw_point(j, i, frame); //Anropas med x, y, och vilken frame den ska rita i
  }

}

void draw (void)
{
  /* Draws bird in frame */
  int i = 0;
  for (i; i < 9; i++)
  {
    draw_point(bird[i][0],bird[i][1], frame);
  }

  // Draws pipes
  for (i = 0; i < 3; i++)
  {
    draw_pipe(30 + (20 * i), pipespaces[i]);
  }

  drawnumbers(235, score_counter, 0, 2, frame);
  drawnumbers(491, highscore, 0, 1, frame);


}

void start(void)
{
  // code to run at start of run
  random_pipes();
  IEC(0) &= ~(1 << 8);
  new_frame_1();
  draw();
  //S
  frame[172] = 0x31;
  frame[173] = 0x20;
  frame[174] = 0x24;
  frame[175] = 0x24;
  frame[176] = 0x04;
  frame[177] = 0x8C;

  frame[178] = 0xFF;
  frame[179] = 0xFF;
  //T
  frame[180] = 0xFC;
  frame[181] = 0xFC;
  frame[182] = 0x00;
  frame[183] = 0x00;
  frame[184] = 0xFC;
  frame[185] = 0xFC;

  frame[186] = 0xFF;
  frame[187] = 0xFF;
  //A
  frame[188] = 0x01;
  frame[189] = 0x00;
  frame[190] = 0xE4;
  frame[191] = 0xE4;
  frame[192] = 0x00;
  frame[193] = 0x01;

  frame[194] = 0xFF;
  frame[195] = 0xFF;
  //R
  frame[196] = 0x00;
  frame[197] = 0x00;
  frame[198] = 0xE4;
  frame[199] = 0xE4;
  frame[200] = 0x00;
  frame[201] = 0x19;

  frame[202] = 0xFF;
  frame[203] = 0xFF;
  //T
  frame[204] = 0xFC;
  frame[205] = 0xFC;
  frame[206] = 0x00;
  frame[207] = 0x00;
  frame[208] = 0xFC;
  frame[209] = 0xFC;
  display_image(frame);

  if (stage == 1)
  {
    // Pause untill a button is pushed
    // btn4 starts game, btn 1 returns to menu
    quicksleep(1000000);
    while ((getbtns() & 8) == 0)
    {
      if ((getbtns() & 1))
      {
        stage = 0;
        break;
      }

    }
  }
  TMR2 = 0;
  IEC(0) |= (1 << 8);
}


void stage1_int(void)
{
  // Interrupt handaling for stage 1

  count++;
  /* Clears frame */
  new_frame_1();

  // Collision detection
  if(collision())
  {
    bird_reset();
    if (score_counter > highscore)
      highscore = score_counter;
    if (score_counter > temp_highscore)
    {
      temp_highscore = score_counter;
      stage = 8;
      return;
    }

    score_counter = 0;
    start();
  }

  draw();
  /* Sends frame to display */
  display_image(frame);


  // updates birds possition
  if (count >= speed)
  {
    count = 0;
    int i;
    /* Moves bird 1 pixel along the x-axis*/
    for (i = 0; i < 9; i++)
    {
      // x values
      if (bird[i][0] >= 90)
      {
        bird[i][0] = 0;
      }
      else
      {
        (bird[i][0])++;
      }


      // y values
      if (jump <= 0)
      {
        (bird[i][1])++;
      }
      else
      {
        (bird[i][1])--;
      }
    }

    scores(); // checks if score advances
    if (jump > 0)
      jump--;
    if (bird[3][0] == 0) // bird is at x = 0  generate new pipes
      random_pipes();
  }
}



void stage1_work(void)
{

  int btnstate;
  start();

  // Pushing btn4 causes bird to move uppwards one pixel at a time
  while (stage == 1)
  {
    btnstate = getbtns();
    if (btnstate & 8)
    {
      if (jump == 0)
        jump = 5;
    }
    else if (btnstate & 1)
      stage = 0;
    randomseed = TMR2;
  }
  // Reset score and bird if stage is exited
  bird_reset();
  score_counter = 0;

}
