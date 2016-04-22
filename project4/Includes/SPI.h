/*
 * SPI.h
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

// definitions for SPI register settings
#define C1_SETTING 	0x54
#define C2_SETTING 	0x80
#define BR_SETTING 	0x21

// definitions for external SPI pins
#define MUX1 		0x1
#define MUX2 		0x2
#define CE_PIN3		0x8
#define CSN_PIN4 	0x10

// Initialize the SPI module
void SPI_init();

// Transmit a byte
void SPIwrite(uint8_t writeByte);

// Receive a byte
uint8_t SPIread();

// Set CE LOW -- used for signaling Nordic command starts
void CE_ClrVal();

// Set CE HIGH -- used for signaling Nordic command stops
void CE_SetVal();

// Set CSN HIGH -- used for signaling Nordic to start sending
void CSN_SetVal();

// Set CSN LOW -- used for signaling Nordic to start listening
void CSN_ClrVal();
#endif /* SPI_H_ */
