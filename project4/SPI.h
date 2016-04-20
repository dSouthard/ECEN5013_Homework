/*
 * spi.h
 *
 * ECEN 5013 Spring 2016
 *
 * Created on: Apr 20, 2016
 *      Author: Diana Southard
 *
 *
 * Holds all SPI initialization and setup code.
 *
 * We need to configure the Serial Peripheral interface (SPI) for the Freedom Freescale KL25Z processor and the BeagleBone.
 * We will use these interfaces to interact with the Nordic nRF24L01+ module that was mentioned in the course syllabus class
 * materials list. One note is that you will need to be careful on the SPI clock frequencies you select and you will need
 * to set the processor into Master mode for SPI as the module will act as a slave device.
 */

#ifndef SPI_H_
#define SPI_H_

#include<stdint.h>

/* Firmware level interface – Create a SPI library that will configure the peripheral, allow sending and receiving data.
 * This should look like (but is not limited to) function calls listed in the following examples, but the design is up to you.
 */

// Initialize the SPI module
void SPI_init();

// Transmit a byte
void SPI_tx_byte(uint8_t sendByte);

//
void SPI_send_byte();

//
void SPI_flush();

#endif /* SPI_H_ */
