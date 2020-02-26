#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

uint8_t frame_0[512];
uint8_t pos = 0;

void new_frame_0(void)
{
    /* sets all pixels in frame to off */
    int i = 0;
    for (i = 0; i < 512; i++)
    {
        frame_0[i] = 255;
    }

    drawletter('s',148,frame_0,3);
    drawletter('t',152,frame_0,3);
    drawletter('a',157,frame_0,3);
    drawletter('r',162,frame_0,3);
    drawletter('t',166,frame_0,3);

    drawletter('s',201,frame_0,3);
    drawletter('e',205,frame_0,3);
    drawletter('t',209,frame_0,3);
    drawletter('t',213,frame_0,3);
    drawletter('i',217,frame_0,3);
    drawletter('n',222,frame_0,3);
    drawletter('g',227,frame_0,3);
    drawletter('s',232,frame_0,3);

    /*
    //S
    frame[181] = 0x47;
    frame[182] = 0x57;
    frame[182] = 0x17;

    //T
    frame[184] = 0xF7;
    frame[185] = 0x07;
    frame[186] = 0xF7;

    //A
    frame[188] = 0x07;
    frame[189] = 0xD7;
    frame[190] = 0x07;

    //R
    frame[192] = 0x07;
    frame[193] = 0xD7;
    frame[194] = 0x27;

    //T
    frame[196] = 0xF7;
    frame[197] = 0x07;
    frame[198] = 0xF7;


    //S
    frame[172] = 0x31;
    frame[173] = 0x20;
    frame[174] = 0x24;
    frame[175] = 0x24;
    frame[176] = 0x04;
    frame[177] = 0x8C;

    //T
    frame[180] = 0xFC;
    frame[181] = 0xFC;
    frame[182] = 0x00;
    frame[183] = 0x00;
    frame[184] = 0xFC;
    frame[185] = 0xFC;

    //A
    frame[188] = 0x01;
    frame[189] = 0x00;
    frame[190] = 0xE4;
    frame[191] = 0xE4;
    frame[192] = 0x00;
    frame[193] = 0x01;

    //R
    frame[196] = 0x00;
    frame[197] = 0x00;
    frame[198] = 0xE4;
    frame[199] = 0xE4;
    frame[200] = 0x00;
    frame[201] = 0x19;

    //T
    frame[204] = 0xFC;
    frame[205] = 0xFC;
    frame[206] = 0x00;
    frame[207] = 0x00;
    frame[208] = 0xFC;
    frame[209] = 0xFC;
    */



}

void stage0_int(void)
{
    new_frame_0();
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
    display_image(frame_0);
}

void stage0_work(void)
{
  int btnstate;
  int btn3pushed = 0;

  while (stage == 0)
  {
    btnstate = getbtns();
    if (btnstate & 8)
    {
        stage = 1;
    }
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
