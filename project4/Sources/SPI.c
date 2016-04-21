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

	// Configure the SPI

	/* Control Register 1
	 * Enable SPI, disables receive and mode fault interrupts, Disables SPI transmit interrupts, sets the SPI module as a master SPI device
	 * Configures SPI clock as active-high, First edge on SPSCK at start of first data transfer cycle, Determines SS pin function when mode
	 * fault enabled, SPI serial data transfers start with most significant bit
	 */
	SPI0->C1 = C1_SETTING;

	/* Control Register 2
	 * SPI hardware match interrupt enabled, DMA request disabled, Disables mode fault function, SPI data I/O pin acts as input, DMA request
	 * disabled, SPI clocks operate in wait mode, Uses separate pins for data input and output
	 */
	SPI0->C2 = C2_SETTING;

	/* Baud Rate Register
	 * Sets prescale divisor to 5, Sets baud rate divisor to 3
	 * --> 542.25 kHz
	 */
	SPI0->BR = BR_SETTING;

	// Configure the port pins
	PORTD_PCR0 = PORT_PCR_MUX(MUX1);    // PTD0 pin is configured as GPIO (CE line driven manually)
	PORTD_PCR1 = PORT_PCR_MUX(MUX2);    // PTD1 pin is SPI0 CLK line
	PORTD_PCR2 = PORT_PCR_MUX(MUX2);    // PTD2 pin is SPI0 MOSI line
	PORTD_PCR3 = PORT_PCR_MUX(MUX2);    // PTD3 pin is SPI0 MISO line
	PORTD_PCR4 = PORT_PCR_MUX(MUX1);    // PTD4 pin is configured as GPIO (CSN line driven manually)

	// Setup CE [PORTD PIN 3] and CSN [PORTD PIN4] pins
	GPIOD->PDDR |= CE_PIN3 | CSN_PIN4;	   // GPIOD Pin 3/4 set as output to be used as Nordic's CE/CSN connection
}


// Transmit a byte
void SPIwrite(uint8_t writeByte) {
	// Wait for SPI Transmit Data Buffer Empty flag (SPTEF) to set
	while (!(SPI1->S & SPI_S_SPTEF_MASK));

	// Write byte to the data register
	SPI0->D = writeByte;
}

// Receive a byte
uint8_t SPIread() {
	// Wait for SPI Receive Data Buffer Full flag (SPRF) to set
	while (!(SPI1->S & SPI_S_SPRF_MASK));

	// return byte
	return SPI0->D;
}

// Set CE LOW -- used for signaling Nordic command starts
void CE_ClrVal() {
	GPIOD->PCOR |= CE_PIN3;
}

// Set CE HIGH -- used for signaling Nordic command stops
void CE_SetVal() {
	GPIOD->PCOR |= CE_PIN3;
}

// Set CSN HIGH -- used for signaling Nordic to start sending
void CSN_SetVal() {
	GPIOD->PSOR |= CSN_PIN4;
}

// Set CSN LOW -- used for signaling Nordic to start listening
void CSN_ClrVal() {
	GPIOD->PCOR |= CSN_PIN4;
}

