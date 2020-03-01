#include <stdint.h>
#include <pic32mx.h>
#include "header.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

//Sends/recives 8 bits of data over SPI
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

// Initialises display
void display_init(void) {
  DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);

	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);
}

// Writes an entire frame of data to display
void display_image(const uint8_t *data) {
	int i, j;

	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

		spi_send_recv(0x22);
		spi_send_recv(i);

        spi_send_recv(0x00);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 128; j++)
			spi_send_recv(~data[i*128 + j]);
	}
}

void draw_point(uint8_t x, uint8_t y, uint8_t *cframe)
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
        ( ( y / (column hight) ) * ( display width ) ) + x

        a pixel is then added by shifting pixel into the
        correct position with:
        column &= ~(1 << (y % (column hight)))

        */
    cframe[((y/8)*128)+x] &= ~(0x1 << (y%8));
}

void drawnumbers(int numbers, int start, int inv, uint8_t *frame, int offset)
{
	// Adds numbers to a frame
  int i;
  for (i = 0; i < 4; i++)
	{
		frame[i + start] = (number[( (numbers % 10)* 4) + i] << offset);
		if (inv)
			frame[i + start] = 	~(frame[i + start]);
	}

  if (numbers > 9)
  {
    for (i = 0; i < 4; i++)
		{
			frame[i + start - 5] = (number[( ((numbers % 100)/10)* 4) + i] << offset);
			if (inv)
				frame[i + start - 5] = 	~(frame[i + start - 5]);
		}

  }
  if (numbers > 99)
  {
    for (i = 0; i < 4; i++)
		{
			frame[i + start - 10] = (number[( ((numbers / 100) % 1000) *4) + i] << offset);
			if (inv)
				frame[i + start - 10] = ~(frame[i + start - 10]);
		}
  }
}

int drawletter(char c, int start, uint8_t *frame, uint8_t shift)
{
	//Addes a letter to a frame and returns last colum of letter +5
	uint8_t l = ((c - 97) * 4);
	int i;
	for (i = 0; i < 4; i++)
	{
		frame[((start)+i)] = ~(~(letter[l+i]) << shift);
		if (frame[((start)+i)] == 0xFF)
			(start)--;
	}
	return start+=5;
}

void drawword(char *word, int start, uint8_t *frame, uint8_t shift, int len)
{
	// Addes a word to a frame
	int i;
	for (i = 0; i < len; i++)
	{
		start = drawletter(word[i],start,frame,shift);
	}

}
