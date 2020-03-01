#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>
#include "header.h"
#define EEPROM_ADDR 0x50

/* Wait for I2C bus to become idle */
void i2c_idle() {
	while(I2C1CON & 0x1F || I2C1STAT & (1 << 14)); //TRSTAT
}

/* Send one byte on I2C bus, return ack/nack status of transaction */
uint8_t i2c_send(uint8_t data) {
	i2c_idle();
	I2C1TRN = data;
	i2c_idle();
	return !(I2C1STAT & (1 << 15)); //ACKSTAT
}

/* Receive one byte from I2C bus */
uint8_t i2c_recv() {
	i2c_idle();
	I2C1CONSET = 1 << 3; //RCEN = 1
	i2c_idle();
	I2C1STATCLR = 1 << 6; //I2COV = 0
	return I2C1RCV;
}

/* Send acknowledge conditon on the bus */
void i2c_ack() {
	i2c_idle();
	I2C1CONCLR = 1 << 5; //ACKDT = 0
	I2C1CONSET = 1 << 4; //ACKEN = 1
}

/* Send not-acknowledge conditon on the bus */
void i2c_nack() {
	i2c_idle();
	I2C1CONSET = 1 << 5; //ACKDT = 1
	I2C1CONSET = 1 << 4; //ACKEN = 1
}

/* Send start conditon on the bus */
void i2c_start() {
	i2c_idle();
	I2C1CONSET = 1 << 0; //SEN
	i2c_idle();
}

/* Send restart conditon on the bus */
void i2c_restart() {
	i2c_idle();
	I2C1CONSET = 1 << 1; //RSEN
	i2c_idle();
}

/* Send stop conditon on the bus */
void i2c_stop() {
	i2c_idle();
	I2C1CONSET = 1 << 2; //PEN
	i2c_idle();
}

void eeprom_write(uint8_t addrhigh, uint8_t addrlow, uint8_t data)
{

	// Start and send eeprom address + r/w bit
	do {
		i2c_start();
	} while(!i2c_send(EEPROM_ADDR << 1));

	// Sends high address
	i2c_send(addrhigh);
	// Sends low address
	i2c_send(addrlow);
  //Sends data
	i2c_send(data);
  i2c_stop();
}

uint8_t eeprom_read(uint8_t addrhigh, uint8_t addrlow)
{
  uint8_t data;

  do {
		i2c_start();
	} while(!i2c_send(EEPROM_ADDR << 1));

  /*
  i2c_start();
  i2c_send(0xA0);*/

  // Sends high address
	i2c_send(addrhigh);
	// Sends low address
	i2c_send(addrlow);

  i2c_start();
  i2c_send(0xA1);
  data = i2c_recv();

  i2c_stop();
  return data;
}
