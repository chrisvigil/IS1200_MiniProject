/*  main.c

    This file written 2020 by Chris Vigil


*/

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "header.h"  /* Declatations for this program */

int main( void )
{
    init();
    //data_init();
    while (1)
    {
        work();
    }

}
