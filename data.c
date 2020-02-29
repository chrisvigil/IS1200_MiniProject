#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"


const uint8_t const number[] = {
  0x0E,0x11,0x11,0x0E, //0
  0x00,0x12,0x1F,0x10, //1
  0x12,0x19,0x15,0x12, //2
  0x00,0x15,0x15,0x0A, //3
  0x00,0x07,0x04,0x1F, //4
  0x00,0x17,0x15,0x09, //5
  0x0E,0x15,0x15,0x08, //6
  0x00,0x19,0x05,0x03, //7
  0x0A,0x15,0x15,0x0A, //8
  0x02,0x15,0x15,0x0E  //9
};

const uint8_t const letter[] = {
  0xE1,0xFA,0xFA,0xE1, //A
  0xE0,0xEA,0xEA,0xF5, //B
  0xFF,0xF1,0xEE,0xEE, //C
  0xE0,0xEE,0xEE,0xF1, //D
  0xFF,0xE0,0xEA,0xEA, //E
  0xFF,0xE0,0xFA,0xFA, //F
  0xF1,0xEE,0xEA,0xE2, //G
  0xE0,0xFB,0xFB,0xE0, //H
  0xFF,0xEE,0xE0,0xEE, //I
  0xFF,0xEE,0xEE,0xF0, //J
  0xE0,0xFB,0xF5,0xEE, //K
  0xFF,0xE0,0xEF,0xEF, //L
  0xE0,0xFD,0xFD,0xE0, //M
  0xE0,0xFD,0xFB,0xE0, //N
  0xF1,0xEE,0xEE,0xF1, //O
  0xE0,0xF6,0xF6,0xF9, //P
  0xF1,0xEE,0xE6,0xE1, //Q
  0xE0,0xF6,0xF6,0xE9, //R
  0xED,0xEA,0xEA,0xF6, //S
  0xFF,0xFE,0xE0,0xFE, //T
  0xF0,0xEF,0xEF,0xF0, //U
  0xFF,0xF0,0xEF,0xF0, //V
  0xE0,0xF7,0xF7,0xE0, //W
  0xE4,0xFB,0xFB,0xE4, //X
  0xFF,0xFC,0xE3,0xFC, //Y
  0xEE,0xE6,0xEA,0xEC  //Z 
};
