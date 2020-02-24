#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

uint8_t frame[512];

void new_frame_0(void)
{
    /* sets all pixels in frame to off */
    int i = 0;
    for (i = 0; i < 512; i++)
    {
        frame[i] = 255;
    }
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
    */

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

}

void stage0_int(void)
{
    new_frame_0();
    display_image(frame);
}

void stage0_work(void)
{
    if (getbtns())
    {
        stage = 1;
    }
}
