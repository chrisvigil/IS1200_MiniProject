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
  0xE1,0xFA,0xFA,0xE1, //A 0-3
  0xE0,0xEA,0xEA,0xF5, //B 3-6
  0xFF,0xF1,0xEE,0xEE, //C 7-10
  0xE0,0xEE,0xEE,0xF1, //D 11-14
  0xFF,0xE0,0xEA,0xEA, //E 15-18
  0xFF,0xE0,0xFA,0xFA, //F 19- dfsdd26
  0xF1,0xEE,0xEA,0xE2, //G 27-30
  0xE0,0xFB,0xFB,0xE0, //H 31-34
  0xFF,0xEE,0xE0,0xEE, //I 35-38
  0xFF,0xEE,0xEE,0xF0, //J 39-42
  0xE0,0xFB,0xF5,0xEE, //K 43-46
  0xFF,0xE0,0xEF,0xEF, //L 47-50
  0xE0,0xFD,0xFD,0xE0, //M 51-54
  0xE0,0xFD,0xFB,0xE0, //N 55-58
  0xF1,0xEE,0xEE,0xF1, //O 59-62
  0xE0,0xF6,0xF6,0xF9, //P 63-66
  0xFF,0xFF,0xFF,0xFF, //Q 67-70 - not implemented
  0xE0,0xF6,0xF6,0xE9, //R 71-74
  0xED,0xEA,0xEA,0xF6, //S 75-78
  0xFF,0xFE,0xE0,0xFE, //T 79-82
  0xF0,0xEF,0xEF,0xF0, //U 83-86
  0xFF,0xF0,0xEF,0xF0, //V 87-90
  0xE0,0xF7,0xF7,0xE0, //W 91-94
  0xFF,0xFF,0xFF,0xFF, //X - not implemented
  0xFF,0xFC,0xE3,0xFC, //Y
  0xFF,0xFF,0xFF,0xFF  //Z - not implemented
};
