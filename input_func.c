#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"

int getbtns( void )
{
  // Returns state of btn4
  int state = ((PORTD & 0xe0) >> 4) | ((PORTF & 0x2) >> 1);

  return state;
}
