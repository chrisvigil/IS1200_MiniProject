#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"


void system_init(void)
{
    /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

    /* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
}

void oledhost_init(void)
{
    /* Set up SPI as master */
    IECCLR(1) = 0x70; // Disables SPI interrupts
    SPI2CON= 0; // Stop and reset the SPI module
    SPI1BUF = 0; // Clear the receive buffer.
    SPI2BRG = 4; //Write the Baud Rate register
    SPI2STATCLR = 0x40; //Clear the SPIROV bit
    SPI2CONSET = 0x40; // CKP = 1
    SPI2CONSET = 0x20; // Write the desired settings to the SPIxCON register with MSTEN
    SPI2CONSET = 0x8000; //Enable SPI operation by setting the ON bit

    /* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

}

void init(void)
{
    system_init();
    oledhost_init();
	display_init();
}
