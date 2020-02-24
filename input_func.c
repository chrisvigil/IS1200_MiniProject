#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

int getbtns( void )
{
    // Returns state of btn4
    int state = ((PORTD & 0x80) >> 4); // gets btn 4 state
    state |= (PORTF & 2) >> 1; // gets btn 1 state

    return state;
}
