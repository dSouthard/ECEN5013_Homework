/*
 * spi.c
 *
 * ECEN 5013
 *  Created on: Apr 20, 2016
 *      Author: Diana Southard
 *
 *      Holds all of your SPI initialization and setup code
 */


#include "SPI.h"
#include "MKL25Z4.h"	// Common device definitions

// Initialize the SPI module
void SPI_init() {
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;      //Turn on clock to D module
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;       //Enable SPI0 clock

	PORTD_PCR0 = PORT_PCR_MUX(0x2);    //Set PTD0 to mux 2 [SPI0_PCS0]
	PORTD_PCR1 = PORT_PCR_MUX(0x2);    //Set PTD1 to mux 2 [SPI0_SCK]
	PORTD_PCR2 = PORT_PCR_MUX(0x2);    //Set PTD2 to mux 2 [SPI0_MOSI]
	PORTD_PCR3 = PORT_PCR_MUX(0x2);    //Set PTD3 to mux 2 [SPIO_MISO]

	SPI0_C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;   //Set SPI0 to Master & SS pin to auto SS

	SPI0_C2 = SPI_C2_MODFEN_MASK;   //Master SS pin acts as slave select output

	SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x08));     //Set baud rate prescale divisor to 3 & set baud rate divisor to 64 for baud rate of 15625 hz

	SPI0_C1 |= SPI_C1_SPE_MASK;    //Enable SPI0

}

// Transmit a byte
void SPI_tx_byte(uint8_t sendByte) {

}
