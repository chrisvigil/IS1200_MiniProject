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
        stage1_int();
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

int main( void )
{
    init();
    stage = 1;

    while (1)
    {
        stage1_work();
    }

}
