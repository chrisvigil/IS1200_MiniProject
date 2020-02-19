#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

uint8_t frame[512];
int bird[9][2] = {{0,16},{2,16},{3,16},{0,17},{1,17},{2,17},{0,18},{1,18},{2,18}};
int count = 0;
int jump = 0;

void new_frame(void)
{
    /* sets all pixels in frame to off */
    int i = 0;
    for (i = 0; i < 512; i++)
    {
        frame[i] = 255;
    }
}

void draw_point(int x, int y)
{
    /*  Draws a point in the frame with x,y cordinates
        Point [0,0] is located at the top left of the display
        Point [127,31] is bottom right.

        Display consists of 4 rows, each row consists of
        128 coloums, each 8 pixels high for a total of 512 coloums.

        Each column is controlled by a 8 bit value with each bit
        representing a pixel. LSB represents top pixel.

        For example ~0x02 would light second from the top in the coloumn.
        ~0xaa or ~0x55 would liight every other pixel in the column.

        A full frame is represented as an array of 512 uint8_t values.
        Each index is a column.

        To draw a point, index is caululated with the formula:
        ( y / (column hight) ) + ( display width )

        a pixel is then added by shifting pixel into the
        correct position with:
        column &= ~(1 << (y % (column hight)))

        */
    frame[((y/8)*128)+x] &= ~(0x1 << (y%8));
}

int getbtns( void )
{
    // Returns state of btn4
    int state = ((PORTD & 0x80) >> 7);

    return state;
}

void user_isr( void )
{
    if ((IFS(0) & 0x100) == 0x100)
    {
        IFS(0) &= ~0x100; // clears timer 2 interrupt flag
            count++;
            /* Clears frame */
            new_frame();

            /* Draws bird in frame */
            int i = 0;
            for (i; i < 9; i++)
            {
                draw_point(bird[i][0],bird[i][1]);
            }

            /* Sends frame to display */
            display_image(frame);

            if (count >= 4)
            {
                count = 0;
                /* Moves bird 1 pixel along the x-axis*/
                for (i = 0; i < 9; i++)
                {
                    if (bird[i][0] >= 127)
                    bird[i][0] = 0;
                    else
                    (bird[i][0])++;

                    if (bird[i][1] >= 31)
                        bird[i][1] = 0;
                    else
                    {
                        if (jump <= 0)
                            (bird[i][1])++;
                        else
                        {
                            (bird[i][1])--;
                        }
                    }
                }
                if (jump > 0)
                    jump--;

                /*
                if (jump == 0)
                    IECSET(1) = 1;*/

            }
        }

        /*
    if (IFS(0) & 1)
    {
        IFSCLR(1) = 1;
        if (jump == 0)
            jump = 5;
        IECCLR(1) = 1;
    }
    */
}

void work(void)
{
    if (getbtns())
    {
        if (jump == 0)
            jump = 5;
    }
}
